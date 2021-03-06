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
#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <poly2tri.h> 
#include <utils.hpp>
#include <line.hpp>


class chunk {
public:
	chunk();
	chunk(float conversion, sf::RenderWindow* window);
	chunk(sf::Vector2f* start, sf::Vector2f* end, float conversion, sf::RenderWindow* window);
	void draw();
	void generate();
	void triangulate();
	void convert();
	//void genGrass(); //In progress
	std::vector<line*> *getLines();
private:
	std::vector<sf::Vertex*> triVerts; //in-engine unit triangles, every 3 points define a new triangle
	std::vector<p2t::Point*> polyLine; //initial list of points generated to be triangulated for drawing (counterclockwise)
	std::vector<sf::Vertex> converted; //converted triangles to be drawn
	std::vector<sf::Vertex> convertedLines;
	std::vector<line*> lines; //list of lines for hit detection
	std::vector<sf::RectangleShape*> grass;
	sf::RenderWindow* window;
	sf::Texture fill;
	sf::Vector2f* start;
	sf::Vector2f* end;
	float conv;
};

#endif
