#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "RPG");
	world world;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		world.update();
		world.draw(window);
		window.display();
	}
	return 0;
}