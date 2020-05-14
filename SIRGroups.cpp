#include <cassert>
#include "simulation.hpp"

Simulation::SIRGroups::SIRGroups(People const& S_group,
                                 People const& I_group,
                                 People const& R_group)
    : S_group_{S_group}, I_group_{I_group}, R_group_{R_group} {};

Simulation::SIRGroups::SIRGroups(int S, int I, int R)
    : S_group_(S), I_group_(I), R_group_(R)
{
  // metterli in posizione
  // meglio usare default constructor di Person?
}

Simulation::SIRGroups::SIRGroups(int N) : SIRGroups(N - 1, 1, 0)
{
}

void Simulation::SIRGroups::add_person(SIRState state, Person const& person)
{
  switch (state) {
    case (SIRState::S):
      S_group_.push_back(person);
      break;
    case (SIRState::I):
      I_group_.push_back(person);
      break;
    case (SIRState::R):
      R_group_.push_back(person);
      break;
    default:
      assert(true);
  }
}

int Simulation::SIRGroups::get_group_size(SIRState state)
{
  switch (state) {
    case (SIRState::S):
      return S_group_.size();
    case (SIRState::I):
      return I_group_.size();
    case (SIRState::R):
      return R_group_.size();
    default:
      return (0);
  }
}