#include "chunk.hpp"

chunk::chunk() {
	//todo
}

chunk::chunk(double width, double height)
{
	this->width = width;
	this->height = height;
}

void chunk::triangulate()
{
	std::vector<sf::Vertex*> copy;
	for (int i = 0; i < vertices.size(); i++)
			copy.push_back(&vertices[i])		
}

void chunk::draw(sf::RenderWindow &window) {
    //todo  	
} 


//generates a random chunk, with a fixed width and starting height (if set)
void chunk::generate()
{
	//todo: make a random world generator.
}
