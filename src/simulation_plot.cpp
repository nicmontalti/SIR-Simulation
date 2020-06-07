#include "simulation_plot.hpp"
#include <iostream>
#include <vector>
#include "TQObject.h"
#include "TRootCanvas.h"
#include "TSystem.h"

SimulationPlot::SimulationPlot(Simulation_State const& state)
    : state_{state}
    , app_{"", nullptr, nullptr}
    , canvas_{}
    , legend_{0.7, 0.75, 0.95, 0.95}
    , S_graph_{}
    , I_graph_{}
    , R_graph_{1000}
    , multi_graph_{}
{
  // TQObject::Connect(
  // "TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");
  canvas_.SetTitle("SIR Simulation");

  init_Graph(S_graph_, kGreen);
  init_Graph(I_graph_, kRed);
  init_Graph(R_graph_, kBlue);

  multi_graph_.SetTitle("SIR Simulation");

  multi_graph_.Add(&S_graph_);
  multi_graph_.Add(&I_graph_);
  multi_graph_.Add(&R_graph_);

  // draw multiple graph with axis and points connected by a smooth line
  multi_graph_.Draw("AC");

  legend_.SetHeader("Legend", "C");
  legend_.AddEntry(&S_graph_, "Sane");
  legend_.AddEntry(&I_graph_, "Infected");
  legend_.AddEntry(&R_graph_, "Recovered");
  legend_.Draw();

  update();
}

void SimulationPlot::init_Graph(TGraph& graph, int color)
{
  graph.SetLineWidth(2);
  graph.SetLineColor(color);
  graph.SetMarkerColor(color);
}

void SimulationPlot::update_graphs()
{
  S_graph_.SetPoint(S_graph_.GetN(), state_.ticks, state_.population.S.size());
  I_graph_.SetPoint(I_graph_.GetN(), state_.ticks, state_.population.I.size());
  R_graph_.SetPoint(R_graph_.GetN(), state_.ticks, state_.population.R.size());
}

void SimulationPlot::update_canvas()
{
  canvas_.cd();
  canvas_.Update();
  canvas_.Pad()->Draw();
  gSystem->ProcessEvents();
}

void SimulationPlot::fit()
{
  S_graph_.Fit("gaus");
  update_canvas();
}

void SimulationPlot::update()
{
  update_graphs();
  update_canvas();
}
