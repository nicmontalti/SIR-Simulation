#include "doctest.h"
#include "population.hpp"
#include "simple_infection.hpp"

namespace sir {

bool operator==(Position const& left, Position const& right)
{
  return left.x == right.x && left.y == right.y;
}

bool operator!=(Position const& left, Position const& right)
{
  return !(left == right);
}

bool operator==(Velocity const& left, Velocity const& right)
{
  return left.vx == right.vx && left.vy == right.vy;
}

bool operator==(Person const& left, Person const& right)
{
  return left.position == right.position && left.velocity == right.velocity;
}

bool operator==(Population const& left, Population const& right)
{
  return left.S == right.S && left.I == right.I && left.R == right.R;
}

}  // namespace sir

using namespace sir;

TEST_CASE("Testing Simple_Infection")
{
  Person pers1 = {Position{1., 1.}, Velocity{0., 0.}};
  Person pers2 = {Position{5., 5.}, Velocity{0., 0.}};
  Person pers3 = {Position{5., 5.1}, Velocity{0., 0.}};
  pers3.sub_status = Sub_Status::Infective;
  pers3.ticks_of_infection = 0;
  pers3.ticks_of_recovery = 2;
  Person pers4 = {Position{5.1, 5.}, Velocity{0., 0.}};
  pers4.sub_status = Sub_Status::Recovered;
  pers4.ticks_of_infection = 0;
  pers4.ticks_of_recovery = 0;

  Population pop1 = {People{pers1, pers2}, People{pers3}, People{pers4}};
  Population pop2 = {People{pers2}, People{pers3}, People{pers4}};

  double constexpr limiting_distance = 1.;
  float constexpr infection_probability_s = 1.F;
  float constexpr mean_recovering_ticks_s = 1.F;
  float constexpr sd_recoverty_ticks_s = 1.f;

  Simple_Infection infection = {limiting_distance,
                                infection_probability_s,
                                mean_recovering_ticks_s,
                                sd_recoverty_ticks_s};

  infection.update(pop1, 1);
  infection.update(pop2, 1);
  SUBCASE("sane_to_infected")
  {
    CHECK(pop1 ==
          Population{People{pers1}, People{pers3, pers2}, People{pers4}});

    CHECK(pop2.S == People{});
    CHECK(pop2.I == People{pers3, pers2});
    CHECK(pop2.R == People{pers4});
  }

  SUBCASE("infected_to_recovered")
  {
    pop2.I.back().ticks_of_recovery = 4;

    infection.update(pop2, 2);
    CHECK(pop2.S.size() == 0);
    CHECK(pop2.I.size() == 1);
    CHECK(pop2.R == People{pers4, pers3});

    infection.update(pop2, 3);
    CHECK(pop2.S.size() == 0);
    CHECK(pop2.I.size() == 1);
    CHECK(pop2.R == People{pers4, pers3});

    infection.update(pop2, 4);
    CHECK(pop2.S.size() == 0);
    CHECK(pop2.I.size() == 0);
    CHECK(pop2.R == People{pers4, pers3, pers2});
  }
}