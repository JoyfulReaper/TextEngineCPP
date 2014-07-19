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

#include "npcParser.hpp"

typedef std::pair<std::string,bool> conf;

std::map<std::string,bool> NPCParser::setObjectConfig()
{
  // False = required, True = optional
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

std::vector<std::map<std::string,std::string>> NPCParser::parseNPCs(const std::string &path)
{
  boost::filesystem::path fullPath(path);
  boost::filesystem::path npcs("/characters");
  fullPath += npcs;
  
  std::map<std::string, bool> npcConfig = setObjectConfig();
  std::vector<boost::filesystem::path> files = getAllFilesWithExt(fullPath.native(), ".lua");
  return parseFiles(files, npcConfig);
}