#include "chunk.hpp"

chunk::chunk() {
	//default constructor
}

chunk::chunk(float conversion)
{

}

chunk::chunk(double width, double height)
{
	this->width = width;
	this->height = height;
}

void chunk::triangulate()
{
	p2t::SweepContext polygon(polyLine); //context for sweep in order to triangulate
	p2t::Sweep s; //instance to triangulate polygon
	s.Triangulate(polygon); //triangles generated here
	for (int i = 0; i < polygon.GetTriangles().size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p2t::Point* p = polygon.GetTriangles()[i]->GetPoint(j);
			sf::Vertex* vert = new sf::Vertex(sf::Vector2f(p->x, p->y), sf::Vector2f(p->x, p->y));
			triVerts.push_back(vert);
		}
	}		
}

void chunk::draw(sf::RenderWindow &window) {
	std::vector<sf::Vertex*> scaled; //maybe the conversion should be done either once (make a converted list as a member) or in a function for ease of use...
	for (int i = 0; i < triVerts.size(); i++)
	{
		sf::Vertex* v = new sf::Vertex(sf::Vector2f(triVerts[i]->position.x*conv, triVerts[i]->position.y*conv), sf::Color::White, sf::Vector2f(triVerts[i]->position.x*conv, triVerts[i]->position.y*conv));
		scaled.push_back(v);
	}

    window.draw(scaled[0], scaled.size(), sf::Triangles);
} 


//generates a random chunk, with a fixed width and starting height (if set)
void chunk::generate()
{
	//todo: make a random world generator.
	//test points
	polyLine.push_back(new p2t::Point(10.0, 0.0));
	polyLine.push_back(new p2t::Point(9.0, 1.0));
	polyLine.push_back(new p2t::Point(8.0, 5.0));
	polyLine.push_back(new p2t::Point(7.0, 6.0));
	polyLine.push_back(new p2t::Point(6.0, 4.0));
	polyLine.push_back(new p2t::Point(5.0, 2.0));
	polyLine.push_back(new p2t::Point(4.0, 3.0));
	polyLine.push_back(new p2t::Point(3.0, 5.0));
	polyLine.push_back(new p2t::Point(2.0, 4.5));
	polyLine.push_back(new p2t::Point(1.0, 3.25));
	polyLine.push_back(new p2t::Point(0.0, 1.0));
	polyLine.push_back(new p2t::Point(0.0, 0.0));
}
