#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>

class entity {
public:
	entity(double xpos, double ypos, double mass, double width, double height);
	entity();
	virtual void draw(sf::RenderWindow &window);
protected:
	double xpos;
	double ypos;
	double xvel;
	double yvel;
	double mass;
	double width;
	double height;
};

#endif