#include "doctest.h"
#include "random_motion.hpp"
#include "simulation.hpp"

using namespace sir;

TEST_CASE("Testing motion")
{
  int constexpr size = 100;
  double constexpr sd_motion = 0.;

  People people{Person{Position{0., 0.}, Velocity{0., 0.}}};
  Population population{people, People(), People()};
  Simulation_State state(size, population);
  Random_Motion motion{sd_motion};

  SUBCASE("no acceleration (sd = 0)")
  {
    CHECK(state.population.S[0].position.x == doctest::Approx(0.));
    CHECK(state.population.S[0].position.y == doctest::Approx(0.));

    motion.update(state.population, state.size);
    CHECK(state.population.S[0].position.x == doctest::Approx(0.));
    CHECK(state.population.S[0].position.y == doctest::Approx(0.));

    state.population.S[0].velocity.vx = 10.;
    state.population.S[0].velocity.vy = 20.;
    motion.update(state.population, state.size);

    CHECK(state.population.S[0].velocity.vx ==
          doctest::Approx(10.).epsilon(0.02));
    CHECK(state.population.S[0].velocity.vy ==
          doctest::Approx(20.).epsilon(0.02));
    CHECK(state.population.S[0].position.x ==
          doctest::Approx(10.).epsilon(0.02));
    CHECK(state.population.S[0].position.y ==
          doctest::Approx(20.).epsilon(0.02));
  }

  SUBCASE("friction")
  {
    // v -= |v| * v / 10000

    state.population.S[0].position.x = 0.;
    state.population.S[0].position.y = 0.;
    state.population.S[0].velocity.vx = 100.;
    state.population.S[0].velocity.vy = 200.;
    motion.update(state.population, state.size);

    CHECK(std::abs(state.population.S[0].velocity.vx) ==
          doctest::Approx(99.).epsilon(0.01));
    CHECK(std::abs(state.population.S[0].velocity.vy) ==
          doctest::Approx(196.).epsilon(0.01));
  }

  SUBCASE("bouncing")
  {
    state.population.S[0].position.x = 0.;
    state.population.S[0].position.y = 0.;
    state.population.S[0].velocity.vx = -10.;
    state.population.S[0].velocity.vy = -20.;
    motion.update(state.population, state.size);

    CHECK(state.population.S[0].velocity.vx ==
          doctest::Approx(10.).epsilon(0.02));
    CHECK(state.population.S[0].velocity.vy ==
          doctest::Approx(20.).epsilon(0.02));
    CHECK(state.population.S[0].position.x ==
          doctest::Approx(0.).epsilon(0.02));
    CHECK(state.population.S[0].position.y ==
          doctest::Approx(0.).epsilon(0.02));
    CHECK(state.population.S[0].position.x >= 0.);
    CHECK(state.population.S[0].position.y >= 0.);

    state.population.S[0].position.x = size;
    state.population.S[0].position.y = size;
    state.population.S[0].velocity.vx = 10.;
    state.population.S[0].velocity.vy = 20.;
    motion.update(state.population, state.size);

    CHECK(state.population.S[0].velocity.vx ==
          doctest::Approx(-10.).epsilon(0.02));
    CHECK(state.population.S[0].velocity.vy ==
          doctest::Approx(-20.).epsilon(0.02));
    CHECK(state.population.S[0].position.x ==
          doctest::Approx(state.size).epsilon(0.02));
    CHECK(state.population.S[0].position.y ==
          doctest::Approx(state.size).epsilon(0.02));
    CHECK(state.population.S[0].position.x <= state.size);
    CHECK(state.population.S[0].position.x <= state.size);
  }

  int constexpr S = 200;
  int constexpr I = 0;
  int constexpr R = 0;
  int constexpr sd_motion_2 = 1.;

  Simulation_State state_2(size, S, I, R);
  Random_Motion motion_2{sd_motion_2};

  SUBCASE("Testing motion position, velocity and acceleration mean")
  {
    for (int i = 0; i != 10; ++i) {
      Simulation_State previous_state = state_2;
      double position_sum = 0.;
      double displacement_sum = 0.;
      double velocity_sum = 0.;
      double acceleration_sum = 0.;

      motion_2.update(state_2.population, state_2.size);

      for (int i = 0; i != S; ++i) {
        position_sum += state_2.population.S[i].position.x;
        position_sum += state_2.population.S[i].position.y;

        displacement_sum += state_2.population.S[i].position.x -
                            previous_state.population.S[i].position.x;
        displacement_sum += state_2.population.S[i].position.y -
                            previous_state.population.S[i].position.y;

        velocity_sum += state_2.population.S[i].velocity.vx;
        velocity_sum += state_2.population.S[i].velocity.vy;

        acceleration_sum += state_2.population.S[i].velocity.vx -
                            previous_state.population.S[i].velocity.vx;
        acceleration_sum += state_2.population.S[i].velocity.vy -
                            previous_state.population.S[i].velocity.vy;
      }

      CHECK(position_sum / (2 * S) == doctest::Approx(size / 2).epsilon(1.));
      CHECK(displacement_sum / (2 * S) == doctest::Approx(0.).epsilon(1.));
      CHECK(velocity_sum / (2 * S) == doctest::Approx(0.).epsilon(1.));
      CHECK(acceleration_sum / (2 * S) == doctest::Approx(0.).epsilon(1.));
    }
  }
}