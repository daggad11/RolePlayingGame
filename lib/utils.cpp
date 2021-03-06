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
#include "utils.hpp"

sf::Vertex* utils::wrapIndex(std::vector<sf::Vertex*> vertices, int i)
{
	if (i >= vertices.size())
			i %=  vertices.size();
	return vertices[i];	
}

sf::Vector2f utils::createVector(sf::Vertex* u, sf::Vertex* v)
{
	sf::Vector2f resultant;
	resultant.x = v->position.x - u->position.x;
	resultant.y = v->position.y - u->position.y;
	return resultant;
}

double utils::getAngle(sf::Vector2f u, sf::Vector2f v)
{
	return acos((u.x*v.x + u.y*v.y)/(sqrt(u.x*u.x + u.y*u.y)*sqrt(v.x*v.x + v.y*v.y))); 
}

float utils::getZProduct(sf::Vector2f u, sf::Vector2f v)
{
	return u.x*v.y - v.x*u.y;
}

double utils::getRand(double start, double end, double randNum)
{
	return randNum*(end - start) + start;
}

float utils::getRand(float start, float end, float randNum)
{
	return randNum*(end - start) + start;
}