#include "player.hpp"
#include <iostream>

player::player() {
	//todo
}

void player::init(double xpos, double ypos, double mass, double width, double height, float conv) {
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
	this->rotconversion = 200;
	this->rotlimit = 60;

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
}

void player::draw(sf::RenderWindow &window) {
	window.draw(head);
	window.draw(torso);
	window.draw(rightArm);
	window.draw(leftArm);
	window.draw(rightLeg);
	window.draw(leftLeg);

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
		if (rotdir == 0 && rightArm.getRotation() > 1) {
			rightArm.setRotation(rightArm.getRotation()+time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()-time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()+time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()-time*rotconversion);
			if (abs(rightArm.getRotation() - rotlimit) <= 1)
				rotdir = 1;
		}
		else if (rotdir == 1 && leftArm.getRotation() > 1) {
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
		}
		if (event.key.code == sf::Keyboard::A) {
			accelleft = true;
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

void player::update(double time) {
	animate(time);


	//movement
	if (accelright && xvel < speed)
		xvel += speed*time;
	if (accelleft && xvel > -1*speed)
		xvel -= speed*time;
	if (!accelright && xvel > 0)
		xvel -= speed*4*time;
	if (!accelleft && xvel < 0)
		xvel += speed*4*time;

	if (xvel != 0) 
		xpos += xvel*time;
}