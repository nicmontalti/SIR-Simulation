#include "population.hpp"
#include <TRandom.h>
#include <algorithm>
#include <cassert>
#include <vector>

void init_state(Simulation_State& state, int S, int I, int R)
{
  assert(S >= 0);
  assert(I >= 0);
  assert(R >= 0);

  class New_Person
  {
    int const size_;
    Sub_Status const sub_status_;
    TRandom random_gen_;

   public:
    New_Person(int size, Sub_Status sub_status)
        : size_{size}, sub_status_{sub_status}, random_gen_{}
    {
      random_gen_.SetSeed();
    }
    void operator(Person& person)()
    {
      double const x = random_gen_.Uniform(0., size_);
      double const y = random_gen_.Uniform(0., size_);
      person = Person{Position{x, y}, Velocity{0., 0.}, sub_status_};
    }
  };

  state.population = Population{People(S), People(I), People(R)};

  std::transform(state.population.S.begin(),
                 state.population.S.end(),
                 New_Person(state.size, Sub_Status::Sane));
  std::generate(state.population.I.begin(),
                state.population.I.end(),
                New_Person(state.size, Sub_Status::Infective));
  std::generate(state.population.R.begin(),
                state.population.R.end(),
                New_Person(state.size, Sub_Status::Recovered));
}