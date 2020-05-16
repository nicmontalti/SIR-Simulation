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

struct Person
{
  Position position;
  Velocity velocity;
};

using People = std::vector<Person>;

struct SIR_population
{
  People S;
  People I;
  People R;
};

#endif