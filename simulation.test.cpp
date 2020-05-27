#include <iostream>
#include "doctest.h"
#include "simulation.hpp"

int constexpr ticks_frequency = 10;
double constexpr limiting_distance = 1.;

int constexpr size = 20;
int constexpr S = 10;
int constexpr I = 3;
int constexpr R = 5;

float constexpr infection_probability = 0.F;
float constexpr recovering_probability = 0.F;

TEST_CASE("Testing simulation")
{
  Random_Motion motion{};
  Simple_Infection infection = {ticks_frequency,
                                limiting_distance,
                                infection_probability,
                                recovering_probability};
  auto population = make_sir_population(size, S, I, R);

  // assert size_ > ls 0 should fail
  // Simulation{-10, population, motion, infection};

  Simulation sim_1{size, population, motion, infection};
  Simulation sim_2{size, make_sir_population(size, 1, 0, 0), motion, infection};
  CHECK(sim_1.size() == sim_2.size());

  SIR_Population population_2{
      People{Person{1., 1.5, 2, 2}}, People(), People()};
  CHECK(Simulation(size, population_2, motion, infection)
            .get_state()
            .population.S[0]
            .position.y == 1.5);

  SIR_Population population_3{
      People{Person{11., -1.5, 2, 2}}, People(), People()};

  // assert check_everyone_position should fail
  // Simulation sim_3(10, population_3, motion, infection);

  auto& state = sim_2.evolve();
  auto& state2 = sim_2.get_state();

  // state and state2 should be const&
  // state = Simulation_State{SIR_Population{}};
  // state2 = Simulation_State{SIR_Population{}};
}