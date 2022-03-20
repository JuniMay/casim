// still many bruteforce implementation in this file
// TODO: optimization

#include "core/automaton.hpp"

namespace casim {
namespace core {

Automaton::Automaton(const xt::xarray<size_t>& shape,
                     const std::string& script) {
  shape_ = shape;

  script_ = script;

  flip_ = 0;
  generation_0_.resize(shape_);
  generation_1_.resize(shape_);
  generation_0_.fill(0);
  generation_1_.fill(0);
  dim_ = shape_.size();
  // set default to 1
  neighbor_radius_ = 1;

  calc_local_states_size();

  local_states_.resize({local_states_size_});
  local_states_.fill(0);

  // state_cnt_ = 2;
  // state_color_list_ = {"#ffffff", "#000000"};
}  // namespace core

Automaton::Automaton(const xt::xarray<size_t>& shape, const std::string& script,
                     const size_t& neighbor_radius) {
  shape_ = shape;

  script_ = script;

  flip_ = 0;
  generation_0_.resize(shape_);
  generation_1_.resize(shape_);
  generation_0_.fill(0);
  generation_1_.fill(0);
  dim_ = shape_.size();
  neighbor_radius_ = neighbor_radius;

  calc_local_states_size();

  local_states_.resize({local_states_size_});
  local_states_.fill(0);

  // TODO: better initialization
  // e.g. check if the script works
  // state_cnt_ = 2;
  // state_color_list_ = {"#ffffff", "#000000"};
}

void Automaton::set_shape(const xt::xarray<size_t>& shape) {
  shape_ = shape;
  generation_0_.resize(shape);
  generation_1_.resize(shape);
  // xarray do not preserve data in `resize`
  // after setting the shape of the grid/universe,
  // the states of all cells are set to 0 the default state.
  reset();
  dim_ = shape_.size();

  calc_local_states_size();

  local_states_.resize({local_states_size_});
  local_states_.fill(0);
}

void Automaton::set_script(const std::string& script) {
  script_ = script;
  //  std::cout << script_ << std::endl;
  fetch_ca_name();
  fetch_state_cnt();
  fetch_state_color_list();
}
void Automaton::set_neighbor_radius(const size_t& neighbor_radius) {
  neighbor_radius_ = neighbor_radius;
}

const xt::xarray<uint32_t>& Automaton::get_curr_generation() {
  if (flip_) {
    return generation_1_;
  } else {
    return generation_0_;
  }
}
const xt::xarray<size_t>& Automaton::get_shape() { return shape_; }
const std::string& Automaton::get_script() { return script_; }
const size_t& Automaton::get_neighbor_radius() { return neighbor_radius_; }
const std::string& Automaton::get_ca_name() { return ca_name_; }
const std::string& Automaton::get_default_color() { return default_color_; }
const std::vector<std::string>& Automaton::get_state_color_list() {
  return state_color_list_;
}
const size_t& Automaton::get_state_cnt() { return state_cnt_; }

void Automaton::reset() {
  flip_ = 0;
  generation_0_.fill(0);
  generation_1_.fill(0);
}

void Automaton::set_cell_state(const xt::xarray<size_t>& coordinate,
                               uint32_t state) {
  std::cout << coordinate << std::endl << state << std::endl;
  if (flip_) {
    generation_1_[coordinate] = state;
  } else {
    generation_0_[coordinate] = state;
  }
}

void Automaton::fetch_local_states(const xt::xarray<size_t>& coordinate) {
  local_states_.fill(0);
  local_states_idx_ = 0;
  xt::xarray<size_t> c;
  c.resize({dim_});
  fecth_local_states_helper(coordinate, c, 0);
  // std::cout << generation_0_ << std::endl;
  // std::cout << generation_1_ << std::endl;
  // std::cout << local_states_ << std::endl;
}

void Automaton::evolve_by_step() {
  flip_ = !flip_;

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dostring(L, script_.c_str());
  xt::xarray<size_t> c;
  c.resize({dim_});
  evolve_by_step_helper(L, c, 0);
  std::cout << "OK" << std::endl;
  lua_close(L);
}

void Automaton::fetch_state_color_list() {
  state_color_list_.clear();

  lua_State* L = luaL_newstate();
  luaL_dostring(L, script_.c_str());

  lua_getglobal(L, "default_color");
  default_color_ = lua_tostring(L, -1);
  lua_pop(L, 1);

  lua_getglobal(L, "color");
  if (!lua_istable(L, -1)) {
    // TODO
    return;
  }
  state_color_list_.push_back(default_color_);
  for (size_t i = 1; i <= state_cnt_ - 1; ++i) {
    lua_pushnumber(L, i);
    lua_gettable(L, -2);
    state_color_list_.push_back(lua_tostring(L, -1));
    lua_pop(L, 1);
  }
  lua_pop(L, 1);
  lua_close(L);
}

void Automaton::fetch_ca_name() {
  lua_State* L = luaL_newstate();
  luaL_dostring(L, script_.c_str());
  lua_getglobal(L, "name");
  if (!lua_isstring(L, -1)) {
    // TODO
    return;
  }
  ca_name_ = lua_tostring(L, -1);
  lua_pop(L, 1);
  lua_close(L);
}

void Automaton::fetch_state_cnt() {
  lua_State* L = luaL_newstate();
  luaL_dostring(L, script_.c_str());
  lua_getglobal(L, "state_count");
  if (!lua_isinteger(L, -1)) {
    // TODO
    return;
  }
  state_cnt_ = lua_tointeger(L, -1);
  lua_pop(L, 1);
  lua_close(L);
}

// native recursive
// TODO: use stack
void Automaton::fecth_local_states_helper(const xt::xarray<size_t>& coordinate,
                                          xt::xarray<size_t>& c, size_t axis) {
  if (axis == dim_) {
    // std::cout << c << std::endl;
    // std::cout << local_states_ << std::endl;
    for (size_t i = 0; i < axis; ++i) {
      if (c[i] == (size_t)-1) {
        local_states_[local_states_idx_++] = 0;
        return;
      }
    }
    if (flip_) {
      local_states_[local_states_idx_++] = generation_0_[c];
    } else {
      local_states_[local_states_idx_++] = generation_1_[c];
    }
    return;
  }

  for (size_t r = neighbor_radius_; r > 0; --r) {
    if (coordinate[axis] < r) {
      c[axis] = -1;
      fecth_local_states_helper(coordinate, c, axis + 1);
    } else {
      c[axis] = coordinate[axis] - r;
      fecth_local_states_helper(coordinate, c, axis + 1);
    }
  }

  c[axis] = coordinate[axis];
  fecth_local_states_helper(coordinate, c, axis + 1);

  for (size_t r = 1; r <= neighbor_radius_; ++r) {
    if (coordinate[axis] + r >= shape_[axis]) {
      c[axis] = -1;
      fecth_local_states_helper(coordinate, c, axis + 1);
    } else {
      c[axis] = coordinate[axis] + r;
      fecth_local_states_helper(coordinate, c, axis + 1);
    }
  }
}

// native recursive
// TODO: use stack
// TODO: error handling
void Automaton::evolve_by_step_helper(lua_State*& L, xt::xarray<size_t>& c,
                                      size_t axis) {
  if (axis == dim_) {
    lua_getglobal(L, "local_evolve");
    if (!lua_isfunction(L, -1)) {
      // TODO
      return;
    }
    fetch_local_states(c);
    lua_newtable(L);
    for (size_t i = 0; i < local_states_size_; ++i) {
      lua_pushnumber(L, i + 1);
      lua_pushnumber(L, local_states_[i]);
      lua_settable(L, -3);
    }
    lua_pcall(L, 1, 1, 0);
    // std::cout << c << " " << lua_tointeger(L, -1) << std::endl;
    set_cell_state(c, lua_tointeger(L, -1));
    lua_pop(L, 1);
    return;
  }
  for (size_t idx = 0; idx < shape_[axis]; ++idx) {
    c[axis] = idx;
    evolve_by_step_helper(L, c, axis + 1);
  }
}

void Automaton::calc_local_states_size() {
  local_states_size_ = 1;
  for (size_t i = 0; i < dim_; ++i) {
    local_states_size_ *= (2 * neighbor_radius_ + 1);
  }
}

}  // namespace core
}  // namespace casim
