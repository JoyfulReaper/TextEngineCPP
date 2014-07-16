/*
 * TextEngine: roomParser.hpp
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
 * @file roomParser.hpp
 * @author Kyle Givler
 */

#ifndef _ROOM_PARSER_H_
#define _ROOM_PARSER_H_

#include <string>
#include <map>
#include "parser.hpp"

class RoomParser : public Parser
{
public:
  RoomParser() {}
  virtual ~RoomParser() {}
  
  /**
   * Parse all the rooms in basePath/rooms
   * @param basePath The path to look for the rooms folder in
   */
  virtual std::vector<std::map<std::string,std::string>> parseRooms(std::string basePath);
  
  virtual std::map<std::string,bool> setObjectConfig();
protected:

};
#endif