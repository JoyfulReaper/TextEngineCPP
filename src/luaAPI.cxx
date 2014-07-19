/*
 TextEngine: luaAPI.cxx
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
 * @file luaAPI.cxx
 * @author Kyle Givler
 * 
 * TODO:
 * Largely un-tested and could use improvements, especially relating to NPCs
 */

#include <boost/filesystem.hpp>
#include <fstream>
#include "luaAPI.hpp"
#include "textEngine.hpp"
#include "exit.hpp"
#include "containerItem.hpp"
#include "thirdParty/luawrapper/LuaContext.hpp"

using namespace boost;

LuaAPI::LuaAPI(TextEngine &engine) : engine(&engine) {}

LuaContext& LuaAPI::getLuaContext()
{
  return lua;
}

void LuaAPI::addMessage(std::string message)
{
  engine->addMessage(message);
}

bool LuaAPI::doCommand(std::string command)
{
  return engine->processCommand(command);
}

bool LuaAPI::doCommandSilent(std::string command)
{
  engine->ignoreMessages(true);
  bool ret = engine->processCommand(command);
  engine->ignoreMessages(false);
  return ret;
}

int LuaAPI::getRandomNumber(int min, int max)
{ 
  return engine->getRandomNumber(min, max); 
}

void LuaAPI::setGameOver()
{
  engine->gameIsOver();
}

bool LuaAPI::runScript(std::string script)
{
  filesystem::path fullPath(engine->getGamePath());
  fullPath += "/scripts/" + script;
  
  try{
    if(!(exists(fullPath) && is_regular_file(fullPath)))
      return false;
  } catch (const filesystem::filesystem_error &ex) {
    return false;
  }
  
  try {
    std::fstream scriptFile(fullPath.native());
    lua.executeCode(scriptFile);
    scriptFile.close();
  } catch (const LuaContext::SyntaxErrorException &see) {
    return false;
  } catch (const LuaContext::ExecutionErrorException &eee) {
    return false;
  }
  return true;
}

bool LuaAPI::runLuaCode(std::string luaCode)
{
  try {
    lua.executeCode(luaCode);
  } catch (const LuaContext::SyntaxErrorException &see) {
    return false;
  } catch (const LuaContext::ExecutionErrorException &eee) {
    return false;
  }
  return true;
}

bool LuaAPI::registerCommand(std::string verb, std::string file)
{
  return engine->registerCommand(verb, file);
}

////////////////////////////////////////////////////////////////////////////////////

bool LuaAPI::roomExists(std::string room)
{
  return engine->getMap().roomExists(room);
}

bool LuaAPI::setRoomDescription(std::string desc, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  theRoom.setDescription(desc);
  return true;
}

std::string LuaAPI::getRoomDescription(std::string room)
{
  if(!engine->getMap().roomExists(room))
    return "";
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getDescription();
}

bool LuaAPI::getRoomVisited(std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getVisited();
}

bool LuaAPI::setRoomVisited(std::string room, bool visited)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);  
  theRoom.setVisited(visited);
  return true;
}

std::string LuaAPI::getRoomShortName()
{
  std::string name = engine->getPlayerRoom().getShortName();
  return name;
}

bool LuaAPI::setRoomName(std::string name, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  engine->getMap().getRoom(room).setName(name);
  return true;
}

std::string LuaAPI::getRoomName(std::string room)
{
  if(!engine->getMap().roomExists(room))
    return "";
    
  return engine->getMap().getRoom(room).getName();
}

bool LuaAPI::setRoomLookDescription(std::string name, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);  
  theRoom.setLookDescription(name);
  return true;
}

std::string LuaAPI::getRoomLookDescription(std::string room)
{
  if(!engine->getMap().roomExists(room))
    return "";
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getLookDescription();
}

bool LuaAPI::roomHasNPC(std::string who, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.hasNpc(who, *engine);
}

std::map<int, std::string> LuaAPI::getTableOfNpcs(std::string room)
{
  std::map<int, std::string> npcTable;
  if(!engine->getMap().roomExists(room))
    return npcTable;
  
  auto allNpcs = engine->getMap().getAllNpcs(room);
  size_t count = 0;
  for(auto it = allNpcs.begin(); it != allNpcs.end(); ++it)
  {
    count++;
    const NonPlayableCharacter *npc = *it;
    npcTable.insert(std::pair<int,std::string>(count, npc->getName()));
  }
  return npcTable;
}

bool LuaAPI::checkIfExitLocked(std::string room, int dir)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  Direction edir = static_cast<Direction>(dir);
  
  if(dynamic_cast<Exit*>(theRoom.getSide(edir)))
  {
    Exit *exit = static_cast<Exit*>(theRoom.getSide(edir));
    return (exit->isExitLocked());
  }
  return false;
}

