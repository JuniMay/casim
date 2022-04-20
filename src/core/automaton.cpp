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

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);

    fetchAll();
}

Automaton::Automaton(const xt::xarray<size_t>& shape,
                     const std::string& script,
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

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);

    fetchAll();
}

void Automaton::setShape(const xt::xarray<size_t>& shape) {
    shape_ = shape;
    generation_0_.resize(shape);
    generation_1_.resize(shape);
    // xarray do not preserve data in `resize`
    // after setting the shape of the grid/universe,
    // the states of all cells are set to 0 the default state.
    reset();
    dim_ = shape_.size();

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);
}

void Automaton::setScript(const std::string& script) {
    script_ = script;
    //  std::cout << script_ << std::endl;
    fetchAll();
}
void Automaton::setNeighborRadius(const size_t& neighbor_radius) {
    neighbor_radius_ = neighbor_radius;
}

const xt::xarray<uint32_t>& Automaton::getCurrGeneration() {
    if (flip_) {
        return generation_1_;
    } else {
        return generation_0_;
    }
}

const xt::xarray<size_t>& Automaton::getShape() {
    return shape_;
}

const std::string& Automaton::getScript() {
    return script_;
}

const size_t& Automaton::getNeighborRadius() {
    return neighbor_radius_;
}

const std::string& Automaton::getName() {
    return name_;
}

const std::string& Automaton::getDefaultColor() {
    return state_color_list_[0];
}

const std::vector<std::string>& Automaton::getStateColorList() {
    return state_color_list_;
}

const size_t& Automaton::getStateCnt() {
    return state_cnt_;
}

const size_t& Automaton::getDim() {
    return dim_;
}

void Automaton::reset() {
    flip_ = 0;
    generation_0_.fill(0);
    generation_1_.fill(0);
}

void Automaton::setCellState(const xt::xarray<size_t>& coordinate,
                             uint32_t state) {
    if (flip_) {
        generation_1_[coordinate] = state;
    } else {
        generation_0_[coordinate] = state;
    }
}

void Automaton::fetchLocalStates(const xt::xarray<size_t>& coordinate) {
    local_states_.fill(0);
    local_states_idx_ = 0;
    xt::xarray<size_t> c;
    c.resize({dim_});
    fecthLocalStatesHelper(coordinate, c, 0);
}

bool Automaton::evolve() {
    flip_ = !flip_;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dostring(L, script_.c_str());
    xt::xarray<size_t> c;
    c.resize({dim_});
    bool success = evolveHelper(L, c, 0);
    lua_close(L);
    return success;
}

bool Automaton::fetchStateColorList() {
    state_color_list_.clear();

    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());

    lua_getglobal(L, "color");
    if (!lua_istable(L, -1)) {
        return false;
    }

    for (size_t i = 1; i <= state_cnt_; ++i) {
        lua_pushnumber(L, i);
        lua_gettable(L, -2);
        if (!lua_isstring(L, -1)) {
            return false;
        }
        state_color_list_.push_back(lua_tostring(L, -1));
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
    lua_close(L);
    return true;
}

bool Automaton::fetchName() {
    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());
    lua_getglobal(L, "name");
    if (!lua_isstring(L, -1)) {
        return false;
    }
    name_ = lua_tostring(L, -1);
    lua_pop(L, 1);
    lua_close(L);
    return true;
}

bool Automaton::fetchStateCnt() {
    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());
    lua_getglobal(L, "state_count");
    if (!lua_isinteger(L, -1)) {
        return false;
    }
    state_cnt_ = lua_tointeger(L, -1);
    lua_pop(L, 1);
    lua_close(L);
    return true;
}

bool Automaton::fetchDim() {
    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());
    lua_getglobal(L, "dimensions");
    if (!lua_isinteger(L, -1)) {
        return false;
    }
    dim_ = lua_tointeger(L, -1);

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);

    lua_pop(L, 1);
    lua_close(L);
    return true;
}

bool Automaton::fetchMinSize() {
    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());

    lua_getglobal(L, "min_size");

    if (!lua_istable(L, -1)) {
        return false;
    }

    xt::xarray<size_t> shape;

    shape.resize({dim_});

    for (size_t i = 1; i <= dim_; ++i) {
        lua_pushnumber(L, i);
        lua_gettable(L, -2);
        if (!lua_isinteger(L, -1)) {
            return false;
        }
        shape[i - 1] = lua_tointeger(L, -1);

        lua_pop(L, 1);
    }

    shape_ = shape;
    generation_0_.resize(shape);
    generation_1_.resize(shape);
    reset();

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);

    lua_pop(L, 1);
    lua_close(L);
    return true;
}

