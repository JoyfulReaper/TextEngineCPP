/*
 TextEngine: mapBuilder.hpp
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
 * @file mapBuilder.hpp
 * @author Kyle Givler
 */

#ifndef _MAP_BUILDER_H_
#define _MAP_BUILDER_H_

#include "map.hpp"
#include "mapsite.hpp"
#include "builder.hpp"

class TextEngine;

class MapBuilder : public Builder
{
public:
  virtual ~MapBuilder() {}
  
  MapBuilder() {}
  
  /**
   * Build the room from the given configuration (see roomParser.cxx)
   * @param roomConfig The configuration to use to build the Room
   */
  virtual void buildObjects(std::vector<std::map<std::string,std::string>> &roomConfig);
  
  /**
   * Build an Exit. An exit must be added to both rooms for it to be bi-directional.
   * @param fromRoom The Room to add the Exit too
   * @param toRoom The Room that the Exit will lead too.
   * @param dir The direction the exit is in
   */
  virtual void buildExit(std::string fromRoom, std::string toRoom, Direction dir, bool locked, bool visible);
  
  /**
   * Get the completed Map
   * @return The completed Map
   */
  //virtual Map* getMap() { return map; }
  
private:
};

#endif