/*
 TextEngine: playerParser.cxx
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
 * @file playerParser.cxx
 * @author Kyle Givler
 */

#include "playerParser.hpp"

typedef std::pair<std::string, bool> conf;

std::map<std::string,bool> PlayerParser::setObjectConfig()
{
  std::map<std::string,bool> objectConfig;
  objectConfig.insert(conf("name", false));
  objectConfig.insert(conf("description", false));
  objectConfig.insert(conf("health", true));
  objectConfig.insert(conf("money", true));
  objectConfig.insert(conf("location", false));
  objectConfig.insert(conf("invCapacity", true));
  
  return objectConfig;
}

void PlayerParser::parsePlayer(const std::string &path)
{
  boost::filesystem::path fullPath(path);
  boost::filesystem::path player("/player.lua");
  fullPath += player;
  
  std::map<std::string,bool> playerConfig = setObjectConfig();
  std::vector<boost::filesystem::path> file = getFile(fullPath.native());
  auto results = parseFiles(file, playerConfig);
}