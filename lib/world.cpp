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