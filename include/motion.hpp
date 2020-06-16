#ifndef SIR_MOTION_HPP
#define SIR_MOTION_HPP

#include "population.hpp"

class G_Motion
{
 public:
  virtual void update(Population& population, int size) = 0;
};

#endif