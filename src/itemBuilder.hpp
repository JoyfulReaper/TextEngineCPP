/*
 TextEngine: itemBuilder.hpp
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
 * @file itemBuilder.hpp
 * @author Kyle Givler
 */

#ifndef _ITEM_BUILDER_H_
#define _ITEM_BUILDER_H_

#include "builder.hpp"

class Inventory;
class Map;

class ItemBuilder : public Builder
{
public:
  ItemBuilder(Inventory &inv) : map(nullptr), inventory(&inv) {}
  ItemBuilder(Map &map) : map(&map), inventory(nullptr) {}
  
  virtual ~ItemBuilder() {}
  
  virtual void buildObjects(std::vector<std::map<std::string,std::string>> &ObjectConfig);
  
  virtual void buildObject(std::vector<std::map<std::string,std::string>> &itemConfig, int quantity = 1);
  
private:
  Map *map;
  Inventory *inventory = nullptr;
  int quantity = -1;
  
  inline Inventory* getInventory() { return inventory; }
  
  inline void setQuantity(int number) { quantity = number; }
  
  inline int getQuantity() { return quantity; }
};
#endif