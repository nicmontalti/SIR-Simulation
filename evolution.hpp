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

struct SIR_population
{
  People S;
  People I;
  People R;
};

class G_Motion
{
 protected:
  int size_;
  SIR_population& population_;

 public:
  G_Motion(int size, SIR_population& SIR_population)
      : size_{size}, population_{SIR_population}
  {
  }
  virtual void move()
  {
  }
};

class Random_Motion : public G_Motion
{
 public:
  Random_Motion(int size, SIR_population& SIR_population)
      : G_Motion(size, SIR_population)
  {
  }

  void move()
  {
  }
};

class Second_Motion : public G_Motion
{
 public:
  Second_Motion(int size, SIR_population& SIR_population)
      : G_Motion(size, SIR_population)
  {
  }

  void move()
  {
  }
};

class G_Infection
{
 protected:
  SIR_population& population_;

 public:
  G_Infection(SIR_population& SIR_population) : population_{SIR_population}
  {
  }
  virtual void update()
  {
  }
};

class Simple_Infection : public G_Infection
{
 public:
  Simple_Infection(SIR_population& SIR_population) : G_Infection(SIR_population)
  {
  }

  void update()
  {
  }
};
#endif