#include <SFML/Graphics.hpp>
#include <cstdio>
#include "world.hpp"

int main(int argc, char *argv[]) {
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	sf::RenderWindow window(sf::VideoMode(width, height), "RPG");
	sf::Clock clock;
	world world1(window.getSize().x/30);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
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