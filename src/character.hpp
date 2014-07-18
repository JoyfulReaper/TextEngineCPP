/*
 TextEngine: character.hpp
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
 * @file character.hpp
 * @author Kyle Givler
 */

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <string>
#include "inventory.hpp"

static std::string INVAILD_FILENAME = "NULL";

class Character
{
public:
  Character();
  
  Character(const Character &obj);
  
  virtual ~Character() {}
  
  /**
   * @param name The Player's name
   */
  virtual void setName(std::string name);
  
   /**
   * @return The player's name
   */
  inline virtual std::string getName() const { return name; }
  
  inline std::string getUppercaseName() const { return upperName; }
  
    /**
   * @param desc the players description
   */
  inline virtual void setDescription(std::string desc) { this->description = desc; }

  /**
   * @return The player's description
   */
  inline virtual std::string getDescription() const { return description; }

  /**
   * @param id The location the player is at
   */
  void setLocation(std::string location);

  /**
   * @return the player's location
   */
   inline std::string getLocation() const { return location; }

  /**
   * @param amount The players health (0-100)
   */
  inline virtual void setHealth(double amount)
  {
    if(amount > 100)
      amount = 100;

    this->health = amount;
  }

  /**
   * @return The player's health (0-100)
   */
  inline virtual double getHealth() const { return this->health; }

  /**
   * @param amount The players money (most be positive)
   */
  inline virtual void setMoney(double amount)
  {
    if(amount < 0)
      amount = 0;
    
    money = amount;
  }

  /**
   * @return The amount of money the player has
   */
  inline virtual double getMoney() const { return money; }

  /**
   * @return The Character's Inventory
   */
  inline Inventory& getInventory()
  {
    return inventory;
  }
  
  /**
   * Check if this Character is alive 
   * @return true if health is >0, false if health == 0
   */
  inline virtual bool isAlive() const { return health > 0; }
  
  /**
   * You probably don't want to change this
   */
  void setFilename(std::string);
  
  /**
   * @return The file associated with this character
   */
  inline std::string getFilename() { return filename; }
  
protected:
  std::string name = "Character";
  std::string upperName = "CHARACTER";
  std::string description = "Character";
  std::string filename = INVAILD_FILENAME;
  std::string location = "";
  double health = 100;
  double money = 0;
  Inventory inventory;
};
#endif