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
#include "player.hpp"
#include <iostream>

const bool LEFT = 0;
const bool RIGHT = 1;

player::player() {
	//todo
}

void player::init(double xpos, double ypos, double mass, double width, double height, float conv, sf::RenderWindow *window) {
	this->window = window;

	this->xpos = xpos;
	this->ypos = ypos;

	this->speed = 5;
	this->agility = 5;
	
	this->xvel = 0;
	this->yvel = 0;
	this->accelright = false;
	this->accelleft = false;
	this->accelup = false;
	this->acceldown = false;

	this->mass = mass;
	this->width = width;
	this->height = height;
	
	//animation variables
	rightArmTarget = 0;
	leftArmTarget = 0;
	rightLegTarget = 0;
	leftLegTarget = 0;
	rightArmDir = LEFT;
	leftArmDir = LEFT;
	rightLegDir = LEFT;
	leftLegDir = LEFT;
	wasMoving = false;
	this->rotMin = 220;
	this->rotMax = 270;
	this->rotSpeed = 0;
	this->rotAccel = 100;
	this->moving = false;

	//collision variables
	this->onground = false;
	this->uphill = false;
	this->obstructedRight = false;
	this->obstructedLeft = false;
	this->phasedHorizontal = false;
	this->direction = RIGHT;

	this->conversion = conv;
	//scaling bodyparts
	head.setRadius(height/6);
	torso.setSize(sf::Vector2f(4*width/5, height/3));
	rightArm.setSize(sf::Vector2f(width/2, height/3));
	leftArm.setSize(sf::Vector2f(width/2, height/3));
	rightLeg.setSize(sf::Vector2f(width/2, height/3));
	leftLeg.setSize(sf::Vector2f(width/2, height/3));

	//converting to pixels
	head.setRadius(head.getRadius()*conversion);
	torso.setSize(torso.getSize()*conversion);
	rightArm.setSize(rightArm.getSize()*conversion);
	leftArm.setSize(leftArm.getSize()*conversion);
	rightLeg.setSize(rightLeg.getSize()*conversion);
	leftLeg.setSize(leftLeg.getSize()*conversion);

	//setting center at middle/top of bodyparts
	head.setOrigin(head.getRadius(), 0);
	torso.setOrigin(torso.getSize().x/2, 0);
	rightArm.setOrigin(rightArm.getSize().x/2, 0);
	leftArm.setOrigin(leftArm.getSize().x/2, 0);
	rightLeg.setOrigin(rightLeg.getSize().x/2, 0);
	leftLeg.setOrigin(leftLeg.getSize().x/2, 0);

	//setting body parts colors
	head.setFillColor(sf::Color::Red);
	torso.setFillColor(sf::Color::Green);
	rightArm.setFillColor(sf::Color::Red);
	leftArm.setFillColor(sf::Color::Blue);
	rightLeg.setFillColor(sf::Color::Red);
	leftLeg.setFillColor(sf::Color::Blue);
}

void player::draw() {
	if (direction == LEFT) {
		window->draw(rightArm);
		window->draw(rightLeg);
	}
	else {
		window->draw(leftArm);
		window->draw(leftLeg);		
	}
	window->draw(torso);
	if (direction == RIGHT) {
		window->draw(rightArm);
		window->draw(rightLeg);
	}
	else {
		window->draw(leftArm);
		window->draw(leftLeg);		
	}
	window->draw(head);
	
	//positioning bodyparts
	head.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion));
	rightArm.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion-head.getRadius()*2));
	rightLeg.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion-head.getRadius()*2-torso.getSize().y));
	torso.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion-head.getRadius()*2));
	leftArm.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion-head.getRadius()*2));
	leftLeg.setPosition(xpos*conversion+width*conversion/2, window->getSize().y - (ypos*conversion-head.getRadius()*2-torso.getSize().y));
}

