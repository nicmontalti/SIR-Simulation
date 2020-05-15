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
  Motion motion_;
  Infection infection_;

  bool check_everyone_position();

 public:
  Simulation(int size,
             SIRGroups const& sir_groups = SIRGroups{People{},
                                                     People{},
                                                     People{}},
             Motion const& motion = Motion{},
             Infection const& infection = Infection{});
  Simulation(int size,
             int S,
             int I,
             int R,
             Motion const& motion = Motion{},
             Infection const& infection = Infection{});
  Simulation(int size,
             int N,
             Motion const& motion = Motion{},
             Infection const& infection = Infection{});

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
