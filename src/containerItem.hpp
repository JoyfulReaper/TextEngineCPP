/*
 TextEngine: containerItem.hpp
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
 * @file containerItem.hpp
 * @author Kyle Givler
 * @brief An item that has an Inventory
 */

#ifndef _CONTAINER_ITEM_H_
#define _CONTAINER_ITEM_H_

#include <memory>
#include "item.hpp"
#include "inventory.hpp"

class ContainerItem : public Item
{
public:
  ContainerItem();
  
  ContainerItem(const ContainerItem &obj);
  
  /**
   * @return The ContainerItem's Inventory
   */
  inline Inventory& getInventory() { return inventory; }
  
  inline bool isLocked() { return this->locked; }
  
  inline void setLocked(bool locked) { this->locked = locked; }
  
private:
  Inventory inventory;
  bool locked = false;
  
  friend boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<Item>(*this);
    ar & locked;
    ar & inventory;
  }
};
#endif