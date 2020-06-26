#include "random_motion.hpp"
#include <algorithm>

using namespace sir;

void Random_Motion::update(Population& population, int size)
{
  auto move = [&](Person& person) {
    person.velocity.vx += random_generator_.Gaus(0., sd_);
    person.velocity.vy += random_generator_.Gaus(0., sd_);

    person.position.x += person.velocity.vx;
    person.position.y += person.velocity.vy;

    if (person.position.x > size || person.position.x < 0) {
      person.velocity.vx = -person.velocity.vx;
      person.position.x += person.velocity.vx;
    }
    if (person.position.y > size || person.position.y < 0) {
      person.velocity.vy = -person.velocity.vy;
      person.position.y += person.velocity.vy;
    }
  };

  std::for_each(population.S.begin(), population.S.end(), move);
  std::for_each(population.I.begin(), population.I.end(), move);
  std::for_each(population.R.begin(), population.R.end(), move);
}