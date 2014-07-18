/*
 * TextEngine: commandParser.cxx
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
 * @file commandParser.cxx
 * @author Kyle Givler
 */

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <memory>
#include <sstream>
#include <iomanip>
#include <climits>
#include <fstream>
#include <functional>
#include "containerItem.hpp"
#include "commandParser.hpp"
#include "textEngine.hpp"

bool CommandParser::doCommand(std::string command, TextEngine &engine)
{
  boost::trim(command);
  boost::to_upper(command);
  std::vector<std::string> cmdVec; // Vector of the command string split on spaces
  boost::split(cmdVec, command, boost::is_any_of(" "));
  
  this->lastCommand = command;
  
  if(cmdVec.size() < 1)
    return false;
  
  if(cmdVec[0] == "N" || cmdVec[0] == "S" || cmdVec[0] == "E" || cmdVec[0] == "W" || cmdVec[0] == "U" || cmdVec[0] == "D")
  {
    std::string shortCmd = "GO ";
    shortCmd.append(cmdVec[0]);
    return doCommand(shortCmd, engine);
  }
  
  // QUIT COMMAND
  if(cmdVec[0] == "QUIT" || cmdVec[0] == "Q" || cmdVec[0] == "EXIT")
  {
    engine.gameIsOver();
    return true;
  }
  
  // LOOK COMMAND
  if(cmdVec[0] == "LOOK" || cmdVec[0] == "L" || cmdVec[0] == "OBSERVE")
    return processLook(cmdVec, engine);
  
  // GO COMMAND
  if(cmdVec[0] == "GO" || cmdVec[0] == "HEAD" || cmdVec[0] == "MOVE" || cmdVec[0] == "WALK" || cmdVec[0] == "RUN")
    return processGo(cmdVec, engine);
  
  // HELP COMMAND
  if(cmdVec[0] == "HELP" || cmdVec[0] == "COMMANDS")
    return processHelp(cmdVec, engine);
  
  // SELF COMMAND
  if(cmdVec.at(0) == "SELF" || cmdVec.at(0) == "HEALTH" || cmdVec.at(0) == "MONEY" || cmdVec.at(0) == "STATUS")
    return processSelf(engine);
  
  // GET COMMAND
  if(cmdVec[0] == "GET" || cmdVec[0] == "TAKE" || cmdVec[0] == "STEAL" || cmdVec[0] == "LOOT" || cmdVec[0] == "ACQUIRE" || cmdVec[0] == "OBTAIN")
    return processGet(cmdVec, engine);
  
  // INV COMMAND
  if(cmdVec[0] == "INV" || cmdVec[0] == "INVENTORY" || cmdVec[0] == "I")
    return processInv(cmdVec, engine);
  
  // DROP COMMAND
  if(cmdVec[0] == "DROP" || cmdVec[0] == "THROW")
    return processDrop(cmdVec, engine);
  
  // SAY COMMAND
  if(cmdVec[0] == "SAY" || cmdVec[0] == "TALK" || cmdVec[0] == "YELL" || cmdVec[0] == "SCREAM" || cmdVec.at(0) == "WHISPER")
    return processSay(cmdVec, engine);
  
  // USE COMMAND
  if(cmdVec[0] == "USE" || cmdVec[0] == "EAT" || cmdVec[0] == "PULL" || cmdVec[0] == "PUSH" || cmdVec[0] == "ACTIVATE")
    return processUse(cmdVec, engine);
  
  // PUT COMMAND
  if(cmdVec[0] == "PUT")
    return processPut(cmdVec, engine);
  
  // SAVE
  if(cmdVec[0] == "SAVE")
    return processSave(cmdVec, engine);
  
  // LOAD
  if(cmdVec[0] == "LOAD")
    return processLoad(cmdVec, engine);
  
  // SCRIPT
  if (processScript(cmdVec, engine))
    return true;
  
  // INVALID COMMAND
  engine.addMessage("\nI don't understand how to do that.\n");
  return false;
}

