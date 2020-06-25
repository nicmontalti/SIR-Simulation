#include "doctest.h"
#include "simulation.hpp"

using namespace sir;

double position_mean(People const& people)
{
  double sum = 0.;
  int N = 0;
  for (Person const& person : people) {
    sum += person.position.x;
    sum += person.position.y;
    N += 2;
  }
  return (sum / N);
}

TEST_CASE("Testing Simulation_State constructor")
{
  int constexpr S = 10;
  int constexpr I = 20;
  int constexpr R = 30;
  int constexpr size1 = 10;

  Simulation_State state1{size1, S, I, R};

  SUBCASE("checking people position and velocity")
  {
    CHECK(state1.size == size1);
    CHECK(state1.ticks == 0);

    CHECK(state1.population.S.size() == S);
    CHECK(state1.population.I.size() == I);
    CHECK(state1.population.R.size() == R);

    for (Person const& person : state1.population.S) {
      CHECK(person.position.x >= 0.);
      CHECK(person.position.x <= state1.size);
      CHECK(person.position.y >= 0.);
      CHECK(person.position.y <= state1.size);
      CHECK(person.velocity.vx == 0.);
      CHECK(person.velocity.vy == 0.);
    }

    for (Person const& person : state1.population.I) {
      CHECK(person.position.x >= 0.);
      CHECK(person.position.x <= state1.size);
      CHECK(person.position.y >= 0.);
      CHECK(person.position.y <= state1.size);
      CHECK(person.velocity.vx == 0.);
      CHECK(person.velocity.vy == 0.);
    }

    for (Person const& person : state1.population.R) {
      CHECK(person.position.x >= 0.);
      CHECK(person.position.x <= state1.size);
      CHECK(person.position.y >= 0.);
      CHECK(person.position.y <= state1.size);
      CHECK(person.velocity.vx == 0.);
      CHECK(person.velocity.vy == 0.);
    }
  }

  int constexpr S2 = 100;
  int constexpr I2 = 200;
  int constexpr R2 = 300;
  int constexpr size2 = 10;

  Simulation_State state2{size2, S2, I2, R2};

  SUBCASE("Checking position mean")
  {
    CHECK(position_mean(state2.population.S) ==
          doctest::Approx(state2.size / 2).epsilon(0.5));
    CHECK(position_mean(state2.population.I) ==
          doctest::Approx(state2.size / 2).epsilon(0.5));
    CHECK(position_mean(state2.population.R) ==
          doctest::Approx(state2.size / 2).epsilon(0.5));
  }

  // THE FOLLOWING STATEMENT SHOULD TRIGGER AN ASSERT
  // Simulation_State{-10, pop1};
}
