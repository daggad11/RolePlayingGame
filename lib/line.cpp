#include "line.hpp"

line::line(double x1, double y1, double x2, double y2) {
	points[0] = new sf::Vector2f(x1, y1);
	points[1] = new sf::Vector2f(x2, y2);
}

std::array<sf::Vector2f*, 2>  line::getPoints() {
	return points;
}

bool line::intersects(line otherline) {
	sf::Rect<double> rect1(points[0]->x, points[0]->y, (points[1]->x-points[0]->x), (points[1]->y-points[0]->y));
	sf::Rect<double> rect2(otherline.getPoints()[0]->x, otherline.getPoints()[0]->y, (otherline.getPoints()[1]->x-otherline.getPoints()[0]->x), (otherline.getPoints()[1]->y-otherline.getPoints()[0]->y));
	return rect1.intersects(rect2);
}
