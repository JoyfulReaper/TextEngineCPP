/*
 TextEngine: luaAPI.hpp
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
 * @file luaAPI.hpp
 * @author Kyle Givler
 * 
 * TODO:
 * Largely un-tested and could use improvements, especially relating to NPCs!
 * 
 */

#ifndef _LUA_API_H_
#define _LUA_API_H_

#include <string>
#include <map>
#include <memory>
#include "thirdParty/luawrapper/LuaContext.hpp"

class TextEngine;

class LuaAPI
{
public:
  LuaAPI(TextEngine &engine);
  
  LuaContext& getLuaContext();
  
  // Engine Related ///////////////////////////////////////////////////////////////
  
  /**
   * Add a message to the message queue.
   * Please note it can be hard to perdict where this message will appear, but I have tried
   * to take steps to have it displayed at a reasonable place.
   * @param message The message to add
   */
  void addMessage(std::string message);
  
  /**
   * Run a command as if the user had typed it
   * @param command The command to run
   * @return true on success, false on failure
   */
  bool doCommand(std::string command);
  
  /**
   * Run a command as if the user had typed it, but don't addMessage()s (no ouput from commands)
   * @param command The command to run 
   * @return true on success, false on failure
   */
  bool doCommandSilent(std::string command);
  
  /**
   * Get a random number in a given range
   * @param min min of range
   * @param max max of range
   * @return A random number in the range of min to max
   */
  int getRandomNumber(int min, int max);
  
  /**
   * End the game, either win or loss
   * Just makes the TextEngine return true to isGameOver()
   */
  void setGameOver();
  
  /**
   * @param script the filename of the script to run (in scripts dir) 
   * @return true on success
   */
  bool runScript(std::string script);
  
  /**
   * @param luaCode The lua code to execute 
   * @return true on success, false on failure
   */
  bool runLuaCode(std::string luaCode);
  
  /**
   * @param verb Command to register
   * @param file Lua script under /scripts to run on verb 
   * @return true on success, false on failure
   */
  bool registerCommand(std::string verb, std::string file);
  
  // Room related ////////////////////////////////////////////////////////////////
  
  /**
   * @return true if it exists, false if it doesn't
   */
  bool roomExists(std::string room);
  
  /**
   * Sets the description for the given room
   * @param desc The new description
   * @param room The short name of the Room
   * @return true on success, false on failure
   */
  bool setRoomDescription(std::string desc, std::string room);
  
  /**
   * @param room the short name of the room to get the description of 
   * @return the description of the given room, or empty string if it doesnt exists
   */
  std::string getRoomDescription(std::string room);
  
  /**
   * Determine if the player has visited the room or not
   * Warning: returns false if the room doesn't exist!
   * @param room The Room to check 
   * @return true if visited, false if not visited or doesn't exist
   */
  bool getRoomVisited(std::string room);
  
  /**
   * Set a room as visited or not visited
   * @param room The Room to set visited state
   * @param visited the true/false visited state
   * @return true on sucess, false on failure (room doesn't exist)
   */
  bool setRoomVisited(std::string room, bool visited);
  
  /**
   * Get the short name of the Room the player is currently in
   * @return short name of room Player's in
   */
  std::string getRoomShortName();
  
  /**
   * @param name The new name for the room
   * @param room the short name of the room
   */
  bool setRoomName(std::string name, std::string room);
  
  /**
   * @param room The short name of the room to get the full name of
   * @return the name of the room
   */
  std::string getRoomName(std::string room);
  
  /**
   * @param desc The look description
   * @param room The room to set the look description for
   * @return true on success, false if room doesn't exist
   */
  bool setRoomLookDescription(std::string desc, std::string room);
  
  /**
   * @param room to get the look description of
   * @return the room's look description, empty string if it doesn't exist
   */
  std::string getRoomLookDescription(std::string room);
  
  /**
   * @param room The room to look in
   * @param who The NPC to look for
   * @return true if the room has the npc
   */
  bool roomHasNPC(std::string who, std::string room);
  
  /**
   * @param room The room to look in
   * @return A table of NPCs in the given room 
   */
  std::map<int, std::string> getTableOfNpcs(std::string room);
  
  /**
   * @param room The room to look in 
   * @param dir The direction to look in (dirNorth, dirSouth, etc)
   * @return true if locked, false if unlocked OR ON FAILURE!!!
   */
  bool checkIfExitLocked(std::string room, int dir);
  
  /**
   * @param locked true to lock, false to unlock 
   * @return true on success, false on failure
   */
  bool setExitLocked(std::string room, int dir, bool locked);
  
  /**
   * @return true if visible, false if invisible OR ON FAILIRE
   */
  bool checkExitVisible(std::string room, int dir);

  /**
   * @return true on success, false on failure
   */  
  bool setExitVisible(std::string room, int dir, bool visible);
  
