#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG");
	sf::Clock clock;
	world world(window.getSize().x/20);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else
				world.handleEvent(event);
		}
		window.clear(sf::Color::Black);
		world.update(clock.getElapsedTime().asSeconds());
		clock.restart();
		world.draw(window);
		window.display();
	}
	return 0;
}