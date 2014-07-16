/*
 * TextEngine: TextEngine.cxx
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
 * @file TextEngine.cxx
 * @author Kyle Givler
 */

#include <random>
#include <chrono>
#include <fstream>
#include "textEngine.hpp"
#include "textEngineException.hpp"

TextEngine::TextEngine(std::string gamePath) : player(Player(gamePath)), gamePath(gamePath)
{ 
  //NPCParser np(this);
  //RoomParser rp(this);
  //ItemParser ip(this);
  
  //rp.parseRooms(gamePath);
  //ip.parseItems(gamePath);
  //np.parseNPCs(gamePath);
  
  //initLuaApi();
  
  //LuaContext *lua = getLuaContext();
  //boost::filesystem::path startScript(gamePath);
  //startScript += "/scripts/startup.lua";
  //std::fstream scriptPath(startScript.native());
  //if(scriptPath.is_open())
  //{
  //  lua->executeCode(scriptPath);
  //  scriptPath.close();
  // }
  
  //gameStarted = true;
  //if(startRoom == "")
  //  throw(TextEngineException("Starting room has not been set"));
  
  //map->getRoom(startRoom)->enter(Direction::Invalid);
  
  //initLuaApi(); 
}

////////////////////////////////////////////////////////////////////////

void TextEngine::addMessage(const std::string message)
{  
  if(!ignoringMessages())
    messages.push_back(message);
}

std::string TextEngine::getMessage()
{ 
  std::string message = messages.front();
  messages.pop_front();
  return message;
}

bool TextEngine::hasMessage() const
{  
  return (!messages.empty());
}

std::string TextEngine::getAllMessages()
{
  std::string message;
  while(hasMessage())
  {
    message.append(messages.front());
    messages.pop_front();
  }
  return message;
}

///////////////////////////////////////////////////////////////////////////

void TextEngine::setStartRoom(std::string startRoom)
{
  if (this->startRoom == "")
    this->startRoom = startRoom;
  else
    throw (TextEngineException("Start room already set"));
}

/////////////////////////////////////////////////////////////////////////

bool TextEngine::processCommand(std::string cmd) 
{ 
  return commandParser.doCommand(cmd, *this);
}

std::string TextEngine::getLastCommand() const {
  return commandParser.getLastCommand();
}

bool TextEngine::registerCommand(std::string verb, std::string file)
{
  return commandParser.registerCommand(verb, file, *this);
}

/////////////////////////////////////////////////////////////////////////

Player& TextEngine::getPlayer()
{
  return player;
}

/////////////////////////////////////////////////////////////////////////

bool TextEngine::isGameOver() const
{  
  return gameOver;
}

void TextEngine::gameIsOver()
{  
  gameOver = true;
}

/////////////////////////////////////////////////////////////////


// Map* TextEngine::getMap() const
// {   
//   return map.get(); 
// }
// 
// 
// void TextEngine::setMap(Map *map) 
// { 
//   this->map.reset(map);
// }

/////////////////////////////////////////////////////////////////////////

// void TextEngine::teachItem(std::string name, std::string filename)
// {
//   std::pair<std::map<std::string, std::string>::iterator, bool> ret;
//   
//   
//   ret = itemNames.insert(std::pair<std::string,std::string>(name, filename));
//   if( (!ret.second) && (ret.first->second != filename) )
//     throw(TextEngineException("Item " + name + " already exists"));
//   
//   
//   
//   boost::to_upper(name);
//   ret = itemNames.insert(std::pair<std::string,std::string>(name, filename));
//   if( (!ret.second) && (ret.first->second != filename) )
//     throw(TextEngineException("Item " + name + " already exists"));
//   
// }
// 
// std::string TextEngine::getItemFilename(std::string ItemName)
// {  
//   auto find = itemNames.find(ItemName);
//   if(find != itemNames.end())
//     return (find->second);
//   
//   return "";
// }
// 
// void TextEngine::registerNPC(std::string name, std::string location)
// {
//   std::pair<std::map<std::string,std::string>::iterator, bool> ret;
//   ret = npcRegistry.insert(std::pair<std::string,std::string>(name, location));
//   if(!ret.second)
//     throw(TextEngineException("NPC already registered: " + name));
// }
// 
// std::string TextEngine::locateNPC(std::string name)
// {
//   auto found = npcRegistry.find(name);
//   if(found == npcRegistry.end())
//     return "";
//   
//   return found->second;
// }

/////////////////////////////////////////////////////////////////////////////////

int TextEngine::getRandomNumber(int min, int max)
{
  size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dist(min, max);
  
  return ( dist(gen) );
}

/////////////////////////////////////////////////////////////////////////////

//LuaContext* TextEngine::getLuaContext() { return api->getLuaContext(); }

////////////////////////////////////////////////////////////////////////////////

