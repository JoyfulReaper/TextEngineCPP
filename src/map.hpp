/*
 TextEngine: map.hpp
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

#include <memory>
#include <string>
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "serialization_adaptors.hpp"

#include "npc.hpp"
#include "wall.hpp"
#include "room.hpp"
#include "roof.hpp"
#include "exit.hpp"
#include "floor.hpp"
#include "player.hpp"
#include "containerItem.hpp"

class TextEngine;

class Map
{
public:
  Map(std::string gamePath);
  
  /**
   * Don't use this copy ctor, not complete
   */
  Map(const Map &obj);
  
  virtual ~Map() {}
  
  ////////////////////////////////////////////////////////////////////////////////
  
  /**
   * Add a Room to the Map 
   * @param room the Room to add
   * @return true on success, false on failure (already exists)
   */
  bool addRoom(std::unique_ptr<Room> room);

   /**
   * @param name The room number of the room to check for
   * @return true if the room with the given room number exists, false otherwise
   */
  bool roomExists(std::string name);
  
  /**
   * @param name Name of room
   * @return Room
   */
  Room& getRoom(std::string name);
  
  /**
   * @param name The room to remove 
   * @return True on success, false on failure
   */
  bool removeRoom(std::string name);
  
  inline void setStartRoom(std::string name) { this->startRoom = name; }
  
  inline std::string getStartRoom() const { return startRoom; }
  
  ////////////////////////////////////////////////////////////////////////////////////
  
  // MapSite* getRoomSide(std::string name, Direction dir);
  
  // bool setRoomSide(std::string name, Direction from, std::unique_ptr<MapSite> side);
  
  bool enterRoom(std::string name, Direction from, TextEngine &engine);
  
  bool setRoomName(std::string shortName, std::string newLongName);
  
  std::string getRoomName(std::string shortName);
  
  bool setRoomDescription(std::string name, std::string description);
  
  std::string getRoomDescription(std::string name);
  
  bool setRoomLookDescription(std::string name, std::string description);
  
  std::string getRoomLookDescription(std::string name);
  
  bool setRoomVisited(std::string room, bool visited);
  
  bool getRoomVisited(std::string room);
  
  ////////////////////////////////////////////////////////////////////////////////////
  
  bool addNpc(std::unique_ptr<NonPlayableCharacter> npc);
  
  /**
   * Remove All NPCs with name at location
   */
  bool removeNpcs(std::string name, std::string location);
  
  bool hasNpc(std::string name, std::string location);
  
  std::vector<NonPlayableCharacter*> getNpcs(std::string name, std::string location);
  
  std::vector<NonPlayableCharacter*> getAllNpcs(std::string location);
  
  std::vector<NonPlayableCharacter*> getAllNpcs();
  
  ////////////////////////////////////////////////////////////////////////////////////
  
private:
  std::vector<boost::shared_ptr<Room>> rooms;
  std::vector<boost::shared_ptr<NonPlayableCharacter>> npcs;
  std::string startRoom = "";
  std::string gamePath;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar.register_type(static_cast<ContainerItem *>(NULL));
    ar.register_type(static_cast<Player *>(NULL));
    ar.register_type(static_cast<NonPlayableCharacter *>(NULL));
    ar.register_type(static_cast<Wall *>(NULL));
    ar.register_type(static_cast<Room *>(NULL));
    ar.register_type(static_cast<Roof *>(NULL));
    ar.register_type(static_cast<Floor *>(NULL));
    ar.register_type(static_cast<Exit *>(NULL));
    ar & rooms;
    ar & npcs;
    ar & startRoom;
    ar & gamePath;
  }
};

#endif