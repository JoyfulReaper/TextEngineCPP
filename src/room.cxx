/*
 * TextEngine: room.cxx
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
 * @file room.cxx
 * @author Kyle Givler
 */

#include <fstream>
#include <boost/algorithm/string/case_conv.hpp>
#include "thirdParty/luawrapper/LuaContext.hpp"
#include "room.hpp"
#include "textEngine.hpp"
#include "textEngineException.hpp"

#include "mapsite.hpp"
#include "roof.hpp"
#include "wall.hpp"
#include "floor.hpp"
#include "exit.hpp"

Room::Room() {}

Room::Room(const Room &obj) : inventory(Inventory(obj.inventory))
{
  this->name = obj.name;
  this->shortName = obj.shortName;
  this->description = obj.description;
  this->lookDescription = obj.lookDescription;
  this->filename = obj.filename;
  this->visited = obj.visited;
  
  size_t count = 0;
  for(auto it = obj.sides.begin(); it != obj.sides.end(); ++it)
  {
    MapSite *ms = it->get();
    if(dynamic_cast<Wall*>(ms))
    {
      this->setSide(static_cast<Direction>(count), std::unique_ptr<Wall>(new Wall(*static_cast<Wall*>(ms))) );
    } else if (dynamic_cast<Roof*>(ms))
    {
      this->setSide(static_cast<Direction>(count), std::unique_ptr<Roof>(new Roof(*static_cast<Roof*>(ms))) );
    } else if (dynamic_cast<Floor*>(ms))
    {
      this->setSide(static_cast<Direction>(count), std::unique_ptr<Floor>(new Floor(*static_cast<Floor*>(ms))) );
    } else if (dynamic_cast<Exit*>(ms)) 
    {
      this->setSide(static_cast<Direction>(count), std::unique_ptr<Exit>(new Exit(*static_cast<Exit*>(ms))) );
    } else 
    {
      this->setSide(static_cast<Direction>(count), std::unique_ptr<MapSite>(nullptr) );
    }
    count++;
  }
}

MapSite* Room::getSide(Direction dir)
{
  return sides[static_cast<size_t>(dir)].get();
}

void Room::setSide(Direction dir, std::unique_ptr<MapSite> side)
{
  sides[static_cast<size_t>(dir)] = std::move(side);
}

// Room was entered by Player
void Room::enter(Direction from, TextEngine &engine)
{
  LuaContext &lua = engine.getLuaContext();
  engine.getPlayer().setLocation(getShortName()); // Update Player's location
  
  engine.addMessage("\nCurrent Location: " + getName() + "\n\n"); // Add name of room
  
  //Call room's onEnter
  try {
    std::ifstream roomFile(filename);
    lua.executeCode(roomFile);
    lua.executeCode("onEnter()"); // Notify room script Player has entered
    roomFile.close();
  } catch (const LuaContext::SyntaxErrorException &see) {
    std::cerr << see.what();
  } catch (const LuaContext::ExecutionErrorException &eee) {
    // No onEnter()
  }
  lua.writeVariable("onEnter", nullptr); // Clear function incase next room doesn't have an onEnter()
  
  engine.addMessage("\t" + getDescription() + "\n\n"); // Add description
  
  //Process NPC stuff
  auto npcs = engine.getMap().getAllNpcs(getShortName());
  try {
    for(auto it = npcs.begin(); it != npcs.end(); ++it)
    {
      NonPlayableCharacter *npc = *it;
      if(!npc->isAlive())
      {
	int ran = engine.getRandomNumber(0, 100);
	if(ran <= npc->getRespawnChance())
	  npc->setHealthNoAttack(100);
      }
      if(npc->isAlive())
      {
	std::ifstream npcFile(npc->getFilename());
	lua.executeCode(npcFile);
	lua.executeCode("playerEntered()");
	npcFile.close();
      }
    }
  } catch (const LuaContext::SyntaxErrorException &see) {
    std::cerr << see.what();
  } catch (const LuaContext::ExecutionErrorException &eee) {
    // No playerEntered
  }
  lua.writeVariable("playerEntered", nullptr);
  
  engine.addMessage(getNpcString(engine) + "\n");
  engine.addMessage("You see: " + getInventoryString() + "\n");
  engine.addMessage("Exits: " + getExitString() + "\n");
  
  setVisited(true);
}

void Room::showFullDescription(TextEngine &engine)
{
  engine.addMessage("\nCurrent Location: " + getName() + "\n\n");
  engine.addMessage("\t" + getDescription() + "\n\n");
  engine.addMessage("\t" + getLookDescription() + "\n\n");
  engine.addMessage(getNpcString(engine) + "\n");
  engine.addMessage("You see: " + getInventoryString() + "\n");
  engine.addMessage("Exits: " + getExitString() + "\n");
}

std::string Room::getExitString()
{
  std::string exits;
  for(size_t i = 0; i < 6; i++)
  {
    MapSite *side = getSide(static_cast<Direction>(i));
    side = dynamic_cast<Exit*>(side);
    if(side)
    {
      Exit *exit = static_cast<Exit *>(side);
      if(exit->isVisible())
	exits.append(getDirectionName(static_cast<Direction>(i)) + ", ");
    }
  }
  exits.erase((exits.length() - 2), 2);
  return exits;
}

std::string Room::getInventoryString()
{
  if(inventory.isEmpty())
    return "No items";
  
  auto allItems = inventory.getAllItems();
  std::string items;
  for(auto it = allItems.begin(); it != allItems.end(); ++it)
  {
    const Item *item = *it;
    if(item->isVisible())
    {
      std::string name = item->getName();
      if(item->getQuantity() > 1)
	name.append(" (" + std::to_string(item->getQuantity()) + ")");
      items.append(name + ", ");
    }
  }
  if(items.length() > 2)
    items.erase(items.length() -2, 2);
  else
  {
    return "No items"; // Could be some invisible
  }
    
  return items;  
}

std::string Room::getNpcString(TextEngine &engine)
{
  auto npcs = engine.getMap().getAllNpcs(getShortName());
  
  if(npcs.empty())
    return "";
  
  std::string creatures = "Creatures: ";
  for(auto it = npcs.begin(); it != npcs.end(); ++it)
  {
    NonPlayableCharacter *npc = *it;
    std::string name = npc->getName();
    creatures.append(name + ", ");
  }
  creatures.erase(creatures.length() -2, 2);
  return creatures;
}

bool Room::setFilename(const std::string filename)
{
  if(this->filename == INVALID_ROOM_FILENAME)
  {
    this->filename = filename;
    return true;
  }
  return false;
}

bool Room::hasNpc(std::string name, TextEngine &engine)
{
  return engine.getMap().hasNpc(name, getShortName());
}