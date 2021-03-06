/* 
 * RolePlayingGame Copyright (c) 2014, RolePlayingGame Contributers
 * https://github.com/daggad11/RolePlayingGame
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of RolePlayingGame nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include <cmath>
#include "line.hpp"
#include "entity.hpp"

class player : public entity  {
public:
	player();
	void init(double xpos, double ypos, double mass, double width, double height, float conv, sf::RenderWindow *window);
	void draw();
	void animate(double time);
	void update(double time, sf::View &view);
	void handleEvent(sf::Event &event);
	void collide(std::vector<line*> *lines);
	void applyForce(sf::Vector2f force);

	//getters
	double getMass();
protected:
	sf::RenderWindow *window; //used for drawing

	//body parts
	sf::CircleShape head;
	sf::RectangleShape torso;
	sf::RectangleShape rightArm;
	sf::RectangleShape leftArm;
	sf::RectangleShape rightLeg;
	sf::RectangleShape leftLeg;

	//animation variables
	bool rightArmDir;
	bool leftArmDir;
	bool rightLegDir;
	bool leftLegDir;
	double rightArmTarget;
	double leftArmTarget;
	double rightLegTarget;
	double leftLegTarget;
	double rotSpeed;
	double rotMax;
	double rotMin;
	double rotAccel;
	bool moving;
	bool wasMoving;

	//collision varibles
	bool direction;
	bool onground;
	bool obstructedRight;
	bool obstructedLeft;
	bool phasedHorizontal;
	bool phasedVertical;

	float conversion; //conversion rate from pixels to game units

	//stats
	double speed;
	double agility;
};

#endif