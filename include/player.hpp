#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <cmath>
#include "entity.hpp"

class player : public entity  {
public:
	player();
	void init(double xpos, double ypos, double mass, double width, double height);
	void draw(sf::RenderWindow &window);
	void animate();
	void update();
private:
	//body parts
	sf::CircleShape head;
	sf::RectangleShape torso;
	sf::RectangleShape rightArm;
	sf::RectangleShape leftArm;
	sf::RectangleShape rightLeg;
	sf::RectangleShape leftLeg;

	//animation bools
	bool rotdir;
};

#endif