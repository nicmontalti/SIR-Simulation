#include "simulation.hpp"

int main(){
    Simulation<> simulation(10);
    Simulation_State const& state=simulation.evolve();
}
