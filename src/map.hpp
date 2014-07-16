/*
 T extE*ngine: map.hpp
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
 * @file map.hpp
 * @author Kyle Givler
 */

#ifndef _MAP_H_
#define _MAP_H_

#include <map>
#include <memory>
#include <string>

class Room;

class Map
{
public:
  Map() {}
  
  Map(const Map &obj);
  
  virtual ~Map() {}
  /**
   * Add a Room to the Map 
   * @param room the Room to add
   * @return true on success, false on failure (already exists)
   */
  bool addRoom(Room *room);
  
  /**
   * Retreive a Room from the map 
   * @param name The Room name
   * @return The requested room, or nullptr if not in the Map
   */
  Room* getRoom(std::string name);
  
  /**
   * @param name The room number of the room to check for
   * @return true if the room with the given room number exists, false otherwise
   */
  bool roomExists(std::string name); 
  
private:
  std::map<std::string, boost::shared_ptr<Room>> rooms;
};

#endif