#include "plot.hpp"
#include <TAxis.h>
#include <TFile.h>
#include <TSystem.h>
#include <fstream>

using namespace sir;

Plot::Plot(Simulation_State const& state)
    : state_{state}
    , app_{"", nullptr, nullptr}
    , canvas_{}
    , legend_{0.7, 0.75, 0.95, 0.95}
    , S_graph_{0}
    , I_graph_{0}
    , R_graph_{0}
    , multi_graph_{}
{
  // terminate application pressing x button
  app_.SetReturnFromRun(kFALSE);
  ((TRootCanvas*)canvas_.GetCanvasImp())
      ->Connect("CloseWindow()", "TApplication", &app_, "Terminate()");

  canvas_.SetTitle("SIR Simulation Plot");

  init_graph(S_graph_, kGreen);
  init_graph(I_graph_, kRed);
  init_graph(R_graph_, kBlue);

  multi_graph_.SetTitle("SIR Simulation; Ticks; People");

  multi_graph_.Add(&S_graph_);
  multi_graph_.Add(&I_graph_);
  multi_graph_.Add(&R_graph_);

  // drawing multigraph with axis (A) and points connected by a smooth line (C)
  multi_graph_.Draw("AC");

  legend_.AddEntry(&S_graph_, "Sane");
  legend_.AddEntry(&I_graph_, "Infected");
  legend_.AddEntry(&R_graph_, "Recovered");
  legend_.Draw();

  update();
}

void Plot::init_graph(TGraph& graph, int color)
{
  graph.SetLineWidth(2);
  graph.SetLineColor(color);
  graph.SetMarkerColor(color);
}

void Plot::update()
{
  int new_point_index = S_graph_.GetN();
  assert(new_point_index == I_graph_.GetN() &&
         new_point_index == R_graph_.GetN());

  S_graph_.SetPoint(new_point_index, state_.ticks, state_.population.S.size());
  I_graph_.SetPoint(new_point_index, state_.ticks, state_.population.I.size());
  R_graph_.SetPoint(new_point_index, state_.ticks, state_.population.R.size());

  multi_graph_.GetXaxis()->SetRange(0., state_.ticks);

  update_canvas();
}

void Plot::update_canvas()
{
  canvas_.Update();

  // process interactions with the application
  // (click, menu, close...)
  gSystem->ProcessEvents();
}

void Plot::save()
{
  TFile root_file("SIR_graph.root", "recreate");
  multi_graph_.Write();
  root_file.Close();

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