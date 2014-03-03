#include "line.hpp"

line::line(double x1, double y1, double x2, double y2) {
	points[0] = new sf::Vector2f(x1, y1);
	points[1] = new sf::Vector2f(x2, y2);
}

line::line(p2t::Point* start, p2t::Point* end) {
	points[0] = new sf::Vector2f(start->x, start->y);
	points[1] = new sf::Vector2f(end->x, end->y);
}

std::array<sf::Vector2f*, 2>  line::getPoints() {
	return points;
}

bool line::intersects(line l) {
	std::array<sf::Vector2f*, 2> lPoints  = l.getPoints();
	double A1 = points[1]->y - points[0]->y;
	double B1 = points[0]->x - points[1]->x;
	double C1 = A1*points[0]->x + B1*points[0]->y;
	double A2 = lPoints[1]->y - lPoints[0]->y;
	double B2 = lPoints[0]->x - lPoints[1]->x;
	double C2 = A2*lPoints[0]->x + B2*lPoints[0]->y;


	double det =  A1*B2 - A2*B1;
	if (det == 0)
		return false;
	else	
	{
		double x = (B2*C1 - B1*C2)/det;
		double y = (A1*C2 - A2*C1)/det;
		if (std::min(points[0]->x, points[1]->x) <= x && std::max(points[0]->x, points[1]->x) >= x && std::min(points[0]->y, points[1]->y) <= y && std::max(points[0]->y, points[1]->y) >= y)
		{
			if (std::min(lPoints[0]->x, lPoints[1]->x) <= x && std::max(lPoints[0]->x, lPoints[1]->x) >= x && std::min(lPoints[0]->y, lPoints[1]->y) <= y && std::max(lPoints[0]->y, lPoints[1]->y) >= y)
				return true;
			else return false;
		}	
		else return false;

	}
}
