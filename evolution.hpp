#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

class Motion
{
  int a;

 public:
  Motion(int n = 0) : a{n}
  {
  }
};

class Infection
{
  int a;

 public:
  Infection(int n = 0) : a{n}
  {
  }
};

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

#endif