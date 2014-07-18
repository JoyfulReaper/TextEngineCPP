/*
 TextEngine: itemParser.hpp
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
 * @file itemParser.hpp
 * @author Kyle Givler
 */

#ifndef _ITEM_PARSER_H
#define _ITEM_PARSER_H

#include <string>
#include <map>
#include "parser.hpp"

class Inventory;

class ItemParser : public Parser
{
public:
  
  ItemParser() {}
  
  virtual ~ItemParser() {}
  
  virtual std::vector<std::map<std::string,std::string>> parseItems(std::string basePath);
  
  //virtual void parseItem(std::string itemName, std::string location);
  
  virtual void parseItem(std::string name, Inventory &inv, size_t number = 1);
  
  /**
   * @return a map of strings to check for in the file to parse, and a bool to indicate if the string is optional
   */
  virtual std::map<std::string,bool> setObjectConfig();
private:
};

#endif