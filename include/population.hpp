#ifndef SIR_POPULATION_HPP
#define SIR_POPULATION_HPP

#include <cassert>
#include <vector>

namespace sir {

struct Position
{
  double x;
  double y;
};

struct Velocity
{
  double vx;
  double vy;
};

enum class Sub_Status { Sane, Incubation, Infective, Quarantined, Recovered };

struct Person
{
  Position position;
  Velocity velocity;
  Sub_Status sub_status = Sub_Status::Sane;
  int ticks_of_infection = 0;
  int ticks_of_recovery = 0;
};

using People = std::vector<Person>;

struct Population
{
  People S;
  People I;
  People R;
};

}  // namespace sir

#endif