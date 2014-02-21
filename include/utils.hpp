#ifndef UTILS_HPP
#define UTILS_HPP

namespace utils {	
	sf::Vertex*  wrapIndex(std::vector<sf::Vertex*> vertices, int i);
	sf::Vector2f getVector(sf::Vertex* u, sf::Vertex* v);
  double getAngle(sf::Vector2f u, sf::Vector2f v);
	double getZProduct(sf::Vector2f u, sf::Vector2f v);
}

#endif 
