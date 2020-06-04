#include "display.hpp"
#include <SFML/Graphics.hpp>

int constexpr window_border = 20;

Display::Display(Simulation_State const& state, float circle_radius)
    : state_{state}
    , circle_radius_{circle_radius}
    , circle_{circle_radius_}
    , borders_{sf::LinesStrip, 5}
    , window_(
          sf::VideoMode(state_.size + 2 * circle_radius_ + 2 * window_border,
                        state_.size + 2 * circle_radius_ + 2 * window_border),
          "SIR Simulation")
{
  assert(circle_.getRadius() == circle_radius_);
  int window_size = window_.getSize().x;

  borders_[0].position = sf::Vector2f(window_border, window_border);
  borders_[1].position =
      sf::Vector2f(window_size - window_border, window_border);
  borders_[2].position =
      sf::Vector2f(window_size - window_border, window_size - window_border);
  borders_[3].position =
      sf::Vector2f(window_border, window_size - window_border);
  borders_[4].position = sf::Vector2f(window_border, window_border);

  window_.clear(sf::Color::Black);
  update();
}

void Display::to_sfml(sf::CircleShape& circle)
{
  sf::Vector2f pos = circle.getPosition();
  pos += sf::Vector2f(window_border + circle_radius_,
                      window_border + circle_radius_);
  circle.setPosition(pos);
}

void Display::draw_borders()
{
  window_.draw(borders_);
}

void Display::draw_person(Person const& person, sf::Color const& color)
{
  circle_.setFillColor(color);
  circle_.setOrigin(sf::Vector2f(circle_radius_, circle_radius_));
  circle_.setPosition(person.position.x, person.position.y);
  to_sfml(circle_);
  window_.draw(circle_);
}

void Display::draw_people(People const& people)
{
  for (Person const& person : people) {
    switch (Sub_Status sub_status = person.sub_status) {
      case (Sub_Status::Sane):
        draw_person(person, sf::Color::Green);
        break;
      case (Sub_Status::Incubation):
        draw_person(person, sf::Color(255, 165, 0));  // Orange
        break;
      case (Sub_Status::Infective):
        draw_person(person, sf::Color::Red);
        break;
      case (Sub_Status::Recovered):
        draw_person(person, sf::Color::White);
        break;
      default:
        assert(false);
    }
  }
}

bool Display::update()
{
  if (window_.isOpen()) {
    window_.clear(sf::Color::Black);

    draw_borders();

    draw_people(state_.population.S);
    draw_people(state_.population.I);
    draw_people(state_.population.R);

    window_.display();

    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window_.close();
      }
    }
    return true;
  } else {
    return false;
  }
}