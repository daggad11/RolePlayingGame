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
#include "world.hpp"

world::world(float conversion, sf::RenderWindow &window) {
	player1.init(1, 1, 1, .5, 1.8, conversion);
	chunks.push_back(new chunk(new sf::Vector2f(0.0, 7.0), new sf::Vector2f(30.0, 7.0), conversion, &window));
}

void world::draw(sf::RenderWindow &window) {
	player1.draw(window);
	
	for (auto chunk : chunks) {
		chunk->draw();
	}
}

void world::update(double time) {
	player1.update(time);
}

void world::handleEvent(sf::Event &event) {
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::D) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::A) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::W) {
			player1.handleEvent(event);
		}
		if (event.key.code == sf::Keyboard::S) {
			player1.handleEvent(event);
		}
	}
}