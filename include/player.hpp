#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "entity.hpp"

class player : public entity  {
public:
	player(double xpos, double ypos, double mass, double width, double height);
	void draw(sf::RenderWindow &window);
private:
	//body parts
	sf::CircleShape head;
	sf::RectangleShape torso;
	sf::RectangleShape rightArm;
	sf::RectangleShape leftArm;
	sf::RectangleShape rightLeg;
	sf::RectangleShape leftLeg;
};

#endif