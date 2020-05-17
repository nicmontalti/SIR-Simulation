#include <iostream>
#include "doctest.h"
#include "simulation.hpp"

TEST_CASE("Testing evolution")
{
  // assert size_ > ls 0 should fail
  // Simulation{-10};

  // assert is_base_of<G_Motion, Motion> should fail
  // Simulation<Second_Motion>{10};

  Simulation<> sim2{10};
  Simulation<G_Motion> sim3{10,
                            SIR_population{People(12), People(2), People(0)}};
  CHECK(sim2.size() == sim3.size());

  // Simulation<Simple_Infection> fails

  Simulation<Random_Motion, Simple_Infection> sim4(10, 101);
  auto S_people1 = sim4.get_population().S;
  CHECK(S_people1.size() == 100);
  std::cout << S_people1[0].position.x << S_people1[0].position.y << ' '
            << S_people1[0].velocity.vx << '\n';

  Simulation<> sim5(10, 100, 20, 1);
  auto S_people2 = sim5.get_population().S;
  CHECK(S_people1.size() == S_people2.size());
  std::cout << S_people2[0].position.x << ' ' << S_people2[0].velocity.vx
            << '\n';

  SIR_population population{People{Person{1., 1.5, 2, 2}}, People(), People()};
  CHECK(Simulation<>(10, population).get_population().S[0].position.y == 1.5);

  SIR_population people2{People{Person{11., -1.5, 2, 2}}, People(), People()};
  // assert check_everyone_position should fail
  // Simulation sim6(10, people2);
}