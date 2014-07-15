/*
 TextEngine: builder.hpp
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
 * @file builder.hpp
 * @author Kyle Givler
 */

#ifndef _BUILDER_H
#define _BUILDER_H

#include <string>
#include <map>
#include <vector>

class Builder
{
public:
  virtual ~Builder() {}
  
  /**
   * Build objects from the given configuration (see Parser class for more information).
   * 
   * ObjectConfig is an map of strings, the key is the value the parser searched the lua file for
   * and the value is the value found for the given key.
   * 
   * @param ObjectConfig The key, value map used as configuration for building the objects
   */
  virtual void buildObjects(std::vector<std::map<std::string,std::string>> &ObjectConfig) = 0;
};

#endif