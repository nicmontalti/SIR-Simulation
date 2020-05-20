#include "SIR_population.hpp"
#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

SIR_Population create_sir_population(int size, int S, int I, int R)
{
  assert(size > 0);
  assert(S >= 0);
  assert(I >= 0);
  assert(R >= 0);

  SIR_Population population{People(S), People(I), People(R)};

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> position_distribution{
      0., static_cast<double>(size)};

  auto new_starting_state = [&]() {
    double const x = position_distribution(gen);
    double const y = position_distribution(gen);
    return Person{Position{x, y}, Velocity{0., 0.}};
  };

  std::generate(population.S.begin(), population.S.end(), new_starting_state);
  std::generate(population.I.begin(), population.I.end(), new_starting_state);
  std::generate(population.R.begin(), population.R.end(), new_starting_state);
}