#include <chrono>
#include <thread>
#include "display.hpp"
#include "population.hpp"
#include "random_motion.hpp"
#include "simple_infection.hpp"
#include "simulation.hpp"

int constexpr size = 600;
int constexpr S = 200;
int constexpr I = 1;
int constexpr R = 0;
float constexpr infection_probability = 0.05f;
float constexpr recovery_probability = 0.001f;
float constexpr circle_radius = 5.f;

int main()
{
  Population population = init_state(size, S, I, R);
  Random_Motion motion{0.1};
  Simple_Infection infection{
      2 * circle_radius, infection_probability, recovery_probability};
  Simulation simulation{size, population, motion, infection};
  Display display{simulation.get_state(), circle_radius};

  while (display.is_open()) {
    simulation.evolve();
    display.update();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(25ms);
  }
}