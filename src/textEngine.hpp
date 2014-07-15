/*
 TextEngine: TextEngine.hpp
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
 * @file TextEngine.hpp
 * @author Kyle Givler
 * 
 * @mainpage TextEngine is a game engine for easily creating interactive text adventure games.
 * @section Information
 * This project aims provide an easy to use and cross platform mechanism for creating text adventure games 
 * using Lua as the sripting language.
 */

#ifndef _TEXT_ENGINE_H_
#define _TEXT_ENGINE_H_

#include <memory>
#include <string>
#include <deque>
#include <map>
#include "player.hpp"

class TextEngine
{
public:
  
  TextEngine(std::string gamePath);
  
  ///////////////////////////////////////////////////////////
  
  /**
   * Add message to message queue
   * @param message The message to add to the queue
   */
  void addMessage(const std::string message);
  
  /**
   * Get pending messages
   * @return Pending messages
   */
  std::string getMessage();
  
  /**
   * Check if there is a message in the queue
   * @return true if there is a message in the queue, false otherwise
   */
  bool hasMessage() const;
  
  /**
   * @return A string consisting of all the messages in the queue
   */
  std::string getAllMessages();
  
  /**
   * @param ignore Make addMessage ignore new messages
   */
  inline void ignoreMessages(bool ignore) { this->ignoreMsg = ignore; }
  
  /**
   * @return true if messages are being ignored, false if they are being added
   */
  inline bool ignoringMessages() { return this->ignoreMsg; }
  
  //////////////////////////////////////////////////////////////
  
  /**
   * @return true if the command was processed sucessfully, false otherwise
   */
  bool processCommand(std::string cmd);
  
  /**
   * @return The last command given
   */
  std::string getLastCommand() const;
  
  /**
   * Register a command
   */
  bool registerCommand(std::string verb, std::string file);
  
  /**
   * @param room The room to start to game in
   */
  void setStartRoom(std::string room);
  
  /**
   * @return The starting room
   */
  inline std::string getStartRoom() const { return startRoom; }
  
  /////////////////////////////////////////////////////////////
  
  /**
   * @return the current Player
   */
  Player& getPlayer();
  
  //////////////////////////////////////////////////////////////
  
  /**
   * @return true if the game has ended, false if it is in progress
   */
  bool isGameOver() const;
  
  /**
   * End the game
   */
  void gameIsOver();
  
  /////////////////////////////////////////////////////////////////
  
  /**
   * @return The TextEngine's Map
   */
  //Map* getMap() const;
  
  /**
   * @param map The map for the TextEngine to use
   */
  //void setMap(Map *map);
  
  ///////////////////////////////////////////////////////////////
  
  /**
   * @return The base path to the game files
   */
  inline std::string getGamePath() const 
  { 
    return gamePath; 
  }
  
  ///////////////////////////////////////////////////////////////
  
  /**
   * Tell the TextEngine that that an item with the given name exists.
   * This should probably only be called by the ItemBuilder.
   * @param name The name of the item to "teach" the TextEngine
   * @param filename The file of the item to add
   * @throws TextEngineException if the Item id is already known
   */
  //void teachItem(std::string name, std::string filename);
  
  /**
   * @return The filename of the given item if it exists or "" if it doesn't
   */
  //std::string getItemFilename(std::string ItemName);
  
  //void registerNPC(std::string name, std::string location);
  
  //std::string locateNPC(std::string name);
  
  /////////////////////////////////////////////////////////////////////////////
  
  int getRandomNumber(int min, int max);
  
  /////////////////////////////////////////////////////////////////////////////
  

  
  ////////////////////////////////////////////////////////////////////////////
  
  
private:
  //CommandParser commandParser;
  Player player;
  
  std::string startRoom = "";
  std::string gamePath;
  //std::map<std::string,std::string> itemNames;
  //std::map<std::string,std::string> npcRegistry; 
  //std::unique_ptr<Map> map;
  std::deque<std::string> messages;
  bool gameOver = false;
  bool gameStarted = false;
  bool ignoreMsg = false;
};
#endif