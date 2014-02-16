#include "player.hpp"

player::player() {
	//todo
}

void player::init(double xpos, double ypos, double mass, double width, double height) {
	this->xpos = xpos;
	this->ypos = ypos;
	this->xvel = 1;
	this->yvel = 0;
	this->mass = mass;
	this->width = width;
	this->height = height;
	this->rotdir = 0;

	head.setRadius(height/6);
	torso.setSize(sf::Vector2f(4*width/5, height/3));
	rightArm.setSize(sf::Vector2f(width/2, height/3));
	leftArm.setSize(sf::Vector2f(width/2, height/3));
	rightLeg.setSize(sf::Vector2f(width/2, height/3));
	leftLeg.setSize(sf::Vector2f(width/2, height/3));
}

void player::draw(sf::RenderWindow &window) {
	float conv = window.getSize().x/20;
	
	//converting to pixels
	head.setRadius(head.getRadius()*conv);
	torso.setSize(torso.getSize()*conv);
	rightArm.setSize(rightArm.getSize()*conv);
	leftArm.setSize(leftArm.getSize()*conv);
	rightLeg.setSize(rightLeg.getSize()*conv);
	leftLeg.setSize(leftLeg.getSize()*conv);

	//setting center at middle/top of bodyparts
	head.setOrigin(head.getRadius(), 0);
	torso.setOrigin(torso.getSize().x/2, 0);
	rightArm.setOrigin(rightArm.getSize().x/2, 0);
	leftArm.setOrigin(leftArm.getSize().x/2, 0);
	rightLeg.setOrigin(rightLeg.getSize().x/2, 0);
	leftLeg.setOrigin(leftLeg.getSize().x/2, 0);

	//positioning bodyparts
	head.setPosition(xpos*conv+width*conv/2, ypos*conv);
	rightArm.setPosition(xpos*conv+width*conv/2, ypos*conv+head.getRadius()*2);
	rightLeg.setPosition(xpos*conv+width*conv/2, ypos*conv+head.getRadius()*2+torso.getSize().y);
	torso.setPosition(xpos*conv+width*conv/2, ypos*conv+head.getRadius()*2);
	leftArm.setPosition(xpos*conv+width*conv/2, ypos*conv+head.getRadius()*2);
	leftLeg.setPosition(xpos*conv+width*conv/2, ypos*conv+head.getRadius()*2+torso.getSize().y);

	window.draw(head);
	window.draw(torso);
	window.draw(rightArm);
	window.draw(leftArm);
	window.draw(rightLeg);
	window.draw(leftLeg);

	//resizing bodyparts to meters
	head.setRadius(head.getRadius()/conv);
	torso.setSize(torso.getSize()/conv);
	rightArm.setSize(rightArm.getSize()/conv);
	leftArm.setSize(leftArm.getSize()/conv);
	rightLeg.setSize(rightLeg.getSize()/conv);
	leftLeg.setSize(leftLeg.getSize()/conv);
}

void player::animate() {
	if (xvel > 0) {
		//limb animations
		if (rotdir == 0) {
			rightArm.setRotation(rightArm.getRotation()+1);
			leftArm.setRotation(leftArm.getRotation()-1);
			rightLeg.setRotation(rightLeg.getRotation()+1);
			leftLeg.setRotation(leftLeg.getRotation()-1);
			if (abs(rightArm.getRotation() - 60) <= 1)
				rotdir = 1;
		}
		else if (rotdir == 1) {
			rightArm.setRotation(rightArm.getRotation()-1);
			leftArm.setRotation(leftArm.getRotation()+1);
			rightLeg.setRotation(rightLeg.getRotation()-1);
			leftLeg.setRotation(leftLeg.getRotation()+1);
			if (abs(leftArm.getRotation()-60) <= 1)
				rotdir = 0;
		} //end arm animations
	}
}

void player::update() {
	animate();
}