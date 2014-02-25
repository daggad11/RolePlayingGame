/* 
 * RolePlayingGame Copyright (c) 2014, RolePlayingGame Contributers
 * https://github.com/daggad11/RolePlayingGame
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of RolePlayingGame nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without specific
 *   prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "chunk.hpp"

chunk::chunk() {
	//default constructor
}

chunk::chunk(float conversion, sf::RenderWindow &window)
{
	conv = conversion;
	generate();
	triangulate();
	convert(window);
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
			//std::cout << p->x << "," << p->y << "  "; 
			triVerts.push_back(vert);
		}
		//std::cout << std::endl;
	}		
}

void chunk::convert(sf::RenderWindow &window)
{
	std::vector<sf::Vertex> v;
	for (auto vert: triVerts)
	{
		sf::Vector2f pos(vert->position.x*conv, window.getSize().y - (vert->position.y*conv));
		sf::Vector2f texCoords(vert->texCoords.x*conv, window.getSize().y - (vert->texCoords.y*conv));	
		v.push_back(*(new sf::Vertex(pos, sf::Color::Red, texCoords)));
	}	
	converted = v;
	//debugging text to console
	/*for (int i = 0; i < converted.size(); i++)
	{
		std::cout << converted[i].position.x << " " << converted[i].position.y << "  ";
		if ((i+1)%3 == 0)
			std::cout << std::endl;
	}
	*/
}

void chunk::draw(sf::RenderWindow &window) 
{
    window.draw(&converted[0], converted.size(), sf::Triangles);
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
