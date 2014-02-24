#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "../lib/poly2tri/poly2tri.h" 

class chunk {
public:
	chunk();
	chunk(float conversion);
	chunk(double width, double height);
	void draw(sf::RenderWindow &window);
	void generate();
	void triangulate();
	void setWidth(double width){this->width = width;};
	void setHeight(double height){this->height = height;};
	double getHeight(){return height;};
	double getWidth(){return width;};
private:
	std::vector<sf::Vertex*> triVerts;
	std::vector<p2t::Point*> polyLine;
	double width;
	double height;
	float conv;
};

#endif