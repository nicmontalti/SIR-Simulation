#ifndef SIR_RANDOM_MOTION_HPP
#define SIR_RANDOM_MOTION_HPP

#include <TRandom.h>
#include "motion.hpp"

namespace sir {

class Random_Motion : public G_Motion
{
  double const sd_;
  TRandom random_generator_;

 public:
  Random_Motion(double sd = 0.1) : sd_{sd}, random_generator_{}
  {
    assert(sd_ >= 0);
    random_generator_.SetSeed();
  }
  void update(Population& population, int size) override;
};

}  // namespace sir

#endif