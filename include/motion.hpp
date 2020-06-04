#ifndef MOTION_HPP
#define MOTION_HPP

#include <algorithm>
#include <random>
#include "SIR_population.hpp"

class G_Motion
{
 public:
  virtual void update(SIR_Population& population,
                      int const ticks,
                      int const size) = 0;
};

class Random_Motion : public G_Motion
{
  double mean_;
  double sd_;

  std::mt19937_64 gen_;
  std::normal_distribution<double> distribution_;

 public:
  Random_Motion(double mean = 0, double sd = 1)
      : mean_{mean}
      , sd_{sd}
      , gen_{std::random_device{}()}
      , distribution_{mean_, sd_}
  {
  }
  void update(SIR_Population& population,
              int const ticks,
              int const size) override
  {
    auto move = [&](Person& person) {
      // Accelerating
      person.velocity.vx += distribution_(gen_) - std::abs(person.velocity.vx) *
                                                      person.velocity.vx /
                                                      10000;
      person.velocity.vy += distribution_(gen_) - std::abs(person.velocity.vy) *
                                                      person.velocity.vy /
                                                      10000;
      // Updating position and checking borders
      person.position.x += person.velocity.vx;
      if (person.position.x > size || person.position.x < 0) {
        person.velocity.vx = -person.velocity.vx;
        person.position.x += person.velocity.vx;
      }
      person.position.y += person.velocity.vy;
      if (person.position.y > size || person.position.y < 0) {
        person.velocity.vy = -person.velocity.vy;
        person.position.y += person.velocity.vy;
      }
    };

    std::for_each(population.S.begin(), population.S.end(), move);
    std::for_each(population.I.begin(), population.I.end(), move);
    std::for_each(population.R.begin(), population.R.end(), move);
  }
};

#endif