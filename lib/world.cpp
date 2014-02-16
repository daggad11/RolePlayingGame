#include "world.hpp"

world::world() {
	player.init(1, 1, 1, .5, 1.8);
}

void world::draw(sf::RenderWindow &window) {
	player.draw(window);
}

void world::update() {
	player.update();
}