/*
 TextEngine: inventory.hpp
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
 * @file inventory.hpp
 * @author Kyle Givler
 */

#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <string>
#include <vector>
#include <climits>
#include <memory>
#include <map>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include "serialization_adaptors.hpp"
#include "item.hpp"

class Inventory
{
public:
  virtual ~Inventory() {}
  
  Inventory();
  
  Inventory(const Inventory &obj);
  
  static std::map<std::string, std::string> allItems;
  
  /**
   * Add an item to this inventory
   * @param item The item to add
   * @param number the quantity to add
   * @return true on success, false on failure
   */
  bool addItem(std::unique_ptr<Item> item, size_t number = 1);
  
  /**
   * Add an item to this inventory
   * @param item The item to add
   * @param number number of items to add
   * @return true on success, false on failure
   */
  bool addItem(std::string name, size_t number = 1);
  
  
  /**
   * @param item The item to remove
   * @param number The number of items to remove
   * @return true on success, false on failure
   */
  bool removeItem(const Item &item, size_t number = 1);
  
  /**
   * @param name The name of the item to remove
   * @param number The number of items to remove
   * @return true on success, false on failure
   */
  bool removeItem(std::string name, size_t number = 1);
  
  /**
   * Check for item by name
   * @param name Name of item to search for
   * @return true if found, false otherwise
   */
  bool hasItem(std::string name) const;
  
  /**
   * @return true if the Inventory contains the Item, false otherwise
   * @param item The Item to check for
   */
  bool hasItem(const Item &item) const;
  
  /**
   * @param name The name of the Item to retreive
   * @return the Item if it exists, or nullptr if it does not
   */
  Item& getItem(std::string name);
  
  /**
   * @return This Inventory's capacity
   */
  inline size_t getCapacity() const { return this->capacity; }
  
  /**
   * @param cap The capacity of this Inventory
   */
  inline void setCapacity(size_t cap) { this->capacity = cap; }
  
  /**
   * @return The number of items in this Inventory
   */
  inline size_t getSize() const { return this->size; }
  
  /**
   * @return a vector containing all of the items in the Inventory
   */
  std::vector<Item*> getAllItems();
  
  inline bool isEmpty() { return (items.size() == 0); }
  
private:
  size_t capacity = UINT_MAX - 1;
  size_t size = 0;
  std::vector<std::unique_ptr<Item>> items;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & capacity;
    ar & size;
    ar & items;
  }
};
#endif