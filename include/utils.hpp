#ifndef UTILS_HPP
#define UTILS_HPP
#include <cmath>
#include <SFML/Graphics.hpp>

namespace utils {	
	sf::Vertex* wrapIndex(std::vector<sf::Vertex*> vertices, int i);
	sf::Vector2f createVector(sf::Vertex* u, sf::Vertex* v);
  double getAngle(sf::Vector2f u, sf::Vector2f v);
	float getZProduct(sf::Vector2f u, sf::Vector2f v);
}

#endif 
