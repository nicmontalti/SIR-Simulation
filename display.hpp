#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "simulation.hpp"

class Display
{
  Simulation_State const& state_;
  float const circle_radius_;
  sf::RenderWindow window_;

  void to_sfml(sf::CircleShape& circle);
  void draw_borders();
  void draw_person(Person const& person, sf::Color const& color);
  void draw_people(People const& people);

 public:
  Display(Simulation_State const& state, float const circle_radius);
  bool update();
};

#endif