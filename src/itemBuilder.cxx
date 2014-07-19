/*
 * TextEngine: itemBuilder.cxx
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
 * @file itemBuilder.cxx
 * @author Kyle Givler
 */


#include <boost/algorithm/string.hpp>
#include <memory>
#include <cassert>
#include "map.hpp"
#include "itemBuilder.hpp"
#include "item.hpp"
#include "containerItem.hpp"
#include "textEngineException.hpp"

using namespace boost;

void ItemBuilder::buildObject(std::vector<std::map<std::string,std::string>> &itemConfig, int quantity)
{
  setQuantity(quantity);
  buildObjects(itemConfig);
}

void ItemBuilder::buildObjects(std::vector<std::map<std::string,std::string>> &itemConfig)
{  
  for(auto it = itemConfig.begin(); it != itemConfig.end(); ++it)
  {
    auto config = *it;
    size_t obtainable;
    size_t visible;
    size_t container;
    std::string addRoom;
    std::unique_ptr<Item> item;
    
    try{
      if(config["container"] == "") // Are we creating a ContainerItem?
	container = 0;
      else
	container = std::stoi(config["container"]);
      if(container)
      {
	item.reset(new ContainerItem);
	if(config["invCapacity"] != "")
	{
	  size_t cap = std::stoi(config["invCapacity"]);
	  static_cast<ContainerItem*>(item.get())->getInventory().setCapacity(cap);
	}
      }
      else
	item.reset(new Item); // Not a container
	
	if(config["obtainable"] == "") // Is the item obtainable by the player?
	  obtainable = 1;
	else
	  obtainable = std::stoi(config["obtainable"]);
	if(obtainable)
	  item->setObtainable(true);
	else
	  item->setObtainable(false);
	
	if(config["visible"] == "") // Should the item be visible in the list of items in the room?
	  visible = 1;
	else
	  visible = std::stoi(config["visible"]);
	if(visible)
	  item->setVisible(true);
	else
	  item->setVisible(false);
	
	std::string name = config["name"];
	if(name == "player")
	  throw(TextEngineException("'player' is an invalid name for an item!"));
	
	item->setName(name);
	item->setDescription(config["description"]);
	item->setFilename(config["filename"]);
	
    } catch (const std::invalid_argument &ia) {
      throw(TextEngineException("Invaild item configuration: " + config["filename"]));
    }
    int quantity = getQuantity();
    
    if(quantity == -1) // Need to parse location
    {
      // Split locations string: [addRoom | 'player']:quantity
      std::vector<std::string> locVector;
      split(locVector, config["location"], is_any_of(":"));
      if(locVector.size() == 0 || locVector.size() % 2 != 0)
      {
	throw (TextEngineException("Malformed location string in item " + config["name"]));
      }
      
      // Add items to locations
      for(size_t i = 0; i < locVector.size(); i += 2)
      {
	std::unique_ptr<Item> copyItem;
	if(container)
	  copyItem.reset(new ContainerItem(*static_cast<ContainerItem*>(item.get())));
	else
	  copyItem.reset(new Item(*item));
	
	try {
	  quantity = std::stoi(locVector[i+1]);
	} catch (const std::invalid_argument &ia) {
	  throw (TextEngineException("Malformed location string in item " + config["name"]));
	}
	
	addRoom = locVector[i];
	
	
	if(!map->roomExists(addRoom))
	  throw (TextEngineException("Trying to add " + config["name"] + " to invalid location: " + addRoom));
	
	map->getRoom(addRoom).getInventory().addItem(std::move(item), quantity);
	
	if(container)
	  item.reset(new ContainerItem(*static_cast<ContainerItem*>(copyItem.get())));
	else
	  item.reset(new Item(*copyItem));
      }
    } // End location parsing
    else
    { // add to given inventory
      assert(inventory != nullptr);
      if(!inventory->addItem(std::move(item), quantity))
	throw(TextEngineException("Failed to add item"));
    }
  } // End main loop
} // End buildObjects()