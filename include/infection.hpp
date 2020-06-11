#ifndef SIR_INFECTION_HPP
#define SIR_INFECTION_HPP

#include "population.hpp"

class G_Infection
{
 public:
  void virtual update(Population&, int ticks) = 0;
};

#endif