#ifndef INFECTION_HPP
#define INFECTION_HPP

#include "SIR_population.hpp"

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
  Simple_Infection(SIR_population& SIR_population):G_Infection(SIR_population)
  {
  }

  void update(){}
};

#endif