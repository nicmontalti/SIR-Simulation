#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

class Evolution
{
  int a;

 public:
  Evolution(int n = 0) : a{n}
  {
  }
};

struct Position
{
  double x;
  double y;
};

struct Person
{
  Position position;
};

#endif