bool CommandParser::processSave(const vector &command, TextEngine &engine)
{
//   boost::filesystem::path saveFile(engine.getGamePath());
//   saveFile += "/saves/";
//   saveFile += getObjectName(command);
//   saveFile += ".tes";
//   
//   std::ofstream saveOS(saveFile.native());
//   if(!saveOS.good())
//   {
//     engine.addMessage("Failed to save game!\n");
//     return false;
//   }
//   
//   boost::archive::text_oarchive oa(saveOS);
//   auto itemNames = engine.getItemNames();
//   auto npcRegistry = engine.getNPCRegistry();
//   auto map = engine.getMap();
//   auto player = engine.getPlayer();
//   oa << itemNames;
//   oa << npcRegistry;
//   oa << map;
//   oa << player;
//   
//   engine.addMessage("Your game has been saved!\n");
//   saveOS.close();
//   
//   return true;
  return false;
}

bool CommandParser::processLoad(const vector &command, TextEngine &engine)
{
//   boost::filesystem::path saveFile(engine.getGamePath());
//   saveFile += "/saves/";
//   saveFile += getObjectName(command);
//   saveFile += ".tes";
//   
//   std::ifstream saveIS(saveFile.native());
//   if(!saveIS.good())
//   {
//     engine.addMessage("Failed to load game: " + saveFile.string() + "\n");
//     return false;
//   }
//   boost::archive::text_iarchive ia(saveIS);
// 
//   auto itemNames = engine.getItemNames();
//   auto npcRegistry = engine.getNPCRegistry();
//   auto map = engine.getMap();
//   auto player = engine.getPlayer();  
//   ia >> itemNames;
//   ia >> npcRegistry;
//   ia >> map;
//   ia >> player;
//   engine.setItemNames(itemNames);
//   engine.setNPCRegistry(npcRegistry);
//   engine.setMap(new Map(map));
//   engine.setPlayer(new Player(player));
//   
//   engine.getMap()->getRoom(engine.getPlayer()->getLocation())->enter(Direction::Invalid);
//   
//   //TextEngine *restore;
//   //ia >> restore;
//   //delete restore;
//   
//   engine.addMessage("Your game has been loaded!\n");
//   saveIS.close();
//   
//   return true;
  return false;
}

bool CommandParser::processScript(vector &command, TextEngine &engine)
{
  std::string verb = command.at(0);
  auto cmdIt = command.begin();
  command.erase(cmdIt);
  
  std::string full = "";
  for(auto it = command.begin(); it != command.end(); ++it)
    full.append(*it + " ");
  if(full != "")
    full.pop_back();
  
  auto found = commands.find(verb);
  if(found == commands.end())
    return false;
  
  boost::filesystem::path spath = found->second;
  LuaContext &lua =  engine.getLuaContext();
  
  try {
    std::fstream sfile(spath.native());
    lua.executeCode(sfile);
    auto onCommand = lua.readVariable<std::function<void (std::string)>>("onCommand");
    onCommand(full);
    sfile.close();
  } catch (const LuaContext::WrongTypeException &wte) {
    return false;
  } catch (const LuaContext::SyntaxErrorException &see) {
    return false;
  } catch (const LuaContext::ExecutionErrorException &eee) {
    return false;
  }
  lua.writeVariable("onCommand", nullptr);
  return true;
}

bool CommandParser::registerCommand(std::string command, std::string script, TextEngine &engine)
{
//   Commands can't have a space 
  size_t space = command.find(" ");
  if(space == std::string::npos)
    return false;
  
  boost::filesystem::path spath(engine.getGamePath());
  spath += "/scripts/";
  spath += script;
  
  if(!(boost::filesystem::exists(spath)) && (boost::filesystem::is_regular_file(spath)) )
    return false;
  
  std::pair<std::map<std::string, boost::filesystem::path>::iterator, bool> ret;
  ret = commands.insert(std::pair<std::string, boost::filesystem::path>(command, spath));
  
  return ret.second;
}

