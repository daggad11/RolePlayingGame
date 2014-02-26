#include "line.hpp"

line::line(double x1, double y1, double x2, double y2) {
	points[0] = new sf::Vector2f(x1, y1);
	points[1] = new sf::Vector2f(x2, y2);
}

std::array<sf::Vector2f*, 2>  line::getPoints() {
	return points;
}

bool line::intersects(line l) {
	std::array<sf::Vector2f*, 2> lPoints  = l.getPoints();
	double denominator = ((points[0]->x - points[1]->x)*(lPoints[0]->y - lPoints[1]->y)) - ((points[0]->y - points[1]->y) - (lPoints[0]->x, lPoints[1]->x));
	if (denominator == 0)
		return false;
	else	
	{
		return true;
		double xDterm = ((points[0]->x*points[1]->y - points[0]->y*points[0]->x)*(lPoints[0]->x - lPoints[1]->x)) - ((points[0]->x - points[1]->x)*(lPoints[0]->x*lPoints[1]->y - lPoints[0]->y*lPoints[0]->x));
		double yDterm = ((points[0]->x*points[1]->y - points[0]->y*points[0]->x)*(lPoints[0]->y - lPoints[1]->y)) - ((points[0]->y - points[1]->y)*(lPoints[0]->x*lPoints[1]->y - lPoints[0]->y*lPoints[0]->x)); 
	}
}
