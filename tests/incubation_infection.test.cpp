#include <chrono>
#include <thread>
#include "display.hpp"
#include "incubation_infection.hpp"
#include "population.hpp"
#include "random_motion.hpp"
#include "simulation.hpp"

int constexpr size = 600;
int constexpr S = 200;
int constexpr I = 1;
int constexpr R = 0;
float constexpr infection_probability = 0.05f;
float constexpr mean_recovery_ticks = 200.f;
float constexpr sd_recovery_ticks = 20.f;
float constexpr circle_radius = 5.f;
int constexpr incubation_ticks = 100;
float constexpr quarantine_probability = 0.20f;

int main()
{
  Simulation_State state{size, S, I, R};
  Random_Motion motion{0.1};
  Incubation_Infection infection{2 * circle_radius,
                                 infection_probability,
                                 mean_recovery_ticks,
                                 sd_recovery_ticks,
                                 incubation_ticks,
                                 quarantine_probability};
  Simulation simulation{state, motion, infection};
  Display display{simulation.get_state(), circle_radius};

  while (display.is_open()) {
    display.update();
    simulation.evolve();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(25ms);
  }
}