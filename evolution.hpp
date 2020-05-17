#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

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

struct SIR_Population
{
  People S;
  People I;
  People R;
};

struct Simulation_State
{
  SIR_Population population;
  unsigned int ticks;

  Simulation_State(SIR_Population i_population)
      : population{i_population}, ticks{0}
  {
  }
};

class G_Motion
{
 protected:
  int size_;
  SIR_Population& population_;
  unsigned int ticks_;

 public:
  G_Motion(int size, SIR_Population& SIR_population, unsigned int ticks)
      : size_{size}, population_{SIR_population}, ticks_{ticks}
  {
  }
  virtual void move()
  {
  }
};

class Random_Motion : public G_Motion
{
 public:
  Random_Motion(int size, SIR_Population& SIR_population, unsigned int ticks)
      : G_Motion(size, SIR_population, ticks)
  {
  }

  void move()
  {
  }
};

class Second_Motion
{
  int size_;
  SIR_Population& population_;

 public:
  Second_Motion(int size, SIR_Population& SIR_population)
      : size_{size}, population_{SIR_population}
  {
  }

  void move()
  {
  }
};

class G_Infection
{
 protected:
  int size_;
  SIR_Population& population_;
  unsigned int ticks_;

 public:
  G_Infection(int size, SIR_Population& SIR_population, unsigned int ticks)
      : size_{size}, population_{SIR_population}, ticks_{ticks}
  {
  }
  virtual void update()
  {
  }
};

class Simple_Infection : public G_Infection
{
 public:
  Simple_Infection(int size, SIR_Population& SIR_population, unsigned int ticks)
      : G_Infection(size, SIR_population, ticks)
  {
  }

  void update()
  {
  }
};
#endif