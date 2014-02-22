#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class chunk {
public:
	chunk();
	chunk(double width, double height);
	void draw(sf::RenderWindow &window);
	void generate();
	void triangulate();
	void setWidth(double width){this->width = width;};
	void setHeight(double height){this->height = height;};
	double getHeight(){return height;};
	double getWidth(){return width;};
private:
	std::vector<sf::Vertex*> triVertices;
	std::vector<sf::Vertex> vertices;
	double width;
	double height;
};

#endif