// void TextEngine::initLuaApi()
// {
//   LuaContext *lua = api->getLuaContext();
//   // Engine Related
//   lua->registerFunction("addMessage", &LuaAPI::addMessage);
//   lua->registerFunction("doCommand", &LuaAPI::doCommand);
//   lua->registerFunction("doCommandSilent", &LuaAPI::doCommandSilent);
//   lua->registerFunction("getRandomNumber", &LuaAPI::getRandomNumber);
//   lua->registerFunction("setGameOver", &LuaAPI::setGameOver);
//   lua->registerFunction("runScript", &LuaAPI::runScript);
//   lua->registerFunction("runLuaCode", &LuaAPI::runLuaCode);
//   lua->registerFunction("registerCommand", &LuaAPI::registerCommand);
//   // Direction Related:
//   lua->writeVariable("dirNorth", static_cast<int>(Direction::North));
//   lua->writeVariable("dirSouth", static_cast<int>(Direction::South));
//   lua->writeVariable("dirEast", static_cast<int>(Direction::East));
//   lua->writeVariable("dirWest", static_cast<int>(Direction::West));
//   lua->writeVariable("dirUp", static_cast<int>(Direction::Up));
//   lua->writeVariable("dirDown", static_cast<int>(Direction::Down));
//   // Room Related:
//   lua->registerFunction("roomExists", &LuaAPI::roomExists);
//   lua->registerFunction("roomHasNpc", &LuaAPI::roomHasNPC);
//   lua->registerFunction("setRoomDescription", &LuaAPI::setRoomDescription);
//   lua->registerFunction("getRoomDescription", &LuaAPI::getRoomDescription);
//   lua->registerFunction("setRoomVisited", &LuaAPI::setRoomVisited);
//   lua->registerFunction("getRoomVisited", &LuaAPI::getRoomVisited);
//   lua->registerFunction("getRoomShortName", &LuaAPI::getRoomShortName);
//   lua->registerFunction("setRoomName", &LuaAPI::setRoomName);
//   lua->registerFunction("getRoomName", &LuaAPI::getRoomName);
//   lua->registerFunction("setRoomLookDescription", &LuaAPI::setRoomLookDescription);
//   lua->registerFunction("getRoomLookDescription", &LuaAPI::getRoomLookDescription);
//   lua->registerFunction("getTableOfNpcs", &LuaAPI::getTableOfNpcs);
//   lua->registerFunction("checkIfExitLocked", &LuaAPI::checkIfExitLocked);
//   lua->registerFunction("setExitLocked", &LuaAPI::setExitLocked);
//   lua->registerFunction("checkExitVisible", &LuaAPI::checkExitVisible);
//   lua->registerFunction("setExitVisible", &LuaAPI::setExitVisible);
//   // Character Related:
//   lua->registerFunction("characterIsAlive", &LuaAPI::characterIsAlive);
//   lua->registerFunction("setPlayerHealth", &LuaAPI::setPlayerHealth);
//   lua->registerFunction("getPlayerHealth", &LuaAPI::getPlayerHealth);
//   lua->registerFunction("setPlayerMoney", &LuaAPI::setPlayerMoney);
//   lua->registerFunction("getPlayerMoney", &LuaAPI::getPlayerMoney);
//   lua->registerFunction("setCharacterDescription", &LuaAPI::setCharacterDescription);
//   lua->registerFunction("getCharacterDescription", &LuaAPI::getCharacterDescription);
//   lua->registerFunction("setPlayerLocation", &LuaAPI::setPlayerLocation);
//   lua->registerFunction("getCharacterLocation", &LuaAPI::getCharacterLocation);
//   lua->registerFunction("setCharacterMoney", &LuaAPI::setCharacterMoney);
//   lua->registerFunction("getCharacterMoney", &LuaAPI::getCharacterMoney);
//   lua->registerFunction("setCharacterHealth", &LuaAPI::setCharacterHealth);
//   lua->registerFunction("getCharacterHealth", &LuaAPI::getCharacterHealth);
//   // Item and Inventory related
//   lua->registerFunction("playerAddItem", &LuaAPI::playerAddItem);
//   lua->registerFunction("playerRemoveItem", &LuaAPI::playerRemoveItem);
//   lua->registerFunction("roomAddItem", &LuaAPI::roomAddItem);
//   lua->registerFunction("roomRemoveItem", &LuaAPI::roomRemoveItem);
//   lua->registerFunction("playerHasItem", &LuaAPI::playerHasItem);
//   lua->registerFunction("roomHasItem", &LuaAPI::roomHasItem);
//   lua->registerFunction("getPlayerInvTable", &LuaAPI::getPlayerInvTable);
//   lua->registerFunction("getRoomInvTable", &LuaAPI::getRoomInvTable);
//   lua->registerFunction("checkContainerLocked", &LuaAPI::checkContainerLocked);
//   lua->registerFunction("setContainerLocked", &LuaAPI::setContainerLocked);
//   lua->registerFunction("putItemInItem", &LuaAPI::putItemInItem);
//   lua->registerFunction("getItemVisibility", &LuaAPI::getItemVisibility);
//   lua->registerFunction("setItemVisibility", &LuaAPI::setItemVisibility);
//   lua->registerFunction("setItemObtainable", &LuaAPI::setItemObtainable);
//   lua->registerFunction("getItemObtainable", &LuaAPI::getItemObtainable);
//   
//   lua->writeVariable("te", LuaAPI{this});
// }

//////////////////////////////////////////////////////////////////////////////////////////

// std::map<std::string, std::string> TextEngine::getItemNames()
// {
//   return itemNames;
// }
// 
// void TextEngine::setItemNames(std::map<std::string, std::string> itemNames)
// {
//   this->itemNames = itemNames;
// }
// 
// std::map<std::string, std::string> TextEngine::getNPCRegistry()
// {
//   return npcRegistry;
// }
// 
// void TextEngine::setNPCRegistry(std::map<std::string, std::string> npcRegistry)
// {
//   this->npcRegistry = npcRegistry;
// }