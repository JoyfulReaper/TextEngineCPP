/*
 TextEngine: mapsite.hpp
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
 * @file mapsite.hpp
 * @author Kyle Givler
 */

#ifndef _MAPSITE_H_
#define _MAPSITE_H_

#include <string>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

enum class Direction : size_t  { North = 0, South = 1, East = 2, West = 3, Up = 4, Down = 5, Invalid = 6 };

class TextEngine;

class MapSite
{
public:
  MapSite() {}
  
  MapSite(const MapSite &obj);
  
  virtual ~MapSite() {}
  
  /**
   * Enter the mapsite
   * @param from The direction the Character is entering from
   */
  virtual void enter(Direction from, TextEngine &engine) = 0;
  
  /**
   * Set the name of this MapSite 
   */
  virtual void setName(std::string name) { this->name = name; }
  
  /**
   * @return The name of this MapSite
   */
  virtual std::string getName() const { return this->name; }
  
  /**
   * Get the name of the Direction as a String from the Direction enum
   * @param dir The direction to get the name of
   */
  static std::string getDirectionName(Direction dir);
  
  /**
   * Get the Direction enum value from the given char
   * @param letter The char to get the direction for
   */
  static Direction getDirectionFromChar(char letter);
  
protected:
  std::string name;
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & name;
  }
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(MapSite)

#endif