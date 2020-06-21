#ifndef SIR_MOTION_HPP
#define SIR_MOTION_HPP

#include "population.hpp"

namespace sir {

class G_Motion
{
 public:
  virtual void update(Population& population, int size) = 0;
};

}  // namespace sir

#endif