#ifndef LINE_HPP
#define LINE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <poly2tri.h>

class line {
public:
	line(double x1, double y1, double x2, double y2);
	line(p2t::Point* start, p2t::Point* end);
	std::array<sf::Vector2f*, 2> getPoints();
	sf::Vector2f getIntersect(line* otherLine); //this can ONLY be used if intersects(line* l) has already been called.
	bool intersects(line* l);
private:
	std::array<sf::Vector2f*, 2> points;
	line* other;
	double xIntersect;
	double yIntersect;
};

#endif