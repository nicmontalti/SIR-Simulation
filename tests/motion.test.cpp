#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <thread>
#include "SIR_population.hpp"
#include "motion.hpp"

class Display_Person
{
  sf::Color const color_;
  sf::RenderWindow& window_;

 public:
  Display_Person(sf::Color color, sf::RenderWindow& window)
      : color_{color}, window_{window}
  {
  }
  void operator()(Person person)
  {
    sf::CircleShape circle(10.f);
    circle.setFillColor(color_);
    circle.setPosition(person.position.x, person.position.y);
    window_.draw(circle);
  }
};

void display_population(SIR_Population& population, sf::RenderWindow& window)
{
  std::for_each(population.S.begin(),
                population.S.end(),
                Display_Person(sf::Color(0, 250, 0), window));
  std::for_each(population.I.begin(),
                population.I.end(),
                Display_Person(sf::Color(250, 0, 0), window));
  std::for_each(population.R.begin(),
                population.R.end(),
                Display_Person(sf::Color(0, 0, 250), window));
}

int main()
{
  int size = 800;
  SIR_Population population = make_sir_population(size, 50, 20, 0);
  int ticks = 0;
  Random_Motion motion{0.1};

  sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

  while (window.isOpen()) {
    using namespace std::chrono_literals;
    auto time = std::chrono::system_clock::now();

    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) window.close();
    }
    window.clear(sf::Color::Black);

    display_population(population, window);
    motion.update(population, ticks, size);

    window.display();
    std::this_thread::sleep_until(time + 20ms);
  }
}