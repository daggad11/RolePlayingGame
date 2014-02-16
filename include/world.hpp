#ifndef WORLD_HPP
#define WORLD_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include "player.hpp"

class world {
public:
	void draw(sf::RenderWindow &window);
private:
	std::vector<entity> entities;
};

#endif