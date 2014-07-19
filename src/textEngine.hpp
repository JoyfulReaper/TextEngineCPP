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
#include "commandParser.hpp"
#include "map.hpp"
#include "luaAPI.hpp"

class LuaContext;
class Room;

class TextEngine
{
public:
  
  /**
   * Main constructor
   * @param gamePath Base path where lua scripts are stored
   */
  TextEngine(std::string gamePath);
  
  ///////////////////////////////////////////////////////////
  
  /**
   * Add message to message queue
   * @param message The message to add to the queue
   */
  void addMessage(const std::string message);
  
  /**
   * Get pending message from queue
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
   * @return The starting room
   */
  inline std::string getStartRoom() const { return map.getStartRoom(); }
  
  /////////////////////////////////////////////////////////////
  
  /**
   * @return the current Player
   */
  Player& getPlayer();
  
  /**
   * @return The Player's current location
   */
  std::string getPlayerLocation();
  
  /**
   * @return The Room the player is currently in
   */
  Room& getPlayerRoom();
  
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
  Map& getMap() { return map; }
  
  ///////////////////////////////////////////////////////////////
  
  /**
   * @return The base path to the game files
   */
  inline std::string getGamePath() const 
  { 
    return gamePath; 
  }
  
  /////////////////////////////////////////////////////////////////////////////
  
  /**
   * @param min
   * @param max
   * @return A random int in the range of min to max
   */
  int getRandomNumber(int min, int max);
  
  ////////////////////////////////////////////////////////////////////////////
  
  /**
   * @return The LuaContext
   */
  LuaContext& getLuaContext();
  
  ////////////////////////////////////////////////////////////////////////////
  
private:
  CommandParser commandParser;
  Player player;
  Map map;
  LuaAPI api;
  
  void initLuaApi();
  
  std::string gamePath;
  std::deque<std::string> messages;
  bool gameOver = false;
  bool gameStarted = false;
  bool ignoreMsg = false;
  
  friend class CommandParser;
};
#endif