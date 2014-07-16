/*
 TextEngine: map.cxx
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
 * @file map.cxx
 * @author Kyle Givler
 */

#include "config.h"
#include "map.hpp"
#include "room.hpp"

Map::Map(const Map &obj)
{
}

bool Map::addRoom(Room *room)
{
//   boost::shared_ptr<Room> sRoom;
//   sRoom.reset(room);
//   std::pair<std::map<std::string, boost::shared_ptr<Room>>::iterator, bool> ret;
//   ret = rooms.insert(std::pair<std::string, boost::shared_ptr<Room>>(room->getShortName(), sRoom));
//   
//   if(!ret.second)
//     return false;
//   
//   return true;
}

Room* Map::getRoom(std::string name)
{ 
//   Room *room;
//   try {
//     room = rooms.at(name).get();
//     return room;
//   } catch(const std::out_of_range &oor) {
//     return nullptr;
//   }
  return nullptr;
}

bool Map::roomExists(std::string name)
{
  return false;
}