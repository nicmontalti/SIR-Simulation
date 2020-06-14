#include <chrono>
#include <iostream>
#include <thread>
#include "display.hpp"
#include "incubation_infection.hpp"
#include "plot.hpp"
#include "population.hpp"
#include "random_motion.hpp"
#include "simulation.hpp"

int constexpr size = 600;
int constexpr S = 400;
int constexpr I = 10;
int constexpr R = 0;
float constexpr infection_probability = 0.05f;
float constexpr recovery_probability = 0.003f;
float constexpr circle_radius = 5.f;
int constexpr incubation_time = 100;
double constexpr motion_std = 0.1;

int main()
{
  Population population = init_state(size, S, I, R);
  Random_Motion motion{motion_std};
  Incubation_Infection infection{2 * circle_radius,
                                 infection_probability,
                                 recovery_probability,
                                 incubation_time};
  Simulation simulation{size, population, motion, infection};
  Plot simplot(simulation.get_state());
  Display display{simulation.get_state(), circle_radius};

  while (display.is_open()) {
    auto time = std::chrono::system_clock::now();

    simulation.evolve();

    display.update();
    if (simulation.get_state().ticks % 5 == 0) {
      simplot.update();
    }

    using namespace std::chrono_literals;
    std::this_thread::sleep_until(time + 25ms);
  }
  simplot.save();
  std::cout << "test" << '\n';
}