  // Character Related /////////////////////////////////////////////////////////////////////////
  // Use "player" for the player, or the Character's name
  // Note: MOST of these functions will change the settings for ALL NPCs with the given name
  // in ALL of their location.
  
  /**
   * @param room The location to put the Player in
   * @return true on success, false if the room doesn't exist
   */
  bool setPlayerLocation(std::string room);
  
  /**
   * @param amount the amount of money the player has
   */
  bool setPlayerMoney(double amount);
  
  /**
   * @return The amount of money the player has
   */
  double getPlayerMoney();

  /**
   * @return The Players health
   */
  double getPlayerHealth();
  
  /**
   * @param amount Amount of health to set Player as having
   * @return true on success, false on failure
   */
  bool setPlayerHealth(double amount);
  
  /**
   * @param who The name of the Character, or "player"
   * @param desc The Character's description
   * @return true on sucess, false on failure
   */
  bool setCharacterDescription(std::string desc, std::string who);
  
  /**
   * @param who The name of the Character, or "player"
   * @return The Character's description
   */
  std::string getCharacterDescription(std::string who);
  
  /**
   * @param who The name of the Character, or "player"
   * @return The Character's locations in the format: room1:room2:room3
   */
  std::string getCharacterLocation(std::string who);
  
  /**
   * @param who The name of the Character
   * @param amount The amount to set the Character money to (amount >= 0)
   * @param where The location of the Character to set the money of 
   * @return true on success, false on failure
   */
  bool setCharacterMoney(double amount, std::string who, std::string where);
  
  /**
   * @param who The name of the Character
   * @param where The location of the Character to get the money of
   * @return The amount of money the Character has, or -1 on failure
   */
  double getCharacterMoney(std::string who, std::string where);
  
  /**
   * @param who The name of the Character
   * @param where Location of Character
   * @param amount The amount to set the Character's health too (0-100)
   * @return true on success, false on failure
   */
  bool setCharacterHealth(double amount, std::string who, std::string where);
  
  /**
   * @param who The name of the Character
   * @param where Location on Character
   * @return The amount of health the Character has, -1 on failure
   */
  double getCharacterHealth(std::string who, std::string where);
  
  /**
   * @param who The name of the Character 
   * @param where Location of the Character
   */
  bool characterIsAlive(std::string who, std::string where);
  
  // Item and Inventory related ///////////////////////////////////////////////////
  
  /**
   * @param name Name of item to add
   * @param num Number of items to add  
   * @return true on success, false on failure
   */
  bool playerAddItem(std::string name, size_t num);
  
   /**
   * @param name Name of item to remove
   * @param num Number of items to remove 
   * @return true on success, false on failure
   */
  bool playerRemoveItem(std::string name, size_t num);
  
   /**
   * @param name Name of item to add 
   * @param num Number of items to add 
   * @param room The room to add the item to
   * @return true on success, false on failure
   */
  bool roomAddItem(std::string name, size_t num, std::string room);
  
   /**
   * @param name Name of item to remove
   * @param num Number of items to remove
   * @param room The room to remove the item from
   * @return true on success, false on failure
   */
  bool roomRemoveItem(std::string name, size_t num, std::string room);
  
  /**
   * @param name The name of the item 
   * @return true if the player has the item, false otherwise
   */
  bool playerHasItem(std::string name);
  
   /**
   * @param name The name of the item 
   * @return true if the Room has the item, false otherwise
   */
  bool roomHasItem(std::string name, std::string room);
  
  std::map<int, std::string> getRoomInvTable(std::string room);
  
  std::map<int, std::string> getPlayerInvTable();
  
  /**
   * @return true if locked, false if unlocked OR ON ERROR!
   */
  bool checkContainerLocked(std::string item, std::string room);
  
  /**
   * @return true on sucess, false on failure
   */
  bool setContainerLocked(std::string item, std::string room, bool locked);
  
  /**
   * @return The capacity of the player's inventory
   */
  size_t getPlayerInvCapacity();
  
  /**
   * @return the number of items in the player's inventory
   */
  size_t getPlayerInvSize();
  
  /**
   * @param capacity The capacity of the Player's Inventory
   */
  void setPlayerInvCapacity(size_t capacity);
  
  /**
   * @param container Item to container contained item 
   * @param contained Item to put in container
   * @param num Quanity to add
   * @param room Room the container is in
   */
  bool putItemInItem(std::string container, std::string contained, size_t num, std::string room);
  
  bool getItemVisibility(std::string name, std::string room);
  
  bool setItemVisibility(std::string name, std::string room, bool visible);
  
  bool getItemObtainable(std::string name, std::string room);
  
  bool setItemObtainable(std::string name, std::string room, bool obtainable);
  
private:
  LuaContext lua;
  TextEngine *engine;
};

#endif