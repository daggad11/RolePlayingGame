#include <SFML/Graphics.hpp>
#include "world.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG");
	sf::Clock clock;
	world world1(window.getSize().x/30);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else
				world1.handleEvent(event);
		}
		window.clear(sf::Color::Black);
		world1.update(clock.getElapsedTime().asSeconds());
		clock.restart();
		world1.draw(window);
		window.display();
	}
	return 0;
}