bool LuaAPI::setExitLocked(std::string room, int dir, bool lock)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  Direction edir = static_cast<Direction>(dir);
  
  if(dynamic_cast<Exit*>(theRoom.getSide(edir)))
  {
    Exit *exit = static_cast<Exit*>(theRoom.getSide(edir));
    if(lock)
      exit->lockExit();
    else
      exit->unlockExit();
    
    return true;
  }
  return false;
}

bool LuaAPI::checkExitVisible(std::string room, int dir)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  Direction edir = static_cast<Direction>(dir);
  
  if(dynamic_cast<Exit*>(theRoom.getSide(edir)))
  {
    Exit *exit = static_cast<Exit*>(theRoom.getSide(edir));
    return (exit->isVisible());
  }
  return false;
}

bool LuaAPI::setExitVisible(std::string room, int dir, bool visible)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);  
  Direction edir = static_cast<Direction>(dir);
  if(dynamic_cast<Exit*>(theRoom.getSide(edir)))
  {
    Exit *exit = static_cast<Exit*>(theRoom.getSide(edir));
    exit->setVisible(visible);
    return true;
  }
  return false;
}

///////////////////////////////////////////////////////////////////////////////////

bool LuaAPI::setPlayerLocation(std::string loc)
{ 
  if(engine->getMap().roomExists(loc))
  {
    //engine->getPlayer().setLocation(loc);
    engine->getMap().getRoom(loc).enter(Direction::Invalid, *engine);
    return true;
  }
  return false;
}

bool LuaAPI::setPlayerMoney(double amount)
{
  if(amount < 0)
    return false;
  
  engine->getPlayer().setMoney(amount);
  return true;
}

double LuaAPI::getPlayerMoney()
{
  return engine->getPlayer().getMoney();
}

double LuaAPI::getPlayerHealth()
{
  return engine->getPlayer().getHealth();
}

bool LuaAPI::setPlayerHealth(double amount)
{
  if( (amount < 0) || (amount > 100) )
    return false;
  
  engine->getPlayer().setHealth(amount);
  return true;
}

bool LuaAPI::setCharacterDescription(std::string desc, std::string who)
{
  if (who == "player")
  {
    engine->getPlayer().setDescription(desc);
    return true;
  }
  else
  {
    auto npcs = engine->getMap().getAllNpcs();
    for(auto &npc : npcs)
    {
      if(npc->getName() == who || npc->getUppercaseName() == who)
	npc->setDescription(desc);
    }
  }
  return true;
}

std::string LuaAPI::getCharacterDescription(std::string who)
{
  if (who == "player")
    return engine->getPlayer().getDescription();
  
  auto npcs = engine->getMap().getAllNpcs();
  for(auto &npc : npcs)
  {
    if(npc->getName() == who || npc->getUppercaseName() == who)
      return npc->getDescription();
  }
  return "";
}

std::string LuaAPI::getCharacterLocation(std::string who)
{
  if(who == "player")
    return engine->getPlayer().getLocation();
  
  std::string where;
  auto npcs = engine->getMap().getAllNpcs();
  for(auto &npc : npcs)
  {
    if(npc->getName() == who || npc->getUppercaseName() == who)
    {
      where.append(npc->getLocation() + ":");
    }
  }
  return where;
}

bool LuaAPI::setCharacterMoney(double amount, std::string who, std::string where)
{ 
  if(!engine->getMap().roomExists(where))
    return false;
  if(!engine->getMap().getRoom(where).hasNpc(who, *engine))
    return false;
  
  auto npcs = engine->getMap().getNpcs(who, where);
  for(auto &npc : npcs)
  {
    npc->setMoney(amount);
  }
  return true;
}

double LuaAPI::getCharacterMoney(std::string who, std::string where)
{
  if(!engine->getMap().roomExists(where))
    return -1;
  if(!engine->getMap().getRoom(where).hasNpc(who, *engine))
    return -1;
  
  auto npcs = engine->getMap().getNpcs(who, where);
  for(auto &npc : npcs)
  {
    return npc->getMoney();
  }
  return -1;
}

bool LuaAPI::setCharacterHealth(double amount, std::string who, std::string where)
{
  if(!engine->getMap().roomExists(where))
    return false;
  if(!engine->getMap().getRoom(where).hasNpc(who, *engine))
    return false;
  
  auto npcs = engine->getMap().getNpcs(who, where);
  for(auto &npc : npcs)
  {
    npc->setHealth(amount, *engine);
  }
  return true;
}

double LuaAPI::getCharacterHealth(std::string who, std::string where)
{
  if(!engine->getMap().roomExists(where))
    return -1;
  if(!engine->getMap().getRoom(where).hasNpc(who, *engine))
    return -1;
  
  auto npcs = engine->getMap().getNpcs(who, where);
  for(auto &npc : npcs)
  {
    return npc->getHealth();
  }
  return true;
}

