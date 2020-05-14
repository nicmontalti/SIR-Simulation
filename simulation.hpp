#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include "evolution.hpp"

enum class SIRState { S, I, R };

class Simulation
{
  using People = std::vector<Person>;

  int size_;

  class SIRGroups
  {
    People S_group_;
    People I_group_;
    People R_group_;

   public:
    SIRGroups(People const& S_group = People{},
              People const& I_group = People{},
              People const& R_group = People{});
    SIRGroups(int S, int I, int R);
    SIRGroups(int N);
    void add_person(SIRState state, Person const& person = Person{});
    int get_group_size(SIRState state);
  };

  SIRGroups sir_groups_;
  Evolution evolution_;

 public:
  Simulation(int size,
             SIRGroups const& sir_groups = SIRGroups{},
             Evolution const& evolution = Evolution{});

  int size();
};

#endif
