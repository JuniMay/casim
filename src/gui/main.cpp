#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "core/automaton.hpp"

int main() {
  std::string script;
  std::ifstream script_file;
  script_file.open("scripts/game_of_life.lua");
  std::stringstream buf;
  buf << script_file.rdbuf();
  script = buf.str();

  casim::core::Automaton a({20, 20}, script, 1);

  a.set_cell_state({1, 2}, 1);
  a.set_cell_state({2, 3}, 1);
  a.set_cell_state({3, 3}, 1);
  a.set_cell_state({3, 2}, 1);
  a.set_cell_state({3, 1}, 1);
  for (int i = 0; i <= 10; i++) {
    a.evolve_by_step();
    auto gen = a.get_curr_generation();
    // std::cout << gen << std::endl;

    for (size_t j = 0; j < 20; j++) {
      for (size_t k = 0; k < 20; k++) {
        std::cout << (gen[{j, k}] ? '#' : ' ');
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
  return 0;
}