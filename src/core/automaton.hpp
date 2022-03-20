#ifndef CASIM_CORE_AUTOMATON_H_
#define CASIM_CORE_AUTOMATON_H_

#include "core/common.hpp"
#include "third_party/lua/lua.hpp"
#include "third_party/xtensor/xarray.hpp"

namespace casim {
namespace core {

class Automaton {
 public:
  Automaton(const xt::xarray<size_t>& shape, const std::string& script);
  Automaton(const xt::xarray<size_t>& shape, const std::string& script,
            const size_t& neighbor_radius);

  void set_shape(const xt::xarray<size_t>& shape);
  void set_script(const std::string& script);
  void set_neighbor_radius(const size_t& neighbor_radius);

  const xt::xarray<uint32_t>& get_curr_generation();

  const xt::xarray<size_t>& get_shape();
  const std::string& get_script();
  const size_t& get_neighbor_radius();
  const std::string& get_ca_name();
  const std::string& get_default_color();
  const std::vector<std::string>& get_state_color_list();
  const size_t& get_state_cnt();

  void reset();

  void set_cell_state(const xt::xarray<size_t>& coordinate, uint32_t state);

  void fetch_local_states(const xt::xarray<size_t>& coordinate);
  bool evolve_by_step();

  bool fetch_state_color_list();
  bool fetch_ca_name();
  bool fetch_state_cnt();

 private:
  // the lua script for the rule
  std::string script_;
  xt::xarray<size_t> shape_;
  size_t neighbor_radius_;

  // `flip_` indicates the current generation
  // flip_ == 0 => current is generation_0_
  // flip_ == 1 => current is generation_1_
  bool flip_;
  size_t dim_;
  xt::xarray<uint32_t> local_states_;
  size_t local_states_idx_;
  size_t local_states_size_;
  xt::xarray<uint32_t> generation_0_;
  xt::xarray<uint32_t> generation_1_;

  std::string ca_name_;  // name of cellular automaton

  std::vector<std::string> state_color_list_;
  size_t state_cnt_;

  void fecth_local_states_helper(const xt::xarray<size_t>& coordinate,
                                 xt::xarray<size_t>& c, size_t axis);
  bool evolve_by_step_helper(lua_State*& L, xt::xarray<size_t>& c, size_t axis);
  void calc_local_states_size();
};

}  // namespace core
}  // namespace casim

#endif