bool LuaAPI::characterIsAlive(std::string who, std::string where)
{
  if(!engine->getMap().roomExists(where))
    return false;
  if(!engine->getMap().getRoom(where).hasNpc(who, *engine))
    return false;

  auto npcs = engine->getMap().getNpcs(who, where);
  for(auto &npc : npcs)
  {
    return npc->isAlive();
  }
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////

bool LuaAPI::playerAddItem(std::string name, size_t num)
{
  bool ret;
  try {
    ret = engine->getPlayer().getInventory().addItem(name, num);
  } catch (const TextEngineException &te) {
    //Inv is full 
    return false;
  }
  return ret;
}

bool LuaAPI::playerRemoveItem(std::string name, size_t num)
{
  return engine->getPlayer().getInventory().removeItem(name, num);
}

bool LuaAPI::roomAddItem(std::string name, size_t num, std::string room)
{
  bool ret;
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);  
  try {
    ret = theRoom.getInventory().addItem(name, num);
  } catch (const TextEngineException &te) {
    //Inv is full
    return false;
  }
  return ret;
}

bool LuaAPI::roomRemoveItem(std::string name, size_t num, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getInventory().removeItem(name, num);
}

bool LuaAPI::playerHasItem(std::string name)
{
  return engine->getPlayer().getInventory().hasItem(name);
}

bool LuaAPI::roomHasItem(std::string name, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getInventory().hasItem(name);
}

std::map<int, std::string> LuaAPI::getRoomInvTable(std::string room)
{
  std::map<int, std::string> invTable;
  if(!engine->getMap().roomExists(room))
    return invTable;
  
  Room &theRoom = engine->getMap().getRoom(room);
  auto allItems = theRoom.getInventory().getAllItems();
  size_t count = 0;
  for(auto it = allItems.begin(); it != allItems.end(); ++it)
  {
    count++;
    const Item *item = *it;
    invTable.insert(std::pair<int,std::string>(count, item->getName()));
  }
  return invTable;
}

std::map<int, std::string> LuaAPI::getPlayerInvTable()
{  
  std::map<int, std::string> invTable;
  auto allItems = engine->getPlayer().getInventory().getAllItems();
  size_t count = 0;
  for(auto it = allItems.begin(); it != allItems.end(); ++it)
  {
    count++;
    const Item *item = *it;
    invTable.insert(std::pair<int,std::string>(count, item->getName()));
  }
  return invTable;
}

bool LuaAPI::checkContainerLocked(std::string item, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  if( ContainerItem *citem = dynamic_cast<ContainerItem*>(&theRoom.getInventory().getItem(item)) )
  {
    return (citem->isLocked());
  }
  return false;
}

bool LuaAPI::setContainerLocked(std::string item, std::string room, bool locked)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  if( ContainerItem *citem = dynamic_cast<ContainerItem*>(&theRoom.getInventory().getItem(item)) )
  {
    citem->setLocked(locked);
    return true;
  }
  return false;
}

size_t LuaAPI::getPlayerInvCapacity()
{
  return engine->getPlayer().getInventory().getCapacity();
}

size_t LuaAPI::getPlayerInvSize()
{
  return engine->getPlayer().getInventory().getSize();
}

void LuaAPI::setPlayerInvCapacity(size_t cap)
{
  engine->getPlayer().getInventory().setCapacity(cap);
}

bool LuaAPI::putItemInItem(std::string container, std::string contained, size_t num, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  if(dynamic_cast<ContainerItem*>(&theRoom.getInventory().getItem(container)))
  {
    ContainerItem *IContainer = static_cast<ContainerItem*>(&theRoom.getInventory().getItem(container));
    
    try {
      IContainer->getInventory().addItem(contained, num);
    } catch (const TextEngineException &te) {
      //Inv is full
      return false;
    }
    return true;
  }
  
  return false;
}

bool LuaAPI::getItemVisibility(std::string name, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getInventory().getItem(name).isVisible();
}

bool LuaAPI::setItemVisibility(std::string name, std::string room, bool visible)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  theRoom.getInventory().getItem(name).setVisible(visible);
  return true;
}

bool LuaAPI::getItemObtainable(std::string name, std::string room)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);
  return theRoom.getInventory().getItem(name).isObtainable();
}

bool LuaAPI::setItemObtainable(std::string name, std::string room, bool obtainable)
{
  if(!engine->getMap().roomExists(room))
    return false;
  
  Room &theRoom = engine->getMap().getRoom(room);  
  theRoom.getInventory().getItem(name).setObtainable(obtainable);
  return true;
}