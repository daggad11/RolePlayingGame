#include "entity.hpp"

entity::entity() {
	//todo
}

entity::entity(double xpos, double ypos, double mass, double width, double height) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->xvel = 0;
	this->yvel = 0;
	this->mass = mass;
	this->width = width;
	this->height = height;
}

void entity::draw(sf::RenderWindow &window) {
	//todo
}