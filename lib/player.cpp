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
	
	this->xvel = 0;
	this->yvel = 0;
	this->accelright = false;
	this->accelleft = false;
	this->accelup = false;
	this->acceldown = false;

	this->mass = mass;
	this->width = width;
	this->height = height;
	
	this->conversion = conv;
	this->rotdir = 0;
	this->rotconversion = 250;
	this->rotlimit = 60;

	this->direction = LEFT;

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
	head.setPosition(xpos*conversion+width*conversion/2, ypos*conversion);
	rightArm.setPosition(xpos*conversion+width*conversion/2, ypos*conversion+head.getRadius()*2);
	rightLeg.setPosition(xpos*conversion+width*conversion/2, ypos*conversion+head.getRadius()*2+torso.getSize().y);
	torso.setPosition(xpos*conversion+width*conversion/2, ypos*conversion+head.getRadius()*2);
	leftArm.setPosition(xpos*conversion+width*conversion/2, ypos*conversion+head.getRadius()*2);
	leftLeg.setPosition(xpos*conversion+width*conversion/2, ypos*conversion+head.getRadius()*2+torso.getSize().y);
}

void player::animate(double time) {
	//limb animation
	if (accelright || accelleft) {
		if (rotdir == 0) {
			rightArm.setRotation(rightArm.getRotation()+time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()-time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()+time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()-time*rotconversion);
			if (abs(rightArm.getRotation() - rotlimit) <= 1)
				rotdir = 1;
		}
		else if (rotdir == 1) {
			rightArm.setRotation(rightArm.getRotation()-time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()+time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()-time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()+time*rotconversion);
			if (abs(leftArm.getRotation() - rotlimit) <= 1)
				rotdir = 0;
		}
	}
	else {
		if (rotdir == 0 && (rightArm.getRotation() > 1 && abs(rightArm.getRotation() - 360) > 1)) {
			rightArm.setRotation(rightArm.getRotation()+time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()-time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()+time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()-time*rotconversion);
			if (abs(rightArm.getRotation() - rotlimit) <= 1)
				rotdir = 1;
		}
		else if (rotdir == 1 && (leftArm.getRotation() > 1 && abs(leftArm.getRotation() - 360) > 1)) {
			rightArm.setRotation(rightArm.getRotation()-time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()+time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()-time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()+time*rotconversion);
			if (abs(leftArm.getRotation() - rotlimit) <= 1)
				rotdir = 0;
		}
	}
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

	//accelerating based off of forces
	xvel += netForce.x/mass*time;
	yvel+= netForce.y/mass*time;

	if (abs(xvel) > .1)
		xpos += xvel*time;
	if (abs(yvel) > .1)
		ypos += yvel*time;

	//reseting net forces
	netForce.x = 0;
	netForce.y = 0;

	view.setCenter(xpos*conversion, ypos*conversion); //centering view on player
}