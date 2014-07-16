/*
 TextEngine: NPCParser.cxx
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
 * @file NPCParser.cxx
 * @author Kyle Givler
 */

#include "config.h"
#include "npcParser.hpp"
#include "npcBuilder.hpp"
#include "inventory.hpp"

typedef std::pair<std::string,bool> conf;

std::map<std::string,bool> NPCParser::setObjectConfig()
{
  std::map<std::string,bool> objectConfig;
  objectConfig.insert(conf("name", false));
  objectConfig.insert(conf("description", false));
  objectConfig.insert(conf("health", true));
  objectConfig.insert(conf("money", true));
  objectConfig.insert(conf("location", false));
  objectConfig.insert(conf("canBeKilled", false));
  objectConfig.insert(conf("respawnProbablity", true));
  
  return objectConfig;
}

void NPCParser::parseNPCs(const std::string &path)
{
  //NPCBuilder builder(engine);
  boost::filesystem::path fullPath(path);
  boost::filesystem::path npcs("/characters");
  fullPath += npcs;
  
  std::map<std::string, bool> npcConfig = setObjectConfig();
  std::vector<boost::filesystem::path> files = getAllFilesWithExt(fullPath.native(), ".lua");
  auto results = parseFiles(files, npcConfig);
  //builder.buildObjects(results);
}