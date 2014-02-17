#include "player.hpp"

player::player() {
	//todo
}

void player::init(double xpos, double ypos, double mass, double width, double height, float conv) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->xvel = 1;
	this->yvel = 0;
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
	if (xvel > 0) {
		//limb animations
		if (rotdir == 0) {
			rightArm.setRotation(rightArm.getRotation()+xvel*time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()-xvel*time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()+xvel*time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()-xvel*time*rotconversion);
			if (abs(rightArm.getRotation() - rotlimit) <= 1)
				rotdir = 1;
		}
		else if (rotdir == 1) {
			rightArm.setRotation(rightArm.getRotation()-xvel*time*rotconversion);
			leftArm.setRotation(leftArm.getRotation()+xvel*time*rotconversion);
			rightLeg.setRotation(rightLeg.getRotation()-xvel*time*rotconversion);
			leftLeg.setRotation(leftLeg.getRotation()+xvel*time*rotconversion);
			if (abs(leftArm.getRotation() - rotlimit) <= 1)
				rotdir = 0;
		} //end arm animations
	}
}

void player::update(double time) {
	animate(time);
}