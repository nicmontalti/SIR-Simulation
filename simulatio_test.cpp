#include "doctest.h"
#include "simulation.hpp"

TEST_CASE("Testing evolution")
{
  // Simulation{-10};
  Simulation sim2{10};
  Simulation sim3{10, 12};
  CHECK(sim2.size() == sim3.size());
  Simulation{10, -2};
  CHECK(sim2.get_S_number() == 0);
  CHECK(sim2.get_I_number() == 0);
  CHECK(sim2.get_R_number() == 0);
  CHECK(sim3.get_S_number() == 11);
  CHECK(sim3.get_I_number() == 1);
  CHECK(sim3.get_R_number() == 0);
}