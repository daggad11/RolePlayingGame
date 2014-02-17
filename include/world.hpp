#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "chunk.hpp"

class world {
public:
	world(float conv);
	void draw(sf::RenderWindow &window);
	void update(double time);
	void handleEvent(sf::Event &event);
private:
	std::vector<entity> entities;
	std::vector<chunk> chunks;
	player player1;
};

#endif