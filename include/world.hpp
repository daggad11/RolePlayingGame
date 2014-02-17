#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include "player.hpp"

class world {
public:
	world(float conv);
	void draw(sf::RenderWindow &window);
	void update(double time);
	void handleEvent(sf::Event &event);
private:
	std::vector<entity> entities;
	player player;
};

#endif