bool Automaton::fetchNeighborRadius() {
    lua_State* L = luaL_newstate();
    luaL_dostring(L, script_.c_str());
    lua_getglobal(L, "neighbor_radius");
    if (!lua_isinteger(L, -1)) {
        return false;
    }
    neighbor_radius_ = lua_tointeger(L, -1);

    calcLocalStatesSize();

    local_states_.resize({local_states_size_});
    local_states_.fill(0);

    lua_pop(L, 1);
    lua_close(L);
    return true;
}

void Automaton::fetchAll() {
    if (!fetchName()) {
        name_ = "";
    }
    if (!fetchStateCnt()) {
        state_cnt_ = 0;
    }
    if (!fetchStateColorList()) {
        //
    }
    if (!fetchDim()) {
        dim_ = 0;
    }
    if (!fetchMinSize()) {
        //
    }
    if (!fetchNeighborRadius()) {
        neighbor_radius_ = 0;
    }
    reset();
}

bool Automaton::loadPatternFromFile(const std::string& path) {
    xt::xarray<uint32_t> data = xt::load_npy<uint32_t>(path);
    xt::xarray<size_t> shape;
    shape.resize({data.shape().size()});
    for (size_t i = 0; i < data.shape().size(); ++i) {
        shape[i] = data.shape()[i];
    }
    setShape(shape);

    generation_0_ = data;
    generation_1_ = data;

    return true;
}

bool Automaton::savePatternToFile(const std::string& path) {
    xt::dump_npy(path, getCurrGeneration());
    return true;
}

void Automaton::random(const std::vector<double>& w) {
    reset();
    std::mt19937 engine(time(0));
    std::discrete_distribution dist(w.begin(), w.end());
    for (auto iter = generation_0_.begin(); iter != generation_0_.end();
         iter++) {
        *iter = dist(engine);
    }
}

// native recursive
// TODO: use stack
void Automaton::fecthLocalStatesHelper(const xt::xarray<size_t>& coordinate,
                                       xt::xarray<size_t>& c,
                                       size_t axis) {
    if (axis == dim_) {
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
            fecthLocalStatesHelper(coordinate, c, axis + 1);
        } else {
            c[axis] = coordinate[axis] - r;
            fecthLocalStatesHelper(coordinate, c, axis + 1);
        }
    }

    c[axis] = coordinate[axis];
    fecthLocalStatesHelper(coordinate, c, axis + 1);

    for (size_t r = 1; r <= neighbor_radius_; ++r) {
        if (coordinate[axis] + r >= shape_[axis]) {
            c[axis] = -1;
            fecthLocalStatesHelper(coordinate, c, axis + 1);
        } else {
            c[axis] = coordinate[axis] + r;
            fecthLocalStatesHelper(coordinate, c, axis + 1);
        }
    }
}

// native recursive
// TODO: use stack
// TODO: multithreading?
bool Automaton::evolveHelper(lua_State*& L,
                             xt::xarray<size_t>& c,
                             size_t axis) {
    if (axis == dim_) {
        lua_getglobal(L, "local_evolve");
        if (!lua_isfunction(L, -1)) {
            return false;
        }
        fetchLocalStates(c);
        lua_newtable(L);
        for (size_t i = 0; i < local_states_size_; ++i) {
            lua_pushnumber(L, i + 1);
            lua_pushnumber(L, local_states_[i]);
            lua_settable(L, -3);
        }
        lua_pcall(L, 1, 1, 0);
        setCellState(c, lua_tointeger(L, -1));
        lua_pop(L, 1);
        return true;
    }
    for (size_t idx = 0; idx < shape_[axis]; ++idx) {
        c[axis] = idx;
        if (!evolveHelper(L, c, axis + 1)) {
            return false;
        }
    }
    return true;
}

void Automaton::calcLocalStatesSize() {
    local_states_size_ = 1;
    for (size_t i = 0; i < dim_; ++i) {
        local_states_size_ *= (2 * neighbor_radius_ + 1);
    }
}

}  // namespace core
}  // namespace casim
