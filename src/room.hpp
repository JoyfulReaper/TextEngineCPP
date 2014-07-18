/*
 TextEngine: room.hpp
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
 * @file room.hpp
 * @author Kyle Givler
 */

#ifndef _ROOM_H_
#define _ROOM_H_

#include <memory>
#include <boost/array.hpp>
#include "mapsite.hpp"
#include "inventory.hpp"

class NonPlayableCharacter;

static const std::string INVALID_ROOM_FILENAME = "NULL";

class Room : public MapSite
{
public:
  Room();
  
  Room(const Room &obj);
  
  virtual ~Room() {}
  
  /**
   * Get the "side" of the room in the given Direction
   * @return MapSite in direction
   */
  MapSite* getSide(Direction dir);
  
  /**
   * @param dir Direction to put MapSite
   * @param site MapSite to put at direction
   */
  void setSide(Direction dir, std::unique_ptr<MapSite> side);
  
  /**
   * Enter the room
   * @param from The direction the Character came from
   */
  virtual void enter(Direction from, TextEngine &engine);
  
  virtual void showFullDescription(TextEngine &engine);
  
  /**
   * @param sName This Room's short name
   */
  inline void setShortName(std::string sName) { this->shortName = sName;  }
  
  /**
   * @return This Room's short name
   */
  inline std::string getShortName() { return shortName; }
  
  /**
   * @param name the name of the room
   */
  inline void setName(const std::string name) { this->name = name; }
  
  /**
   * @return the name of the room
   */
  inline std::string getName() const { return name; }
  
  /**
   * @param desc Description for the room
   */
  inline void setDescription(const std::string desc) { this->description = desc; }
  
  /**
   * @return the description of this room
   */
  inline std::string getDescription() const { return description; }
  
  /**
   * Set extra look description
   * @param desc Look description
   */
  inline void setLookDescription(const std::string desc) { this->lookDescription = desc; }
  
  /**
   * @return The look description
   */
  inline std::string getLookDescription() const { return lookDescription; }
  
  /**
   * @param visited Set room as visited or not
   */
  inline void setVisited(bool visited) { this->visited = visited; }
  
  /**
   * @return true if the room has been visited, false otherwise
   */
  inline bool getVisited() const { return visited; }
  
  /**
   * @return the Room's Inventory
   */
  inline Inventory& getInventory() { return inventory; }
  
  /**
   * @return true on success, false on failure
   */
  bool setFilename(const std::string filename);
  
  /**
   * @param name The name of the NonPlayableCharacter to check for
   * @return true if it is in the room, false otherwise
   */
  bool hasNpc(std::string name, TextEngine &engine);  
  
private:
  /**
   * Get a string with the direction to this Room's exits
   */
  std::string getExitString();
  
  /**
   * @return a string of Item names and quantities
   */
  std::string getInventoryString();
  
  /**
   * @return String on NPCs in the room
   */
  std::string getNpcString(TextEngine &engine);
  
  boost::array<std::unique_ptr<MapSite>, 6> sides; // Room roof/floor/wall/exits
  Inventory inventory;
  std::string name; // Name of room
  std::string shortName;
  std::string description; // Room description
  std::string lookDescription; // Extra description shown on look command
  std::string filename = INVALID_ROOM_FILENAME; // Lua file associated with room
  bool visited = false;
};
#endif