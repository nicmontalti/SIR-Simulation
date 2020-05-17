#ifndef MOTION_HPP
#define MOTION_HPP

#include "SIR_population.hpp"

class G_Motion {
protected:
  int const size_;
  SIR_Population &population_;
  unsigned int const &ticks_;

public:
  G_Motion(int const size, SIR_Population &population, unsigned int const &ticks)
      : size_{size}, population_{population}, ticks_{ticks} {}

  virtual void move() {}
};

class Random_Motion : public G_Motion {
public:
  Random_Motion(int const size, SIR_Population &population, unsigned int const &ticks)
      : G_Motion(size, population, ticks) {}

  void move() {}
};

#endif