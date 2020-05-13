#include "simulation.hpp"
#include <cassert>
#include <vector>

Simulation::Simulation(int size, Evolution const& evolution)
    : size_{size}
    , S_vector_(0)
    , I_vector_(0)
    , R_vector_(0)
    , evolution_{evolution}
{
  assert(size_ > 0);
}
Simulation::Simulation(
    int size, int S, int I, int R, Evolution const& evolution)
    : size_{size}
    , S_vector_(S)
    , I_vector_(I)
    , R_vector_(R)
    , evolution_{evolution}
{
  assert(size_ > 0);
}
Simulation::Simulation(int size, int N, Evolution const& evolution)
    : Simulation{size, N - 1, 1, 0, evolution}
{
  assert(size_ > 0);
  assert(S_vector_.size() + I_vector_.size() + R_vector_.size() == N);
}

int Simulation::size()
{
  return size_;
}
int Simulation::get_S_number()
{
  return S_vector_.size();
}
int Simulation::get_I_number()
{
  return I_vector_.size();
}
int Simulation::get_R_number()
{
  return R_vector_.size();
}