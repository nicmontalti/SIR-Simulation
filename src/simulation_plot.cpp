#include "simulation_plot.hpp"

SimulationPlot::SimulationPlot(Simulation_State const& state)
    : state_{state}, app{"", NULL, NULL}
{
  canvas_.SetTitle("SIR Simulation");
  canvas_.SetWindowSize(1920, 1080);
  canvas_.Divide(2, 2);

  init_Graph(S_graph_, "Sane population", 3, 1);
  init_Graph(I_graph_, "Infected population", 2, 2);
  init_Graph(R_graph_, "Recovered population", 4, 3);

  update();
}

void SimulationPlot::init_Graph(TGraph& graph,
                                std::string const& title,
                                int color,
                                int padN)
{
  graph.SetTitle((title + ";Ticks;N").c_str());
  graph.SetLineWidth(2);
  graph.SetLineColor(color);
  graph.SetMarkerColor(color);

  canvas_.cd(padN);
  graph.Draw();
}

bool SimulationPlot::update()
{
  if (state_.ticks != 0 && state_.ticks <= ticks_axis_.back()) return false;

  ticks_axis_.push_back(state_.ticks);
  S_axis_.push_back(state_.population.S.size());
  I_axis_.push_back(state_.population.I.size());
  R_axis_.push_back(state_.population.R.size());

  S_graph_.SetPoint(S_graph_.GetN(), ticks_axis_.back(), S_axis_.back());
  I_graph_.SetPoint(I_graph_.GetN(), ticks_axis_.back(), I_axis_.back());
  R_graph_.SetPoint(R_graph_.GetN(), ticks_axis_.back(), R_axis_.back());

  for (int i = 1; i <= 3; i++) {
    canvas_.cd(i);
    canvas_.Update();
    canvas_.Pad()->Draw();
  }
}