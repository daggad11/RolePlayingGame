#include "utils.hpp"

sf::Vertex* utils::wrapIndex(std::vector<sf::Vertex*> vertices, int i)
{
	if (i >= vertices.size())
			i %=  vertices.size();
	return vertices[i];	
}
sf::Vector2f utils::createVector(sf::Vertex* u, sf::Vertex* v)
{
	sf::Vector2f resultant;
	resultant.x = v->position.x - u->position.x;
	resultant.y = v->position.y - u->position.y;
	return resultant;
}
double utils::getAngle(sf::Vector2f u, sf::Vector2f v)
{
	return acos((u.x*v.x + u.y*v.y)/(sqrt(u.x*u.x + u.y*u.y)*sqrt(v.x*v.x + v.y*v.y))); 
}
float utils::getZProduct(sf::Vector2f u, sf::Vector2f v)
{
	return u.x*v.y - v.x*u.y;
}