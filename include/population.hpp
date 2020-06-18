#ifndef SIR_POPULATION_HPP
#define SIR_POPULATION_HPP

#include <cassert>
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

enum class Sub_Status {
  Sane,
  Incubation,
  Infective,
  Quarantined,
  Recovered,
  Dead
};

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

struct Simulation_State
{
  int const size;
  Population population;
  int ticks;

  Simulation_State(int i_size, Population i_population = Population{})
      : size{i_size}, population{i_population}, ticks{0}
  {
    assert(size > 0);
    assert(ticks >= 0);
  }
  Simulation_State(int i_size, int S, int I, int R);
};

#endif