/*
 * TextEngine: roomParser.cxx
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
 * @file roomParser.cxx
 * @author Kyle Givler
 */

#include "roomParser.hpp"

typedef std::pair<std::string,bool> conf;

std::map<std::string,bool> RoomParser::setObjectConfig()
{
  std::map<std::string,bool> objectConfig;
  objectConfig.insert(conf("name", false));
  objectConfig.insert(conf("shortName", false));
  objectConfig.insert(conf("description", false));
  objectConfig.insert(conf("exits", false));
  objectConfig.insert(conf("lookDescription", true));
  objectConfig.insert(conf("startRoom", true));
  
  return objectConfig;
}

std::vector<std::map<std::string,std::string>> RoomParser::parseRooms(std::string basePath)
{
  boost::filesystem::path fullPath(basePath);
  boost::filesystem::path rooms("/rooms");
  fullPath += rooms;
  
  std::map<std::string,bool> objectConfig = setObjectConfig();
  std::string ext = ".lua";
  std::vector<boost::filesystem::path> files = getAllFilesWithExt(fullPath.native(), ext);
  return parseFiles(files, objectConfig);

}