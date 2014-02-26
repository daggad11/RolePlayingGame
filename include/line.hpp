#ifndef LINE_HPP
#define LINE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class line {
public:
	line(double x1, double y1, double x2, double y2);
	std::array<sf::Vector2f*, 2> getPoints();
	bool intersects(line otherline);
private:
	std::array<sf::Vector2f*, 2> points;
};

#endif