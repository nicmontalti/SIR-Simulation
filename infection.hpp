#ifndef INFECTION_HPP
#define INFECTION_HPP

#include "SIR_population.hpp"

class G_Infection
{
 protected:
  int const size_;
  SIR_Population& population_;
  unsigned int const& ticks_;

 public:
  virtual void update()
  {
  }
};

class Simple_Infection : public G_Infection
{
 public:
  void update()
  {
  }
};

#endif