// LOOK
bool CommandParser::processLook(const vector &command, TextEngine &engine)
{
  // Look at Room
  if(command.size() == 1)
  {
    engine.getMap().getRoom(engine.getPlayer().getLocation()).showFullDescription(engine);
    return true;
  }
  
  // Look in Player Inventory
  std::string object = getObjectName(command);
  Inventory &playerInv = engine.getPlayer().getInventory();
  if(playerInv.hasItem(object))
  {
    engine.addMessage("\n" + playerInv.getItem(object).getDescription() + "\n");
    return true;
  }
  
  // Look in room Inventory
  Inventory &inv = engine.getMap().getRoom(engine.getPlayer().getLocation()).getInventory();
  if(inv.hasItem(object))
  {
    Item &item = inv.getItem(object);
    engine.addMessage("\n" + item.getDescription() + "\n");
    return true;
  }
  
  // Look at NPCs
  if(engine.getPlayerRoom().hasNpc(object, engine))
  {
    auto npcs = engine.getMap().getAllNpcs(engine.getPlayerLocation());
    auto npc = npcs[0];
    engine.addMessage("\n" + npc->getDescription() + "\n");
    return true;
  }
  
  engine.addMessage("\nYou don't see that.\n");
  return false;
}

// GO
bool CommandParser::processGo(const vector &command, TextEngine &engine)
{
  Direction dir;
  auto goWhere = [&engine] {engine.addMessage("\nGo where?\n"); return false; };
  
  if(command.size() < 2 || command[1] == "")
    return goWhere();
  if ( (dir = MapSite::getDirectionFromChar(command.at(1)[0])) == Direction::Invalid )
    return goWhere();
  
  MapSite *next = engine.getPlayerRoom().getSide(dir);
  next->enter(dir, engine);
  
  return true;
}

// HELP
bool CommandParser::processHelp(const vector &command, TextEngine &engine)
{
  if(command.size() > 1)
  {
    Inventory &roomInv = engine.getPlayerRoom().getInventory();
    Inventory &playerInv = engine.getPlayer().getInventory();
    std::string object = getObjectName(command);
    
    if(roomInv.hasItem(object))
    {
      roomInv.getItem(object).useHelp(engine);
      return true;
    }
    if(playerInv.hasItem(object))
    {
      playerInv.getItem(object).useHelp(engine);
      return true;
    }
  }
  
  engine.addMessage("\nCurrently supported commands:\n");
  engine.addMessage("HELP [ITEM]: Show item's help message\n");
  engine.addMessage("GO [(N)ORTH, (S)OUTH, (E)AST, (W)EST, (U)P, (D)OWN]: Go in direction\n");
  engine.addMessage("LOOK [ITEM]: Look at room or item\n");
  engine.addMessage("GET [ITEM] [QUANTITY]: Take item\n");
  engine.addMessage("GET [ITEM] FROM [CONTAINER]: Remove item from container\n");
  engine.addMessage("DROP [ITEM]: Drop item\n");
  engine.addMessage("SAY [CREATURE]: Speak with creature\n");
  engine.addMessage("USE [ITEM SPECIFIC]: Use item\n");
  engine.addMessage("PUT [ITEM] IN [CONTAINER]\n");
  engine.addMessage("INV [ITEM]: Show inventory, or ITEM inventory if it is a container\n");
  engine.addMessage("SELF: Show information such as health and money\n");
  engine.addMessage("QUIT: Exit the game\n");
  return true; 
}

// SELF
bool CommandParser::processSelf(TextEngine &engine)
{
  auto to_string_2 = [] ( double value ) {
    std::ostringstream out;
    out << std::setprecision(2) << std::fixed << value;
    return out.str();
  };
  
  Player &player = engine.getPlayer();
  engine.addMessage("\nName: " + player.getName());
  engine.addMessage("\nDescription: " + player.getDescription());
  engine.addMessage("\nHealth: " + to_string_2( player.getHealth() ) );
  engine.addMessage("\nMoney: " + to_string_2(player.getMoney()) + "\n");
  
  return true;
}

