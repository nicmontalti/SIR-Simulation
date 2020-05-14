#include "simulation.hpp"
#include <cassert>

Simulation::Simulation(int size,
                       SIRGroups const& sir_groups,
                       Evolution const& evolution)
    : size_{size}, sir_groups_{sir_groups}, evolution_{evolution}
{
  assert(size_ > 0);
}

int Simulation::size()
{
  return size_;
}