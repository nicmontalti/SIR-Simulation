#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "SIR_population.hpp"
#include "motion.hpp"
#include "infection.hpp"

template<class Motion = Random_Motion, class Infection = Simple_Infection>
class Simulation{
    SIR_population population_;
    
    Motion motion;
    Infection infection;

    bool check_everyone_position();

    public:
    Simulation(): motion{population_}, infection{population_}{}

    void evolve(int ticks){}
};

#endif