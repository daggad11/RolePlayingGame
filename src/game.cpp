#include <SFML/Graphics.hpp>
#include "world.hpp"
#include "player.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "RPG");
	player player1(1, 1, 10, 0.5, 1.8);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		player1.draw(window);
		window.display();
	}
	return 0;
}