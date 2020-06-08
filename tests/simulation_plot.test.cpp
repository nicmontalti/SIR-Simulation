#include <chrono>
#include <iostream>
#include <thread>
#include "simulation.hpp"
#include "simulation_plot.hpp"

int main()
{
  Random_Motion motion;
  Simple_Infection infection(1, 1, 0.01);
  auto population = make_sir_population(400, 995, 5, 0);
  Simulation simulation(400, population, motion, infection);
  Simulation_Plot simplot(simulation.get_state());

  for (int i = 0; i < 2000; i++) {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now();
    simulation.evolve();
    simplot.update();
    std::this_thread::sleep_until(time + 20ms);
  }
}