// GET
bool CommandParser::processGet(vector &command, TextEngine &engine)
{
  std::string object;
  size_t quantity = 1;
  auto cantTake = [&engine] { engine.addMessage("You can't take that.\n"); return false; };
  
  if(command.size() < 2)
    return cantTake();
  
  // Try to take item from container item, could be improved 
  // Won't work on items with " FROM " in the name...
  auto strippedVec = command;
  auto stripIt = strippedVec.begin();
  strippedVec.erase(stripIt);
  
  std::string full = "";
  for(auto it = strippedVec.begin(); it != strippedVec.end(); ++it)
    full.append(*it + " ");
  if(full != "")
    full.pop_back();
  
  size_t pos = full.find(" FROM ");
  if(pos != std::string::npos)
  {
    std::string contained = full.substr(0, pos);
    std::string container = full.substr(pos + 6, std::string::npos);
    
    ContainerItem *containerI = nullptr;
    Item *containedI = nullptr;
    Inventory &playerInv = engine.getPlayer().getInventory();
    Inventory &roomInv = engine.getPlayerRoom().getInventory();
    
    if(roomInv.hasItem(container))
    {
      containerI = dynamic_cast<ContainerItem*>(&roomInv.getItem(container));
    }
    if(!containerI)
    {
      if(playerInv.hasItem(container))
      {
	containerI = dynamic_cast<ContainerItem*>(&playerInv.getItem(container));
      }
    }
    if(containerI)
    {
      if(containerI->isLocked())
      {
	engine.addMessage("The container is locked!\n");
	return true;
      }
      containedI = &containerI->getInventory().getItem(contained);
      if(containedI)
      {
	std::unique_ptr<Item> addItem(nullptr);
	if(dynamic_cast<ContainerItem*>(containedI))
	{
	  addItem.reset(new ContainerItem(*static_cast<ContainerItem*>(containedI)) );
	} else
	  addItem.reset(new Item(*containedI));
	
	playerInv.addItem(std::move(addItem), 1);
	addItem->onTake(engine);
	containerI->getInventory().removeItem(*containedI, 1);
	
	engine.addMessage("You took the " + contained + " from the " + container + ".\n");
	return true;
      }
    }
  }
  
  // Try to take multiple quantity
  if(command.size() >=3)
  {
    try {
      quantity = std::stoi(command.back());
      command.pop_back();
    } catch (const std::invalid_argument &ia) {
      // no quantity given
    }
  }
  
  object = getObjectName(command);
  Inventory &roomInv = engine.getPlayerRoom().getInventory();
  
  if(!roomInv.hasItem(object))
    return cantTake();
  
  Item &item = roomInv.getItem(object);
  if(!item.isObtainable())
  {
    item.onTake(engine);
    return false;
  }
  
  Inventory &playerInv = engine.getPlayer().getInventory();
  if(quantity > item.getQuantity())
  {
    engine.addMessage("The aren't enough " + item.getName() + "s to take that many!\n");
    return false;
  }
  
  bool added = (playerInv.addItem(std::unique_ptr<Item>(new Item(item)), quantity));
  bool removed = (roomInv.removeItem(item, quantity));
  if( added && removed )
  {
    if(quantity > 1)
      engine.addMessage("You took " + std::to_string(quantity) + " " + item.getName() + "s\n");
    else
      engine.addMessage("You took the " + item.getName() + "\n");
    
    return true;
  }
  return false;
}

