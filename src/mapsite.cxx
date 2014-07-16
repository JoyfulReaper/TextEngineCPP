/*
  * TextEngine: mapsite.cxx
  * Copyright (C) 2014 Kyle Givler
  * 
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * 
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  * 
  * You should have received a copy of the GNU General Public License
  * along with this program. If not, see <http://www.gnu.org/licenses/>.
  */

/**
  * @file mapsite.cxx
  * @author Kyle Givler
  */

#include "mapsite.hpp"

MapSite::MapSite(const MapSite &obj)
{
  this->name = obj.name;
}

static std::string getDirectionName(Direction dir)
{
  std::string dirName = "invalid";
  switch (dir)
  {
    case Direction::North:
    {
      dirName = "North";
      break;
    }
    case Direction::South:
    {
      dirName = "South";
      break;
    }
    case Direction::East:
    {
      dirName = "East";
      break;
    }
    case Direction::West:
    {
      dirName = "West";
      break;
    }
    case Direction::Up:
    {
      dirName = "up";
      break;
    }
    case Direction::Down:
      dirName = "down";
      break;
    default:
      dirName = "Invalid";
  }
  return dirName;
}


static Direction getDirectionFromChar(char letter)
{
  Direction direction;
  letter = toupper(letter);
  switch(letter)
  {
    case 'N':
    {
      direction = Direction::North;
      break;
    }
    case 'S':
    {
      direction = Direction::South;
      break;
    }
    case 'E':
    {
      direction = Direction::East;
      break;
    }
    case 'W':
    {
      direction = Direction::West;
      break;
    }
    case 'U':
    {
      direction = Direction::Up;
      break;
    }
    case 'D':
    {
      direction = Direction::Down;
      break;
    }
    default:
      direction = Direction::Invalid;
  }
  return direction;
}