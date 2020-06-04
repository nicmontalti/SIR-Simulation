#ifndef PERSON_HPP
#define PERSON_HPP

#include <vector>

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

enum class Sub_Status { Sane, Incubation, Infective, Recovered };

struct Person
{
  Position position;
  Velocity velocity;
  Sub_Status sub_status;
  int time_of_infection = 0;
  int time_of_recovery = 0;
};

using People = std::vector<Person>;

struct SIR_Population
{
  People S;
  People I;
  People R;
};

SIR_Population make_sir_population(int size, int S, int I, int R);

#endif