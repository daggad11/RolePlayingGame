#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <cmath>
#include "entity.hpp"

class player : public entity  {
public:
	player();
	void init(double xpos, double ypos, double mass, double width, double height, float conv);
	void draw(sf::RenderWindow &window);
	void animate(double time);
	void update(double time);
protected:
	//body parts
	sf::CircleShape head;
	sf::RectangleShape torso;
	sf::RectangleShape rightArm;
	sf::RectangleShape leftArm;
	sf::RectangleShape rightLeg;
	sf::RectangleShape leftLeg;

	//animation variables
	double rotlimit;
	double rotconversion;
	bool rotdir;

	float conversion; //conversion rate from pixels to game units
};

#endif