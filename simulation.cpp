#include "simulation.hpp"
#include <cassert>
#include <vector>

Simulation::Simulation(int size, Evolution const& evolution)
    : size_{size}
    , evolution_{evolution}
    , S_vector_(0)
    , I_vector_(0)
    , R_vector_(0)
{
  assert(size_ > 0);
}
Simulation::Simulation(int size, int N, Evolution const& evolution)
    : size_{size}
    , evolution_{evolution}
    , S_vector_(N - 1)
    , I_vector_(1)
    , R_vector_(0)
{
  assert(size_ > 0);
  assert(N > 0);
  assert(S_vector_.size() + I_vector_.size() + R_vector_.size() == N);
}

Simulation::Simulation(
    int size, int S, int I, int R, Evolution const& evolution)
    : size_{size}
    , evolution_{evolution}
    , S_vector_(S)
    , I_vector_(I)
    , R_vector_(R)
{
  assert(size_ > 0);
  assert(S > 0);
  assert(I > 0);
  assert(R > 0);
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