/*
 * TextEngine: inventory.cxx
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
 * @file inventory.cxx
 * @author Kyle Givler
 */

#include <algorithm>
#include "inventory.hpp"
#include "textEngineException.hpp"

Inventory::Inventory() {}

Inventory::Inventory(const Inventory &obj)
{
  this->capacity = obj.capacity;
  this->size = obj.size;
  //Copy items
}

bool Inventory::addItem(std::unique_ptr<Item> item, size_t number)
{
  if(size + number > capacity)
    ; // throw inv full excpt?
  
  try {
    Item &theItem = getItem(item->getName());
    theItem.setQuantity(theItem.getQuantity() + number);
    size += number;
    return true;
  } catch (const TextEngineException &te) {
  }
  return false;
}

bool Inventory::addItem(std::string name, size_t number)
{
  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////

bool Inventory::removeItem(const Item &item, size_t number)
{
  return false;
}

bool Inventory::removeItem(std::string name, size_t number)
{
  return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool Inventory::hasItem(std::string name)
{
  for(auto &item : items)
  {
    if (item->getName() == name)
      return true;
  }
  return false;
}

bool Inventory::hasItem(const Item &item)
{
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////

Item& Inventory::getItem(std::string name)
{
  for(auto &item : items)
  {
    if(item->getName() == name)
      return *item;
  }
  throw (TextEngineException("Item is not in inventory: " + name));
}

std::vector<const Item*> Inventory::getAllItems()
{
}