/*
 TextEngine: NPCBuilder.hpp
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
 * @file NPCBuilder.hpp
 * @author Kyle Givler
 */

#ifndef _NPC_BUILDER_H_
#define _NPC_BUILDER_H_

#include "builder.hpp"
#include "map.hpp"

class NPCBuilder : public Builder
{
public:
  NPCBuilder(Map &map) : map(map) {}
  
  virtual ~NPCBuilder() {}
  
  virtual void buildObjects(std::vector<std::map<std::string, std::string>> &npcConfig);
  
private: 
  Map &map;
};

#endif