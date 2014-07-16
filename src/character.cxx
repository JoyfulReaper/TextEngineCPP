/*
 TextEngine: character.cxx
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
 * @file character.cxx
 * @author Kyle Givler
 */


#include "character.hpp"

Character::Character() {}

Character::Character(const Character &obj)
{
  this->name = obj.name;
  this->description = obj.description;
  this->filename = obj.filename;
  this->location = obj.location;
  this->health = obj.health;
  this->money = obj.money;
  //Inventory?
}

void Character::setLocation(std::string locId)
{
  this->location = locId;
}

void Character::setFilename(std::string filename)
{
  this->filename = filename;
}