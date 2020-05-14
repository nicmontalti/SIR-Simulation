#include "simulation.hpp"
#include <algorithm>
#include <cassert>

Simulation::Simulation(int size,
                       SIRGroups const& sir_groups,
                       Evolution const& evolution)
    : size_{size}, sir_groups_{sir_groups}, evolution_{evolution}
{
  assert(size_ > 0);

  auto check_position = [=](Person const& p) {
    return (p.position.x >= 0 && p.position.x <= size_ && p.position.y >= 0 &&
            p.position.y <= size_);
  };

  auto check_everyone_position = [&](People const& group) {
    auto it = std::find_if(group.begin(), group.end(), check_position);
    return (it == group.end());
  };

  assert(check_everyone_position(sir_groups_.S));
  assert(check_everyone_position(sir_groups_.I));
  assert(check_everyone_position(sir_groups_.R));
}

int Simulation::size()
{
  return size_;
}