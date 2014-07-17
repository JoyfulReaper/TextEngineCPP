/*
 * TextEngine: mapBuilder.cxx
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
 * @file mapBuilder.cxx
 * @author Kyle Givler
 */

#include <boost/algorithm/string.hpp>
#include <vector>
#include <memory>
//#include <stdexcept>
#include "mapsite.hpp"
#include "mapBuilder.hpp"
#include "textEngineException.hpp"
#include "wall.hpp"
#include "floor.hpp"
#include "roof.hpp"
#include "exit.hpp"


using namespace boost;

void MapBuilder::buildObjects(std::vector<std::map<std::string,std::string>> &roomConfig)
{
  for (auto it = roomConfig.begin(); it != roomConfig.end(); ++it)
  {
    auto config = *it;
    std::unique_ptr<Room> room(new Room);
    std::string startRoom = "";
    
    // Setup the room
    room->setShortName(config["shortName"]);
    room->setFilename(config["filename"]);
    
    std::string name = config["name"];
    if(name == "player")
      throw (TextEngineException("'player' is an invalid name for a room!"));
    room->setName(config["name"]);
    
    room->setDescription(config["description"]);
    if(config["lookDescription"] == "")
      room->setLookDescription("You look really carefully, but you can't see anything you haven't seen before.");
    else
      room->setLookDescription(config["lookDescription"]);
    
    try{
      if(std::stoi(config["startRoom"]))
	map.setStartRoom(room->getShortName());
    } catch(const std::invalid_argument &ia) {
      // Not the starting room
    }
    
    // Set defaults
    room->setSide(Direction::North, std::unique_ptr<Wall>(new Wall));
    room->setSide(Direction::South, std::unique_ptr<Wall>(new Wall));
    room->setSide(Direction::East, std::unique_ptr<Wall>(new Wall));
    room->setSide(Direction::West, std::unique_ptr<Wall>(new Wall));
    room->setSide(Direction::Up, std::unique_ptr<Roof>(new Roof));
    room->setSide(Direction::Down, std::unique_ptr<Floor>(new Floor));
    
    // Add to map, if unique shortName
    if(!map.addRoom(std::move(room)))
      throw (TextEngineException("Unable to add room " + config["shortName"] + ", duplicate room name"));
    
    // Split exit string
    Direction direction;
    std::string toRoomShortName;
    std::vector<std::string> exitVector;
    split(exitVector, config["exits"], is_any_of(":"));
    if(exitVector.size() == 0 || exitVector.size() % 2 != 0)
    {
      throw (TextEngineException("Malformed exits string in room " + config["shortName"]));
    }
    
    // Add Exits
    for(size_t i = 0; i < exitVector.size(); i += 2)
    {
      bool isLocked = false;
      bool isVisible = true;
      direction = MapSite::getDirectionFromChar(exitVector[i][0]);
      if(exitVector[i].find("L") != std::string::npos)
	isLocked = true;
      if(exitVector[i].find("I") != std::string::npos)
	isVisible = false;
      if (direction == Direction::Invalid)
	throw (TextEngineException("Malformed exits string in room " + config["shortName"]));
      toRoomShortName = (exitVector[i+1]);
      buildExit(room->getShortName(), toRoomShortName, direction, isLocked, isVisible);
    }
    
  }
}

void MapBuilder::buildExit(std::string fromRoom, std::string toRoom, Direction dir, bool isLocked, bool isVisible)
{
  //Exit *exit = new Exit(engine, toRoom);
  std::unique_ptr<Exit> exit(new Exit(toRoom));
  if(isLocked)
    exit->lockExit();
  if(!isVisible)
    exit->setVisible(false);
  Room &from = map.getRoom(fromRoom);
  from.setSide(dir, std::move(exit));
}