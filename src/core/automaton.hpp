#ifndef CASIM_CORE_AUTOMATON_H_
#define CASIM_CORE_AUTOMATON_H_

#include "core/common.hpp"
#include "core/utils.hpp"

namespace casim {
namespace core {

class Automaton {
 public:
  Automaton(const xt::xarray<size_t>& shape, const std::string& script);

  Automaton(const xt::xarray<size_t>& shape,
            const std::string& script,
            const size_t& neighbor_radius);

  void set_shape(const xt::xarray<size_t>& shape);

  void set_script(const std::string& script);

  void set_neighbor_radius(const size_t& neighbor_radius);

  const xt::xarray<uint32_t>& get_curr_generation();

  const xt::xarray<size_t>& get_shape();

  const std::string& get_script();

  const size_t& get_neighbor_radius();

  const std::string& get_name();

  const std::string& get_default_color();

  const std::vector<std::string>& get_state_color_list();

  const size_t& get_state_cnt();

  const size_t& get_dim();

  // set current generation to 0, and fill with 0
  void reset();
  // set cell at `coordinate` to `state`
  void set_cell_state(const xt::xarray<size_t>& coordinate, uint32_t state);

  void fetch_local_states(const xt::xarray<size_t>& coordinate);
  // evolve single step to next generation
  bool evolve_by_step();
  // fetch all config from lua script
  bool fetch_all();
  // load `*.npy` file from `path`
  //   after loading the shape of the generation buffer is set to the shape in
  //   `*.npy` file
  bool load_pattern_from_file(const std::string& path);
  // save current generation to `path`
  bool save_pattern_to_file(const std::string& path);
  // randomize
  // TODO: specify posibility
  void random(const std::vector<double>& w);

 private:
  // the lua script for the rule
  std::string script_;
  // shape of generation buffer
  // TODO(maybe): dynamically resizing
  xt::xarray<size_t> shape_;
  // neighbor radius
  //   take moore neighbor as example:
  //     * * *
  //     * # * --> neighbor_radius == 1
  //     * * *
  //
  //     * * * * *
  //     * * * * *
  //     * * # * * --> neighbor_radius == 2
  //     * * * * *
  //     * * * * *
  size_t neighbor_radius_;

  // `flip_` indicates the current generation
  //   flip_ == 0 => current is generation_0_
  //   flip_ == 1 => current is generation_1_
  bool flip_;
  // dimension of this ca
  size_t dim_;
  // storing local states of given cell
  xt::xarray<uint32_t> local_states_;
  // local_states_idx/size_ is used for recursive fetching local states
  size_t local_states_idx_;
  size_t local_states_size_;
  // generations storing current and previous data.
  xt::xarray<uint32_t> generation_0_;
  xt::xarray<uint32_t> generation_1_;
  // name of cellular automaton
  std::string name_;
  // color of different states, represented as `std::string`
  std::vector<std::string> state_color_list_;
  // number of different states in this CA
  size_t state_cnt_;
  // yet recursive
  void fecth_local_states_helper(const xt::xarray<size_t>& coordinate,
                                 xt::xarray<size_t>& c,
                                 size_t axis);
  // yet recursive
  bool evolve_by_step_helper(lua_State*& L, xt::xarray<size_t>& c, size_t axis);
  // calculate the size of `local_states_`
  // result will be stored at `local_states_size_`
  void calc_local_states_size();
  // fetch `color` from lua script
  bool fetch_state_color_list();
  // fetch `name` from lua script
  bool fetch_name();
  // fetch `state_count` from lua script
  bool fetch_state_cnt();
  // fetch `dimension` from lua script
  bool fetch_dim();
  // fetch `min_size` from lua script
  bool fetch_min_size();
};

}  // namespace core
}  // namespace casim

#endif
