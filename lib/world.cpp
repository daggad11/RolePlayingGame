#include "world.hpp"

world::world(float conv) {
	player.init(1, 1, 1, .5, 1.8, conv);
}

void world::draw(sf::RenderWindow &window) {
	player.draw(window);
}

void world::update(double time) {
	player.update(time);
}

void world::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::D) {
			player.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::A) {
			player.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::W) {
			player.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::S) {
			player.handleEvent(event);
		}
	}
}