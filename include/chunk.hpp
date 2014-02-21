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
	void setWidth(double width);
	void setHeight(double height);
	double getHeight();
	double getWidth();
private:
	std::vector<sf::Vertex> vertices;
	double width;
	double height;
};

#endif