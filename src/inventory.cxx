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
    throw (TextEngineException("Inventory is full"));
  
  try {
    // Item already in Inventory
    Item &theItem = getItem(item->getName());
    theItem.setQuantity(theItem.getQuantity() + number);
    size += number;
    return true;
  } catch (const TextEngineException &te) {
    // Item not yet in inventory
    auto ret = allItems.insert(std::pair<std::string, std::string>(item->getName(), item->getFilename()));
    if(!ret.second)
      return false;
    ret = allItems.insert(std::pair<std::string, std::string>(item->getUppercaseName(), item->getFilename()));
    if(!ret.second)
      return false;
    
    item->setQuantity(number);
    items.push_back(std::move(item));
    size += number;
    return true;
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
  return removeItem(item.getName(), number);
}

bool Inventory::removeItem(std::string name, size_t number)
{
  try {
    Item &theItem = getItem(name);
    if(theItem.getQuantity() > number)
    {
      theItem.removeQuantity(number);
      size -= number;
      return true;
    } else if (theItem.getQuantity() == number) {
      for(auto it = items.begin(); it != items.end(); ++it)
      {
	Item &cur = *it->get();
	if (cur.getName() == name)
	{
	  items.erase(it);
	  return true;
	}
      }
      size -= number;
      return true;
    } else {
      return false;
    }
  } catch (const TextEngineException &te) {
    return false;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

bool Inventory::hasItem(std::string name) const
{
  for(auto &item : items)
  {
    if (item->getName() == name)
      return true;
  }
  return false;
}

bool Inventory::hasItem(const Item &item) const
{
  return hasItem(item.getName());
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

std::vector<const Item*> Inventory::getAllItems() const
{
  std::vector<const Item*> all;
  for(auto &item : items)
  {
    const Item *cur = item.get();
    all.push_back(cur);
  }
  return all;
}