#ifndef SIR_PLOT_HPP
#define SIR_PLOT_HPP

#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TRootCanvas.h>
#include "TLegend.h"
#include "simulation.hpp"

class Plot
{
  Simulation_State const& state_;

  TApplication app_;
  TCanvas canvas_;
  TLegend legend_;

  TGraph S_graph_;
  TGraph I_graph_;
  TGraph R_graph_;
  TMultiGraph multi_graph_;

  void init_graph(TGraph& graph, int color);
  void update_canvas();

 public:
  Plot(Simulation_State const& state);
  ~Plot()
  {
    ((TRootCanvas*)canvas_.GetCanvasImp())
        ->Connect("CloseWindow()", "TApplication", &app_, "Terminate()");
    app_.Run(kFALSE);
    // app_.SetReturnFromRun(kTRUE);
    // app_.Terminate();
  }

  void update();
  void fit();
  void save();
};

#endif