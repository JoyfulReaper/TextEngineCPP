/*
 TextEngine: wall.hpp
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
 * @file wall.hpp
 * @author Kyle Givler
 */

#ifndef _WALL_H_
#define _WALL_H_

#include "mapsite.hpp"

class Wall : public MapSite
{
public:
  // Main ctor
  Wall () { setName("wall"); }
  
  // Copy ctor
  Wall (const Wall &obj);
  
  virtual ~Wall() {}
  
  /**
   * Enter the room
   * @param from Direction to enter from
   * @param engine TextEngine to use
   */
  virtual void enter (Direction from, TextEngine &engine);
  
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
      ar & boost::serialization::base_object<MapSite>(*this);
    }
};

#endif