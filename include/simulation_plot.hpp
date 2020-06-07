#ifndef SIMULATION_PLOT_HPP
#define SIMULATION_PLOT_HPP

#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <iostream>
#include <vector>
#include "RQ_OBJECT.h"
#include "TLegend.h"
#include "TRootEmbeddedCanvas.h"
#include "TSystem.h"
#include "simulation.hpp"

class SimulationPlot
{
  RQ_OBJECT("SimulationPlot")
  Simulation_State const& state_;

  TApplication app_;
  TCanvas canvas_;
  TLegend legend_;

  TGraph S_graph_;
  TGraph I_graph_;
  TGraph R_graph_;
  TMultiGraph multi_graph_;

  void init_Graph(TGraph& graph, int color);
  void update_graphs();
  void update_canvas();

 public:
  SimulationPlot(Simulation_State const& state);

  void update();
  void fit();

  void run(bool return_type)
  {
    // run the application, returning from it when quitting Root
    app_.Run(return_type);
  }

  ~SimulationPlot()
  {
    // don't return from the application, but terminate it
    app_.SetReturnFromRun(false);
    app_.Terminate();
  }
};

#endif