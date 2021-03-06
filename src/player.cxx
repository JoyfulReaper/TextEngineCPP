/*
 TextEngine: player.cxx
 Copyright (C) 2014 Kyle Givler
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file player.cxx
 * @author Kyle Givler
 */

#include "player.hpp"
#include "playerParser.hpp"
#include "playerBuilder.hpp"

Player::Player(std::string gamePath) : gamePath(gamePath)
{
  PlayerParser pp;
  PlayerBuilder pb(*this);
  auto results = pp.parsePlayer(gamePath);
  pb.buildObjects(results);
}

Player::Player(const Player &obj) : Character(obj)
{
  this->gamePath = obj.gamePath;
}