// INV 
bool CommandParser::processInv(vector &command, TextEngine &engine)
{
  if(command.size() == 1)
  {
    Inventory &playerInv = engine.getPlayer().getInventory();
    
    size_t capacity = playerInv.getCapacity();
    std::string scapacity;
    if(capacity == UINT_MAX - 1)
      scapacity = "Practicaly Unlimited";
    else
      scapacity = std::to_string(capacity);
    
    engine.addMessage("\nItems: " + std::to_string(playerInv.getSize()) + " Capacity: " + scapacity + "\n");
    engine.addMessage("You have: \n");
    if(playerInv.isEmpty())
    {
      engine.addMessage("No items\n\n");
      return true;
    }
    
    std::string result;
    auto items = playerInv.getAllItems();
    for (auto it = items.begin(); it != items.end(); ++it)
    {
      const Item *item = *it;
      std::string name = item->getName();
      if(item->getQuantity() > 1)
	name.append(" (" + std::to_string(item->getQuantity()) + ")");
      result.append(name + ", ");
    }
    result.erase(result.length() -2, 2);
    engine.addMessage(result + "\n\n");
    return true;
  }
  
  // Check inventory of container object
  // FIXME: Only checks the first container found...
  std::string object = getObjectName(command);
  Inventory &playerInv = engine.getPlayer().getInventory();
  Inventory &roomInv = engine.getPlayerRoom().getInventory();
  Inventory *useInv = nullptr;
  
  if(playerInv.hasItem(object))
    useInv = &playerInv;
  if( (roomInv.hasItem(object)) && (!useInv))
    useInv = &roomInv;
  
  if(useInv == nullptr)
  {
    engine.addMessage("You don't see a " + object + ".\n");
    return false;
  }
  
  ContainerItem *container = dynamic_cast<ContainerItem*>(&useInv->getItem(object));
  if(!container)
  {
    engine.addMessage(object + " isn't a container!\n");
    return false;
  }
  
  if(container->isLocked())
  {
    engine.addMessage("The container is locked\n");
    return true;
  }
  
  size_t capacity = container->getInventory().getCapacity();
  std::string scapacity;
  if(capacity == UINT_MAX - 1)
    scapacity = "Practicaly Unlimited";
  else
    scapacity = std::to_string(capacity);
  
  engine.addMessage("The " + object + " contains " +  std::to_string(container->getInventory().getSize()) + " of " + scapacity + " items:\n");
  if(container->getInventory().isEmpty())
  {
    engine.addMessage("No Items\n\n");
    return true;
  }
  auto allItems = container->getInventory().getAllItems();
  std::string result;
  for(auto it = allItems.begin(); it != allItems.end(); ++it)
  {
    const Item *item = *it;
    std::string name = item->getName();
    if(item->getQuantity() > 1)
      name.append(" (" + std::to_string(item->getQuantity()) + ")");
    result.append(name + ", ");
  }
  result.erase(result.length() -2, 2);
  engine.addMessage(result + "\n");
  return true;
}

// DROP
bool CommandParser::processDrop(vector &command, TextEngine &engine)
{
  size_t quantity = 1;
  auto cantDrop = [&engine] { engine.addMessage("You can't drop that.\n"); return false; };
  if(command.size() < 2)
    return cantDrop();
  
  if(command.size() >= 3)
  {
    try{
      quantity = std::stoi(command.back());
      command.pop_back();
    } catch (const std::invalid_argument &ia) {
      // No quantity given
    }
  }
  
  std::string object = getObjectName(command);
  Inventory &playerInv = engine.getPlayer().getInventory();
  Inventory &roomInv = engine.getPlayerRoom().getInventory();
  
  if(!playerInv.hasItem(object))
    return cantDrop();
  
  Item *item = &playerInv.getItem(object);
  std::string name = item->getName();  
  
  std::unique_ptr<Item> addItem(nullptr);
  if(dynamic_cast<ContainerItem*>(item))
  {
    addItem.reset(new ContainerItem(*static_cast<ContainerItem*>(item)));
  } else
    addItem.reset(new Item(*item));
  
  bool removed = playerInv.removeItem(*item, quantity);
  bool added = roomInv.addItem(std::move(addItem), quantity);
  if( added && removed )
  {
    if(quantity == 1)
      engine.addMessage("You dropped the " + name +  ".\n");
    else if (quantity > 1)
      engine.addMessage("You dropped " + std::to_string(quantity) + " " + name + "s.\n");
    return true;
  }
  
  engine.addMessage("\nSomething went wrong, You shouldn't see this message :(\n");
  return false;
}

