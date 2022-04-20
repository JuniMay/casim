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

    void setShape(const xt::xarray<size_t>& shape);

    void setScript(const std::string& script);

    void setNeighborRadius(const size_t& neighbor_radius);

    const xt::xarray<uint32_t>& getCurrGeneration();

    const xt::xarray<size_t>& getShape();

    const std::string& getScript();

    const size_t& getNeighborRadius();

    const std::string& getName();

    const std::string& getDefaultColor();

    const std::vector<std::string>& getStateColorList();

    const size_t& getStateCnt();

    const size_t& getDim();

    // set current generation to 0, and fill with 0
    void reset();
    // set cell at `coordinate` to `state`
    void setCellState(const xt::xarray<size_t>& coordinate, uint32_t state);

    void fetchLocalStates(const xt::xarray<size_t>& coordinate);
    // evolve single step to next generation
    bool evolve();
    // fetch all config from lua script
    void fetchAll();
    // load `*.npy` file from `path`
    //   after loading the shape of the generation buffer is set to the shape in
    //   `*.npy` file
    bool loadPatternFromFile(const std::string& path);
    // save current generation to `path`
    bool savePatternToFile(const std::string& path);
    // randomize
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
    void fecthLocalStatesHelper(const xt::xarray<size_t>& coordinate,
                                xt::xarray<size_t>& c,
                                size_t axis);
    // yet recursive
    bool evolveHelper(lua_State*& L, xt::xarray<size_t>& c, size_t axis);
    // calculate the size of `local_states_`
    // result will be stored at `local_states_size_`
    void calcLocalStatesSize();
    // fetch `color` from lua script
    bool fetchStateColorList();
    // fetch `name` from lua script
    bool fetchName();
    // fetch `state_count` from lua script
    bool fetchStateCnt();
    // fetch `dimension` from lua script
    bool fetchDim();
    // fetch `min_size` from lua script
    bool fetchMinSize();
    // fetch `neighbor_raidius` from lua script
    bool fetchNeighborRadius();
};

}  // namespace core
}  // namespace casim

#endif
