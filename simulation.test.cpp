#include <iostream>
#include "doctest.h"
#include "simulation.hpp"

TEST_CASE("Testing evolution")
{
  // assert size_ > ls 0 should fail
  // Simulation{-10};
  Simulation sim2{10};
  Simulation sim3{10, SIRGroups{People(12), People(2), People(0)}};
  CHECK(sim2.size() == sim3.size());

  Simulation sim4(10, 101);
  auto S_group1 = sim4.get_sir_groups().S;
  CHECK(S_group1.size() == 100);
  std::cout << S_group1[0].position.x << ' ' << S_group1[0].velocity.vx << '\n';

  Simulation sim5(10, 100, 20, 1);
  auto S_group2 = sim5.get_sir_groups().S;
  CHECK(S_group1.size() == S_group2.size());
  std::cout << S_group2[0].position.x << ' ' << S_group2[0].velocity.vx << '\n';

  SIRGroups group{People{Person{1., 1.5, 2, 2}}, People(), People()};
  CHECK(Simulation(10, group).get_sir_groups().S[0].position.y == 1.5);

  SIRGroups group2{People{Person{11., -1.5, 2, 2}}, People(), People()};
  // assert check_everyone_position should fail
  // Simulation sim6(10, group2);
}