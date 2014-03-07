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

chunk::chunk(float conversion, sf::RenderWindow* window)
{
	this->window = window;
	conv = conversion;
	generate();
	triangulate();
	convert();
	//fill.loadFromFile("resources/textures/seamless_dirt.jpg"); //textures aren't important yet.
	//fill.setRepeated(true);
}

chunk::chunk(sf::Vector2f* start, sf::Vector2f* end, float conversion, sf::RenderWindow* window)
{
	this->window = window;
	conv = conversion;
	this->start = start; //these have to go before generate()... this took me way too long to figure out (I persecuted several random generators needlessly)
	this->end = end;
	generate();
	triangulate();
	convert();
	fill.loadFromFile("resources/textures/seamless_dirt.jpg"); //textures aren't important yet.
	fill.setRepeated(true);
}

void chunk::draw() 
{
    window->draw(&converted[0], converted.size(), sf::Triangles, &fill);
    window->draw(&convertedLines[0], convertedLines.size(), sf::LinesStrip);
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

//generates a random chunk, with a fixed width and starting height (if set)
void chunk::generate()
{
	typedef std::chrono::high_resolution_clock sysclock; //too many goddamn ::s. Maybe chase was right...
	sysclock::time_point now = sysclock::now();
	sysclock::duration d = now.time_since_epoch();
	//std::cout << "Seed: " << d.count() << "." << std::endl;
	std::default_random_engine generator;
	generator.seed(d.count());
	now.~time_point();
	d.~duration();
	std::uniform_real_distribution<double> dist(0, 1.0); 
	polyLine.push_back(new p2t::Point(start->x, start->y));
	polyLine.push_back(new p2t::Point(end->x, end->y)); 
	auto random = std::bind(dist, generator);
	float maxDepth = 4.0; //current generation depth is only 4, float type is IMPORTANT
	for(float depth = 1.0; depth <= maxDepth; depth+=1.0)
	{
		for (int i = 0; i < polyLine.size() - 1; i+=2) //iterates through the vector and adds in new points between the original ones.
		{
			double randX = utils::getRand(polyLine[i]->x, polyLine[i+1]->x, random());
			double randY = ((polyLine[i]->y + polyLine[i+1]->y)/2.0) + utils::getRand(0.0, 3.0, random())/(pow(depth, 2)); //operator precedence screws up here (hence all the parenned stuff), it's really strange
			p2t::Point* p = new p2t::Point(randX, randY); 
			polyLine.insert(polyLine.begin()+i+1, p);
			//std::cout << "Added a new point." << std::endl;
		}		
		//std::cout << "Layer " << depth << " added." << std::endl;
	}

	polyLine.push_back(new p2t::Point(end->x, 0.0));
	polyLine.insert(polyLine.begin(), new p2t::Point(start->x, 0.0));
	for (int i = 0; i < polyLine.size() - 1; i++)
	{ 
		lines.push_back(new line(polyLine[i], polyLine[i+1]));
	}
	//genGrass();
}

void chunk::convert()
{
	std::vector<sf::Vertex> v;
	for (auto vert: triVerts)
	{
		sf::Vector2f pos(vert->position.x*conv, window->getSize().y - (vert->position.y*conv));
		sf::Vector2f texCoords(vert->texCoords.x*conv, window->getSize().y - (vert->texCoords.y*conv));
		v.push_back(*(new sf::Vertex(pos, texCoords)));
	}	
	converted = v;

	std::vector<sf::Vertex> u;
	for (int i = 0; i < lines.size() - 1; i+=2)
	{
		u.push_back(sf::Vertex(sf::Vector2f(lines[i]->getPoints()[0]->x*conv, window->getSize().y - lines[i]->getPoints()[0]->y*conv)));
		u.push_back(sf::Vertex(sf::Vector2f(lines[i]->getPoints()[1]->x*conv, window->getSize().y - lines[i]->getPoints()[1]->y*conv)));
	}
	convertedLines = u;

}
//I'll worry about this later...
/* 
void chunk::genGrass()
{
	for (int i = 0; i < lines.size(); i++)
	{
		bool intersects = false;
		line* testLine = new Line(lines[i]->getMidPoint().x, lines[i]->getMidPoint().y, lines[i]->getMidPoint().x, lines[i]->getMidPoint().y + 50);
		for (int j = 0; j < lines.size(); j++)
		{
			if (j == i)
				continue;
			else
			{
				if (lines[0]->intersects(testLine))
				{
					intersects = true;
					break;
				}
			}
		}
		sf::RectangleShape r = new RectangleShape(sf::Vector2f(lines[i]->getLength, 5.0));
		r.setPosition(min(lines[i]->getPoints()[0]->x, lines[i]->getPoints()[1]->x), )

	}
}
*/

std::vector<line*>* chunk::getLines()
{
	return &lines;
}