void player::animate(double time) {
	if (moving) {
		if (rotSpeed < rotMax)
			rotSpeed += rotAccel * time;
		if (!wasMoving) {
			rotSpeed = rotMin;
			if (accelright) {
				rightArmDir = LEFT;
				leftArmDir = RIGHT;
				rightLegDir = RIGHT;
				leftLegDir = LEFT;
				rightArmTarget = 60;
				leftArmTarget = 300;
				rightLegTarget = 300;
				leftLegTarget = 60;
			}
			if (accelleft) {
				rightArmDir = RIGHT;
				leftArmDir = LEFT;
				rightLegDir = LEFT;
				leftLegDir = RIGHT;
				rightArmTarget = 300;
				leftArmTarget = 60;
				rightLegTarget = 60;
				leftLegTarget = 300;
			}
			wasMoving = true;
		}
		else {
			if (abs(rightArm.getRotation()-rightArmTarget) < 0.1) {
				rightArmDir = !rightArmDir;
				leftArmDir = !leftArmDir;
				rightLegDir = !rightLegDir;
				leftLegDir = !leftLegDir;	
				rightArmTarget = 360 - rightArmTarget;
				leftArmTarget = 360 - leftArmTarget;
				rightLegTarget = 360 - rightLegTarget;
				leftLegTarget = 360 - leftLegTarget;
			}
		}
	}
	else {
		if (rotSpeed > rotMin)
			rotSpeed -= rotAccel * time;
		if (wasMoving) {
			rightArmTarget = 0;
			leftArmTarget = 0;
			rightLegTarget = 0;
			leftLegTarget = 0;

			if (rightArm.getRotation() <= 180)
				rightArmDir = RIGHT;
			else
				rightArmDir = LEFT;
			if (leftArm.getRotation() <= 180)
				leftArmDir = RIGHT;
			else
				leftArmDir = LEFT;
			if (rightLeg.getRotation() <= 180)
				rightLegDir = RIGHT;
			else
				rightLegDir = LEFT;
			if (leftLeg.getRotation() <= 180)
				leftLegDir = RIGHT;
			else
				leftLegDir = LEFT;
			wasMoving = false;
		}
	}

	if (rightArmDir == RIGHT && abs(rightArm.getRotation()-rightArmTarget) > 0.1)
		rightArm.rotate(-rotSpeed*time);
	else if (rightArmDir == LEFT && abs(rightArm.getRotation()-rightArmTarget) > 0.1)
		rightArm.rotate(rotSpeed*time);
	if (leftArmDir == RIGHT && abs(leftArm.getRotation()-leftArmTarget) > 0.1)
		leftArm.rotate(-rotSpeed*time);
	else if (abs(leftArm.getRotation()-leftArmTarget) > 0.1)
		leftArm.rotate(rotSpeed*time);
	if (rightLegDir == RIGHT && abs(rightLeg.getRotation()-rightLegTarget) > 0.1)
		rightLeg.rotate(-rotSpeed*time);
	else if (abs(rightLeg.getRotation()-rightLegTarget) > 0.1)
		rightLeg.rotate(rotSpeed*time);
	if (leftLegDir == RIGHT && abs(leftLeg.getRotation()-leftLegTarget) > 0.1)
		leftLeg.rotate(-rotSpeed*time);
	else if (abs(leftLeg.getRotation()-leftLegTarget) > 0.1)
		leftLeg.rotate(rotSpeed*time);
}

void player::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::D) {
			accelright = true;
			direction = RIGHT;
		}
		if (event.key.code == sf::Keyboard::A) {
			accelleft = true;
			direction = LEFT;
		}
		if (event.key.code == sf::Keyboard::W) {
			accelup = true;
		}
		if (event.key.code == sf::Keyboard::S) {
			acceldown = true;
		}
	}
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::D) {
			accelright = false;
		}
		if (event.key.code == sf::Keyboard::A) {
			accelleft = false;
		}
		if (event.key.code == sf::Keyboard::W) {
			accelup = false;
		}
		if (event.key.code == sf::Keyboard::S) {
			acceldown = false;
		}
	}
}

void player::update(double time, sf::View &view) {
	if (accelleft || accelright)
		moving = true;
	animate(time);

	//movement
	if (accelright && xvel < speed) 
		netForce.x += speed*3*mass;
	if (accelleft && xvel > -1*speed)
		netForce.x -= speed*3*mass;
	if (!accelright && xvel > 0)
		netForce.x -= speed*4*mass;
	if (!accelleft && xvel < 0)
		netForce.x += speed*4*mass;

	//applying normal force
	if (onground && not phasedHorizontal) {
		applyForce(sf::Vector2f(0, -yvel*mass/time));
	}

	//hill moving and obstruction
	if (uphill && !obstructedRight && !obstructedLeft) {;
		applyForce(sf::Vector2f(0, 1000));
	}

	if (obstructedRight && accelright) {
		applyForce(sf::Vector2f(-netForce.x, 0));
		xvel = -xvel;
	}
	if (obstructedLeft && accelleft) {
		applyForce(sf::Vector2f(-netForce.x, 0));
		xvel = -xvel;
	}

	//preventing phasing through walls
	if(phasedHorizontal)
		xvel = -xvel;

	//jumping
	if (accelup && abs(yvel) < 0.1 && (onground || uphill)) {
		netForce.y += agility*mass*(1/time);
	}

	//accelerating based off of forces
	xvel += netForce.x/mass*time;
	yvel += netForce.y/mass*time;


	if (abs(xvel) > .1)
		xpos += xvel*time;
	if (abs(yvel) > .1)
		ypos += yvel*time;

	//reseting net forces
	netForce.x = 0;
	netForce.y = 0;
	//reseting collision bools & animation bools
	onground = false; 
	uphill = false;
	obstructedRight = false;
	obstructedLeft = false;
	phasedHorizontal = false;
	moving = false;

	view.setCenter(xpos*conversion, window->getSize().y - (ypos*conversion)); //centering view on player
}

void player::collide(std::vector<line*> *lines) {
	double x1 = xpos + (width - torso.getSize().x/conversion)/2;
	double x2 = xpos + width - (width - torso.getSize().x/conversion)/2;
	double y1 = ypos;
	double y2 = ypos - height;
	line top(x1, y1, x2, y1);
	line bottom(x1, y2, x2, y2);
	line left(x1, y1, x1, y2);
	line right(x2, y1, x2, y2);

	for (auto line : *lines) {
			if (bottom.intersects(line))
			{
				if (top.intersects(line))
					phasedHorizontal = true;
				onground = true;
			}
			if (right.intersects(line))
			{
				if (right.getIntersect(line).y < ypos - 9/10*height)
					uphill = true;
				if (right.getIntersect(line).y > ypos - 9/10*height)
					obstructedRight = true;
			}
			if (left.intersects(line))
			{
				if (left.getIntersect(line).y < ypos - 9/10*height)
					uphill = true;
				if (right.getIntersect(line).y > ypos - 9/10*height)
					obstructedLeft = true;
			}
	}
}

void player::applyForce(sf::Vector2f force) {
	netForce += force;
}

//getters
double player::getMass() {
	return mass;
}