// SAY
bool CommandParser::processSay(vector &command, TextEngine &engine)
{
  auto allNpcs = engine.getMap().getAllNpcs(engine.getPlayerLocation());
  if(allNpcs.size() == 0)
  {
    engine.addMessage("You talk, but no one listens...\n");
    return false;
  }
  
  if(allNpcs.size() == 1)
  {
    NonPlayableCharacter *npc = allNpcs.at(0);
    std::string said = getObjectName(command);
    npc->processSpeech(said, engine);
    return true;
  }
  
  //More than one NPC (PROBABLY A BETTER WAY TO DO THIS?!)
  auto cmdIt = command.begin();
  command.erase(cmdIt); // Strip verb
  std::string full = "";
  for(auto it = command.begin(); it != command.end(); ++it)
    full.append(*it + " ");
  if(full != "")
    full.pop_back(); // Stip trailing space
    
  // Find potential matches
  size_t pos;
  std::string name;
  std::vector<std::string> matches;
  for(auto it = allNpcs.begin(); it != allNpcs.end(); ++it)
  {
    const NonPlayableCharacter *npc = *it;
    name = npc->getName();
    boost::to_upper(name);
    pos = full.rfind(name);
    if(pos != std::string::npos)
      matches.push_back(full.substr(pos, name.length()));
  }
  if(matches.size() == 0)
  {
    engine.addMessage("Say to who?\n");
    return false;
  }
  // Find best match (longest)
  std::string bestMatch;
  for(auto it = matches.begin(); it != matches.end(); ++it)
  {
    if(it->length() > bestMatch.length())
      bestMatch = *it;
  }
  
  NonPlayableCharacter *theMatch = nullptr;
  for(auto &curNpc : allNpcs)
  {
    if(curNpc->getName() == bestMatch || curNpc->getUppercaseName() == bestMatch)
      theMatch = curNpc;
  }
  full.replace(pos, name.length()+1, ""); // Remove NPC name
  boost::trim(full);
  if(full.length() == 0)
  {
    engine.addMessage("Say to what to " + theMatch->getName() + "?\n");
    return false;
  }
  
  theMatch->processSpeech(full, engine);
  return true;
}

// USE
bool CommandParser::processUse(vector &command, TextEngine &engine)
{
//   std::string verb = command.at(0);
//   auto cmdIt = command.begin();
//   command.erase(cmdIt); //strip verb
//   
//   std::string full = "";
//   for(auto it = command.begin(); it != command.end(); ++it)
//     full.append(*it + " ");
//   if(full != "")
//     full.pop_back();
//   
//   auto findMatches = [](Inventory *inv, std::string fullString) -> std::string
//   {
//     std::vector<std::string> matches;
//     size_t pos;
//     std::string name;
//     auto allItems = inv->getAllItems();
//     
//     for(auto it = allItems.begin(); it != allItems.end(); ++it)
//     {
//       const Item *item = *it;
//       name = item->getName();
//       boost::to_upper(name);
//       pos = fullString.rfind(name);
//       if(pos != std::string::npos)
// 	matches.push_back(fullString.substr(pos, name.length()));
//     }
//     
//     if(matches.size() == 0)
//       return "";
//     
//     std::string bestMatch;
//     for(auto it = matches.begin(); it != matches.end(); ++it)
//       if(it->length() > bestMatch.length())
// 	bestMatch = *it;
//       
//       return bestMatch;
//   };
//   
//   auto stripBestMatch = [&full](std::string bestMatch)
//   {
//     full.replace(0, bestMatch.length()+1, "");
//     boost::trim(full);
//     return;
//   };
//   
//   Inventory *playerInv = engine.getPlayer()->getInventory();
//   Inventory *roomInv = engine.getMap()->getRoom(engine.getPlayer()->getLocation())->getInventory();
//   if(!roomInv->isEmpty())
//   {
//     std::string itemMatch = findMatches(roomInv, full);
//     if(itemMatch != "")
//     {
//       stripBestMatch(itemMatch);
//       //std::cerr << "DEBUG: using: " << itemMatch << " full: " << full << std::endl;
//       roomInv->getItem(itemMatch)->useItem(full);
//       return true;
//     }
//   }
//   
//   if(!playerInv->isEmpty())
//   {
//     std::string itemMatch = findMatches(playerInv, full);
//     if(itemMatch != "")
//     {
//       stripBestMatch(itemMatch);
//       //std::cerr << "DEBUG: using: " << itemMatch << " full: " << full << std::endl;
//       Item *matchItem = playerInv->getItem(itemMatch);
//       matchItem->useItem(full);
//       return true;
//     }
//   }
//   
//   engine.addMessage("You can't " + verb + " that!\n");
//   return false;
  return false;
}

