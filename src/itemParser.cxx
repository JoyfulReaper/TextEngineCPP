/*
 TextEngine: itemParser.cxx
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
 * @file itemParser.cxx
 * @author Kyle Givler
 */

#include "itemParser.hpp"
#include "itemBuilder.hpp"
#include "inventory.hpp"
#include "textEngineException.hpp"

typedef std::pair<std::string,bool> config;

std::map<std::string,bool> ItemParser::setObjectConfig()
{
  std::map<std::string,bool> objectConfig;
  objectConfig.insert(config("description", false));
  objectConfig.insert(config("name", false));
  objectConfig.insert(config("location", false));
  objectConfig.insert(config("obtainable", true));
  objectConfig.insert(config("visible", true));
  objectConfig.insert(config("container", true));
  objectConfig.insert(config("invCapacity", true));
  return objectConfig;
}

std::vector<std::map<std::string,std::string>> ItemParser::parseItems(std::string basePath)
{
  boost::filesystem::path fullPath(basePath);
  boost::filesystem::path items("/items");
  fullPath += items;
  
  if(!boost::filesystem::exists(fullPath))
  {
    std::vector<std::map<std::string,std::string>> empty;
    return empty;
  }
  
  std::map<std::string,bool> objectConfig = setObjectConfig();
  std::string ext = ".lua";
  std::vector<boost::filesystem::path> files = getAllFilesWithExt(fullPath.native(), ext);
  return parseFiles(files, objectConfig);
}

void ItemParser::parseItem(std::string name, Inventory &inv, size_t number)
{
  std::string file;
  auto it = Inventory::allItems.find(name);
  if(it == Inventory::allItems.end())
    throw(TextEngineException("Unknown item: " + name));
  
  file = it->second;
  
  boost::filesystem::path fullPath(file);
  std::map<std::string,bool> objectConfig = setObjectConfig();
  std::vector<boost::filesystem::path> files;
  files.push_back(fullPath);
  
  auto result = parseFiles(files, objectConfig);
  ItemBuilder builder(inv);
  builder.buildObject(result, number);
}