#ifndef INFECTION_HPP
#define INFECTION_HPP

#include "SIR_population.hpp"

class G_Infection {
protected:
  int const size_;
  SIR_Population &population_;
  unsigned int const &ticks_;

public:
  G_Infection(int const size, SIR_Population &population, unsigned int const &ticks)
      : size_{size}, population_{population}, ticks_{ticks} {}

  virtual void update() {}
};

class Simple_Infection : public G_Infection {
public:
  Simple_Infection(int const size, SIR_Population &population, unsigned int const &ticks)
      : G_Infection(size, population, ticks) {}

  void update() {}
};

#endif