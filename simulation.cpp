#include "simulation.hpp"
#include <algorithm>
#include <cassert>
#include <random>

bool Simulation::check_everyone_position()
{
  auto const check_position = [=](Person const& p) {
    return (p.position.x >= 0 && p.position.x <= size_ && p.position.y >= 0 &&
            p.position.y <= size_);
  };
  auto const check_group_position = [&](People const& group) {
    auto it = std::find_if_not(group.begin(), group.end(), check_position);
    return (it == group.end());
  };
  return check_group_position(sir_groups_.S) &&
         check_group_position(sir_groups_.I) &&
         check_group_position(sir_groups_.R);
}

Simulation::Simulation(int size,
                       SIRGroups const& sir_groups,
                       Evolution const& evolution)
    : size_{size}, sir_groups_{sir_groups}, evolution_{evolution}
{
  assert(size_ > 0);
  assert(check_everyone_position());
}

Simulation::Simulation(
    int size, int S, int I, int R, Evolution const& evolution)
    : size_{size}
    , sir_groups_{People(S), People(I), People(R)}
    , evolution_{evolution}
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> position_distribution{
      0., static_cast<double>(size_)};
  auto new_starting_state = [&]() {
    double const x = position_distribution(gen);
    double const y = position_distribution(gen);
    return Person{Position{x, y}, Velocity{0., 0.}};
  };
  std::generate(sir_groups_.S.begin(), sir_groups_.S.end(), new_starting_state);
  std::generate(sir_groups_.I.begin(), sir_groups_.I.end(), new_starting_state);
  std::generate(sir_groups_.R.begin(), sir_groups_.R.end(), new_starting_state);

  assert(check_everyone_position());
}

Simulation::Simulation(int size, int N, Evolution const& evolution)
    : Simulation(size, N - 1, 1, 0, evolution)
{
}