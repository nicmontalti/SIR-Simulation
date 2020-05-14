#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "evolution.hpp"

using People = std::vector<Person>;

struct SIRGroups
{
  People S;
  People I;
  People R;
};

class Simulation
{
  int size_;
  SIRGroups sir_groups_;
  Evolution evolution_;

  bool check_everyone_position();

 public:
  Simulation(int size,
             SIRGroups const& sir_groups = SIRGroups{People{},
                                                     People{},
                                                     People{}},
             Evolution const& evolution = Evolution{});
  Simulation(
      int size, int S, int I, int R, Evolution const& evolution = Evolution{});
  Simulation(int size, int N, Evolution const& evolution = Evolution{});

  auto& get_sir_groups() const
  {
    return sir_groups_;
  }
  int size() const
  {
    return size_;
  };
};

#endif
