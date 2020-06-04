#ifndef SIMULATION_PLOT_HPP
#define SIMULATION_PLOT_HPP

#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <vector>
#include "simulation.hpp"

class SimulationPlot
{
  Simulation_State const& state_;

  std::vector<int> S_axis_;
  std::vector<int> I_axis_;
  std::vector<int> R_axis_;
  std::vector<int> ticks_axis_;

  TApplication app;
  TCanvas canvas_;

  TGraph S_graph_;
  TGraph I_graph_;
  TGraph R_graph_;

  void init_Graph(TGraph& graph, std::string const& title, int color, int padN);

 public:
  SimulationPlot(Simulation_State const& state);

  bool update();

  ~SimulationPlot()
  {
    app.Terminate();
  }
};

#endif