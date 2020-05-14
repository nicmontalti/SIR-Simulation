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

 public:
  Simulation(int size,
             SIRGroups const& sir_groups = SIRGroups{People{},
                                                     People{},
                                                     People{}},
             Evolution const& evolution = Evolution{});

  int size();
};

#endif
