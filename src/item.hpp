/*
 TextEngine: item.hpp
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
 * @file item.hpp
 * @author Kyle Givler
 */

#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

static const std::string INVALID_ITEM_FILENAME = "NULL";

class TextEngine;

class Item
{
public:
  Item(const Item &obj);
  
  Item();
  
  virtual ~Item() {}
  
  /**
   * @param name Name of item, must be unique
   */
  void setName(std::string name);
  
  /**
   * @return Item's name
   */
  inline std::string getName() const { return name; }
  
  /**
   * @return the item's name in uppercase
   */
  inline std::string getUppercaseName() const { return uppercaseName; }
  
  /**
   * @param desc Item's description
   */
  inline void setDescription(std::string desc) { this->description = desc; }
  
  /**
   * @return Item's description
   */
  inline std::string getDescription() const { return description; }
  
  /**
   * @return Lua file associated with item
   */
  inline std::string getFilename() const { return filename; }
  
  /**
   * @param canBePickedUp Whether or not the item can be put in a Player inventory
   */
  inline void setObtainable(bool canBePickedUp) { this->obtainable = canBePickedUp; }
  
  /**
   * @return Wheater or not the item is obtainable by Players
   */
  inline bool isObtainable() const { return obtainable; }
  
  /**
   * @return True if visible to players, false if not
   */
  inline bool isVisible() const { return visible; }
  
  /**
   * @param  visible determin if the object shows up in the list of objects in the room
   */
  inline void setVisible(bool visible) { this->visible = visible; }
  
  /**
   * @return the quantity of this item
   */
  inline size_t getQuantity() const { return quantity; }
  
  /**
   * @param number The amount to add to the quantity
   */
  inline void addQuantity(size_t number) { quantity += number; }
  
  /**
   * @param number the number to set at the quantity
   */
  bool setQuantity(size_t number);
  
  /**
   * @param number the amound to remove from the quantity
   */
  bool removeQuantity(size_t number);
  
  /**
   * Called on command USE ITEM {PARAMS}
   */
  virtual void useItem(std::string command, TextEngine &engine);
  
  /**
   * Called on HELP ITEM
   */
  virtual void useHelp(TextEngine &engine);
  
  /**
   * Called on TAKE ITEM
   */
  virtual void onTake(TextEngine &engine);
  
  /**
   * Set filename associated with this item
   * You probably don't want to change this
   */
  void setFilename(std::string filename);
  
  
protected:
  bool obtainable = true;
  bool visible = true;
  size_t quantity = 1;
  std::string name;
  std::string uppercaseName;
  std::string description;
  std::string filename = INVALID_ITEM_FILENAME;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & obtainable;
    ar & visible;
    ar & quantity;
    ar & name;
    ar & uppercaseName;
    ar & description;
    ar & filename;
  }
};
#endif