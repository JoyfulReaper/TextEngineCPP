/*
 TextEngine: roof.hpp
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
 * @file roof.hpp
 * @author Kyle Givler
 */

#ifndef _ROOF_H_
#define _ROOF_H_

#include "mapsite.hpp"

class Roof : public MapSite
{
public:
  Roof() { setName("roof"); }
  
  Roof(const Roof &obj);
  
  virtual ~Roof() {}
  
  virtual void enter(Direction from, TextEngine &engine);
  
private:
  friend boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<MapSite>(*this);
  }
};
#endif