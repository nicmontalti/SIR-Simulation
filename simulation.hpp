#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "evolution.hpp"

class Simulation
{
  int size_;
  std::vector<Person> S_vector_;
  std::vector<Person> I_vector_;
  std::vector<Person> R_vector_;
  Evolution evolution_;

 public:
  Simulation(int size, Evolution const& evolution = Evolution{});
  Simulation(int size, int N, Evolution const& evolution = Evolution{});
  Simulation(
      int size, int S, int I, int R, Evolution const& evolution = Evolution{});

  int size();
  int get_S_number();
  int get_I_number();
  int get_R_number();
};

#endif
