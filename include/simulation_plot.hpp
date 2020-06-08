#ifndef SIMULATION_PLOT_HPP
#define SIMULATION_PLOT_HPP

#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include "TLegend.h"
#include "TRootCanvas.h"
#include "simulation.hpp"

class Simulation_Plot
{
  Simulation_State const& state_;

  TApplication app_;
  TCanvas canvas_;
  TLegend legend_;

  TGraph S_graph_;
  TGraph I_graph_;
  TGraph R_graph_;
  TMultiGraph multi_graph_;

  void init_Graph(TGraph& graph, int color);
  void update_canvas();

 public:
  Simulation_Plot(Simulation_State const& state);
  ~Simulation_Plot()
  {
    //((TRootCanvas*)canvas_.GetCanvasImp())
    //  ->Connect("CloseWindow()", "TApplication", &app_, "Terminate()");
    // app_.Run(kFALSE);
    app_.SetReturnFromRun(kFALSE);
    app_.Terminate();
  }

  bool is_open()
  {
    return !app_.IsRunning();
  }

  void update();
  void fit();
  void save();
};

#endif