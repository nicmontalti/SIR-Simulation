#include "doctest.h"
#include "incubation_infection.hpp"
#include "population.hpp"

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

inline bool operator==(Population const& left, Population const& right)
{
  return left.S == right.S && left.I == right.I && left.R == right.R;
}

TEST_CASE("Testing Incubation_infection")
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

  double constexpr limiting_distance = 1.;
  float constexpr infection_probability = 1.f;
  float constexpr mean_recovery_ticks = 1.f;
  float constexpr sd_recovery_ticks = 1.f;

  int constexpr incubation_ticks = 1;
  float constexpr quarantine_probability1 = 0.f;
  float constexpr quarantine_probability2 = 1.f;

  Incubation_Infection infection1{limiting_distance,
                                  infection_probability,
                                  mean_recovery_ticks,
                                  sd_recovery_ticks,
                                  incubation_ticks,
                                  quarantine_probability1};

  Incubation_Infection infection2{limiting_distance,
                                  infection_probability,
                                  mean_recovery_ticks,
                                  sd_recovery_ticks,
                                  incubation_ticks,
                                  quarantine_probability2};

  infection1.update(pop1, 1);
  SUBCASE("sane_to_infected")
  {
    CHECK(pop1 ==
          Population{People{pers1}, People{pers3, pers2}, People{pers4}});
    CHECK(pop1.I.back().sub_status == Sub_Status::Incubation);
  }

  SUBCASE("infected_to_recovered (no quarantine)")
  {
    pop1.I.back().ticks_of_recovery = 4;

    infection1.update(pop1, 2);
    CHECK(pop1 ==
          Population{People{pers1}, People{pers2}, People{pers4, pers3}});
    CHECK(pop1.I.back().sub_status == Sub_Status::Infective);
    CHECK(pop1.R.back().sub_status == Sub_Status::Recovered);

    infection1.update(pop1, 3);
    CHECK(pop1 ==
          Population{People{pers1}, People{pers2}, People{pers4, pers3}});

    infection1.update(pop1, 4);
    CHECK(pop1 ==
          Population{People{pers1}, People{}, People{pers4, pers3, pers2}});
  }

  SUBCASE("infected_to_recovered (with quarantine)")
  {
    pop1.I.back().ticks_of_recovery = 4;

    infection2.update(pop1, 2);
    CHECK(pop1 ==
          Population{People{pers1}, People{pers2}, People{pers4, pers3}});
    CHECK(pop1.I.back().sub_status == Sub_Status::Quarantined);
    CHECK(pop1.R.back().sub_status == Sub_Status::Recovered);

    infection2.update(pop1, 3);
    CHECK(pop1 ==
          Population{People{pers1}, People{pers2}, People{pers4, pers3}});
    CHECK(pop1.I.back().sub_status == Sub_Status::Quarantined);
    CHECK(pop1.R.back().sub_status == Sub_Status::Recovered);

    infection2.update(pop1, 4);
    CHECK(pop1 ==
          Population{People{pers1}, People{}, People{pers4, pers3, pers2}});
    CHECK(pop1.R[1].sub_status == Sub_Status::Recovered);
    CHECK(pop1.R[2].sub_status == Sub_Status::Recovered);
  }
}