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
#include "containerItem.hpp"
#include "itemParser.hpp"
#include "itemBuilder.hpp"
#include "textEngineException.hpp"

std::map<std::string, std::string> Inventory::allItems;

Inventory::Inventory() {}

Inventory::Inventory(const Inventory &obj)
{
  this->capacity = obj.capacity;
  
  // I think this is correct
  for(auto it = obj.items.begin(); it != obj.items.end(); ++it)
  {
    Item *item = it->get();
    if(dynamic_cast<ContainerItem*>(item))
    {
      std::unique_ptr<ContainerItem> cItem( new ContainerItem(*static_cast<ContainerItem*>(item)) );
      this->addItem(std::move(cItem), item->getQuantity());
    } else {
      this->addItem(std::unique_ptr<Item>( new Item(*item)), item->getQuantity() );
    }
  }
}

bool Inventory::addItem(std::unique_ptr<Item> item, size_t number)
{
  if((size + number) > capacity)
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
    if(!ret.second && item->getFilename() != ret.first->second)
      return false;
    ret = allItems.insert(std::pair<std::string, std::string>(item->getUppercaseName(), item->getFilename()));
    if(!ret.second && item->getFilename() != ret.first->second)
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
  if((size + number) > capacity)
    throw(TextEngineException("Inventory is full"));
  
  try {
    ItemParser ip;
    ip.parseItem(name, *this, number);
  } catch (const TextEngineException &te) {
    return false;
  }
  
  return true;
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
	if (cur.getName() == name || cur.getUppercaseName() == name)
	{
	  items.erase(it);
	  size -= number;
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
    if (item->getName() == name || item->getUppercaseName() == name)
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
    if(item->getName() == name || item->getUppercaseName() == name)
      return *item;
  }
  throw (TextEngineException("Item is not in inventory: " + name));
}

std::vector<Item*> Inventory::getItems(std::string name)
{
  std::vector<Item*> results;
  for(auto &item: items)
  {
    if(item->getName() == name || item->getUppercaseName() == name)
      results.push_back(item.get());
  }
  return results;
}

std::vector<Item*> Inventory::getAllItems()
{
  std::vector<Item*> all;
  for(auto &item : items)
  {
    Item *cur = item.get();
    all.push_back(cur);
  }
  return all;
}