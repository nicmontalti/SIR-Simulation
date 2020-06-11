#include "simulation_plot.hpp"
#include <TApplication.h>
#include <TAxis.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <TRootCanvas.h>
#include <TSystem.h>
#include <fstream>
#include "simulation.hpp"

Simulation_Plot::Simulation_Plot(Simulation_State const& state)
    : state_{state}
    , app_{"", nullptr, nullptr}
    , canvas_{}
    , legend_{0.7, 0.75, 0.95, 0.95}
    , S_graph_{0}
    , I_graph_{0}
    , R_graph_{0}
    , multi_graph_{}
{
  // app_.SetReturnFromRun(kTRUE);
  // terminate application by closing canvas (pressing on the 'x')
  // ((TRootCanvas*)canvas_.GetCanvasImp())
  //   ->Connect("CloseWindow()", "TApplication", &app_, "Terminate()");

  canvas_.SetTitle("SIR Simulation");

  // initializing graphs with different colors
  init_Graph(S_graph_, kGreen);
  init_Graph(I_graph_, kRed);
  init_Graph(R_graph_, kBlue);

  multi_graph_.SetTitle("SIR Simulation");

  // combining graphs in a multigraph
  multi_graph_.Add(&S_graph_);
  multi_graph_.Add(&I_graph_);
  multi_graph_.Add(&R_graph_);

  // drawing multigraph with axis (A) and points connected by a smooth line (C)
  multi_graph_.Draw("AC");

  // creating and drawing a legend
  legend_.AddEntry(&S_graph_, "Sane");
  legend_.AddEntry(&I_graph_, "Infected");
  legend_.AddEntry(&R_graph_, "Recovered");
  legend_.Draw();

  // adding starting values to graphs
  // updating canvas
  update();
}

void Simulation_Plot::init_Graph(TGraph& graph, int color)
{
  graph.SetLineWidth(2);
  graph.SetLineColor(color);
  graph.SetMarkerColor(color);
}

void Simulation_Plot::update()
{
  // adding a new point at the end of graphs
  int new_point_index = S_graph_.GetN();
  assert(new_point_index == I_graph_.GetN() &&
         new_point_index == R_graph_.GetN());

  S_graph_.SetPoint(new_point_index, state_.ticks, state_.population.S.size());
  I_graph_.SetPoint(new_point_index, state_.ticks, state_.population.I.size());
  R_graph_.SetPoint(new_point_index, state_.ticks, state_.population.R.size());

  // setting display range of x axis
  multi_graph_.GetXaxis()->SetRange(0., state_.ticks);

  update_canvas();
}

void Simulation_Plot::update_canvas()
{
  // updating canvas with new graphs
  canvas_.Update();

  // process interactions with the application
  // (click, menu, close...)
  gSystem->ProcessEvents();
}

void Simulation_Plot::fit()
{
  S_graph_.Fit("gaus");
  update_canvas();
}

void Simulation_Plot::save()
{
  // save graphs in a ROOT file
  TFile root_file("SIR_graph.root", "recreate");
  multi_graph_.Write();
  root_file.Close();

  // save SIR datas in a CSV file
  std::ofstream csv_file{"SIR_data.csv"};
  csv_file << "Ticks, Sane, Infected, Recovered\n";
  int N_points = S_graph_.GetN();
  for (int i = 0; i != N_points; ++i) {
    double x, y;
    S_graph_.GetPoint(i, x, y);
    csv_file << x << ',';
    csv_file << y << ',';
    I_graph_.GetPoint(i, x, y);
    csv_file << y << ',';
    R_graph_.GetPoint(i, x, y);
    csv_file << y << '\n';
  }
}