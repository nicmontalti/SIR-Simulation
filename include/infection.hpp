#ifndef SIR_INFECTION_HPP
#define SIR_INFECTION_HPP

#include "population.hpp"

namespace sir {

class G_Infection
{
 public:
  virtual void update(Population& population, int ticks) = 0;
};

}  // namespace sir

#endif