#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class chunk {
public:
	chunk();
	void draw(sf::RenderWindow &window);
	void generate();
private:
	std::vector<sf::Vertex> vertices;
	double width;
	double height;
};

#endif