// PUT 
// TODO: Allow objects with " in " in their name
// Puts the item in the first container found with the given name
/**
 * @bug Item name cannot contain " in "!
 */
bool CommandParser::processPut(vector &command, TextEngine &engine)
{
//   auto cmdIt = command.begin();
//   command.erase(cmdIt); //strip verb
//   
//   std::string full = "";
//   for(auto it = command.begin(); it != command.end(); ++it)
//     full.append(*it + " ");
//   if(full != "")
//     full.pop_back();
//   
//   size_t pos = full.find(" IN ");
//   if(pos == std::string::npos)
//   {
//     engine.addMessage("Put what in what?");
//     return false;
//   }
//   
//   std::string contained = full.substr(0, pos);
//   std::string container = full.substr(pos + 4, std::string::npos);
//   //std::cerr << "DEBUG: " << " '"<< container << "' " << " '" << contained <<"' " << std::endl;
//   
//   if(container.length() == 0 || contained.length() == 0)
//   {
//     engine.addMessage("Put what in what?");
//     return false;
//   }
//   
//   ContainerItem *containerI = nullptr;
//   Item *containedI = nullptr;
//   Inventory *playerInv = engine.getPlayer()->getInventory();
//   Inventory *roomInv = engine.getMap()->getRoom(engine.getPlayer()->getLocation())->getInventory();
//   Inventory *removeInv = nullptr;
//   assert(playerInv && roomInv);
//   
//   if(roomInv->hasItem(container))
//   {
//     containerI = dynamic_cast<ContainerItem*>(roomInv->getItem(container));
//     if(!containerI)
//     {
//       engine.addMessage(container + " is not a container!\n");
//       return false;
//     }
//   }
//   if(roomInv->hasItem(contained))
//   {
//     containedI = roomInv->getItem(contained);
//     removeInv = roomInv;
//   }
//   
//   if(!containerI)
//   {
//     if(playerInv->hasItem(container))
//     {
//       containerI = dynamic_cast<ContainerItem*>(playerInv->getItem(container));
//       if(!containerI)
//       {
// 	engine.addMessage(container + " is not a container!\n");
// 	return false;
//       }
//     }
//   }
//   if(!containedI)
//   {
//     if(playerInv->hasItem(contained))
//     {
//       containedI = playerInv->getItem(contained);
//       removeInv = playerInv;
//     }
//   }
//   
//   if(!containerI)
//   {
//     engine.addMessage("You don't see a " + container + ".\n");
//     return false;
//   }
//   if(!containedI)
//   {
//     engine.addMessage("You don't see a " + contained + ".\n");
//     return false;
//   }
//   
//   if(containerI->isLocked())
//   {
//     engine.addMessage("The container is locked!\n");
//     return true;
//   }
//   
//   if(containedI == containerI)
//   {
//     engine.addMessage("I don't think that should be allowed! The world might end!\n");
//     return false;
//   }
//   
//   Item *tempItem = new Item(containedI);
//   tempItem->setQuantity(0);
//   containerI->getInventory()->addItem(tempItem, 1);
//   removeInv->removeItem(containedI, 1);
//   
//   delete tempItem;
//   engine.addMessage("You put the " + contained + " in the " + container + ".\n");
//   
//   return true;
  return false;
}

std::string CommandParser::getObjectName(const vector &command)
{
  std::string object;
  for(size_t i = 1; i < command.size(); i++)
  {
    object.append(command.at(i));
    if(i != command.size() - 1)
      object.append(" ");
  }
  return object;
}