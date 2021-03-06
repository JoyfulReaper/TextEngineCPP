/*
 TextEngine: NPCParser.hpp
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
 * @file NPCParser.hpp
 * @author Kyle Givler
 */

#ifndef _NPC_PARSER_H_
#define _NPC_PARSER_H_

#include "parser.hpp"
#include <map>

class NPCParser : public Parser
{
public:
  NPCParser() {}
  
  virtual ~NPCParser() {}
  
  virtual std::vector<std::map<std::string,std::string>> parseNPCs(const std::string &path);
  
  virtual std::map<std::string, bool> setObjectConfig();
  
private:

};

#endif