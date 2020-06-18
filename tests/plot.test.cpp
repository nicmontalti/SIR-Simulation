#include <chrono>
#include <iostream>
#include <thread>
#include "plot.hpp"
#include "random_motion.hpp"
#include "simple_infection.hpp"
#include "simulation.hpp"

int main()
{
  Random_Motion motion;
  Simple_Infection infection(1, 1, 200.f, 20.f);
  Simulation_State state{600, 100, 10, 0};
  Simulation simulation(state, motion, infection);
  Plot simplot(simulation.get_state());

  for (int i = 0; i < 2000; i++) {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now();
    simulation.evolve();
    simplot.update();
    std::this_thread::sleep_until(time + 20ms);
  }
}