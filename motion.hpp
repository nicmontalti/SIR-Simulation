#ifndef MOTION_HPP
#define MOTION_HPP

#include "SIR_population.hpp"

class G_Motion
{
 protected:
  SIR_population& population_;
 public:
  G_Motion(SIR_population& SIR_population) : population_{SIR_population}
  {
  }
  virtual void move()
  {
  }
};

class Random_Motion : public G_Motion
{
 public:
  Random_Motion(SIR_population& SIR_population):G_Motion(SIR_population)
  {
  }

  void move(){}
};

#endif