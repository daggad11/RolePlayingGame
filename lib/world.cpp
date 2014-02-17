#include "world.hpp"

world::world(float conv) {
	player1.init(1, 1, 1, .5, 1.8, conv);
}

void world::draw(sf::RenderWindow &window) {
	player1.draw(window);
}

void world::update(double time) {
	player1.update(time);
}

void world::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::D) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::A) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::W) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::S) {
			player1.handleEvent(event);
		}
	}
}