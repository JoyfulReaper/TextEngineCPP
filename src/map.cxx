/*
 * TextEngine: map.cxx
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
 * @file map.cxx
 * @author Kyle Givler
 */

#include <algorithm>
#include <iostream>
#include "map.hpp"
#include "mapBuilder.hpp"
#include "roomParser.hpp"
#include "npcParser.hpp"
#include "npcBuilder.hpp"
#include "room.hpp"
#include "textEngineException.hpp"

Map::Map(std::string gamePath) : gamePath(gamePath)
{
  RoomParser rp;
  MapBuilder mp(*this);
  auto results = rp.parseRooms(gamePath);
  mp.buildObjects(results);
  
  NPCParser np;
  NPCBuilder nb(*this);
  results = np.parseNPCs(gamePath);
  nb.buildObjects(results);
}

Map::Map(const Map &obj)
{
  //this->rooms = obj.rooms;
}

bool Map::addRoom(std::unique_ptr<Room> room)
{
  if( roomExists( room->getShortName() ) )
    return false;
  
  rooms.push_back(std::move(room));
  return true;
}

bool Map::roomExists(std::string name)
{
  for (auto &curRoom : rooms)
  {
    if (curRoom->getShortName() == name)
      return true;
  }
  return false;
}

Room& Map::getRoom(std::string name)
{
  for(auto &curRoom : rooms)
  {
    if(curRoom->getShortName() == name)
      return *curRoom;
  }
  
  throw(TextEngineException("Requested non-existant room: " + name));
}

////////////////////////////////////////////////////////////////////////////////////

bool Map::enterRoom(std::string name, Direction from, TextEngine &engine)
{
  try {
    getRoom(name).enter(from, engine);
  } catch (const TextEngineException &te) {
    return false;
  }
  return true;
}

bool Map::setRoomName(std::string shortName, std::string newLongName)
{
  try {
    getRoom(shortName).setName(newLongName);
  } catch (const TextEngineException &te) {
    return false;
  }
  return true;
}

std::string Map::getRoomName(std::string shortName)
{
  try {
    return getRoom(shortName).getName();
  } catch (const TextEngineException &te) {
    return "";
  }
}

bool Map::setRoomDescription(std::string name, std::string desc)
{
  try {
    getRoom(name).setDescription(desc);
    return true;
  } catch (const TextEngineException &te) {
    return false;
  }
}

std::string Map::getRoomDescription(std::string name)
{
  try {
    return getRoom(name).getDescription();
  } catch (const TextEngineException &te) {
    return "";
  }
}

bool Map::setRoomLookDescription(std::string name, std::string desc)
{
  try {
    getRoom(name).setLookDescription(desc);
    return true;
  } catch (const TextEngineException &te) {
    return false;
  }
}

std::string Map::getRoomLookDescription(std::string name)
{
  try {
    return getRoom(name).getLookDescription();
  } catch (const TextEngineException &te) {
    return "";
  }
}

bool Map::setRoomVisited(std::string room, bool visited)
{
  try {
    getRoom(room).setVisited(visited);
    return true;
  } catch (const TextEngineException &te) {
    return false;
  }
}

bool Map::getRoomVisited(std::string room)
{
  return getRoom(room).getVisited();
}

////////////////////////////////////////////////////////////////////////////////////

bool Map::addNpc(std::unique_ptr<NonPlayableCharacter> npc)
{
  if(roomExists(npc->getLocation()))
  {
    npcs.push_back(std::move(npc));
    return true;
  }
  return false;
}

bool Map::removeNpcs(std::string name, std::string location)
{
  for(auto it = npcs.begin(); it != npcs.end(); ++it)
  {
    if(it->get()->getName() == name && it->get()->getLocation() == location)
    {
      npcs.erase(it);
    }
    return true;
  }
  return false;
}

std::vector<NonPlayableCharacter*> Map::getNpcs(std::string name, std::string location)
{
  std::vector<NonPlayableCharacter*> results;
  for(auto& npc : npcs)
  {
    if(npc->getName() == name && npc->getLocation() == location)
      results.push_back(npc.get());
  }
  return results;
}

////////////////////////////////////////////////////////////////////////////////////
