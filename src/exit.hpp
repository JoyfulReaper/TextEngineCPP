/*
 TextEngine: exit.hpp
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
 * @file exit.hpp
 * @author Kyle Givler
 */

#ifndef _EXIT_H_
#define _EXIT_H_

#include "mapsite.hpp"
#include "textEngineException.hpp"

class Exit : public MapSite
{
public:
  Exit(std::string exitToRoom);
  
  Exit(const Exit &obj);
  
  virtual ~Exit() {}
  
  virtual void enter(Direction from, TextEngine &engine);
  
  /**
   * Set this exit as locked
   */
  inline void lockExit()
  {
    isLocked = true;
  }
  
  /**
   * Set this Exit as unlocked
   */
  inline void unlockExit()
  {
    isLocked = false;
  }
  
  inline bool isVisible() { return this->visible; }
  
  inline void setVisible(bool visible) { this->visible = visible; }
  
  /**
   * @return true if locked, false is unlocked
   */
  inline bool isExitLocked() const { return isLocked; }
  
  /**
   * Set the name of this exit, default is 'door'
   * @param name The name of this exit
   */
  inline void setName(std::string name) { this->name = name; }
  
  /**
   * @return the name of this exit
   */
  inline std::string getName() const { return name; }
  
  /**
   * Set the Room that this Exit goes to
   * @param toRoom The room this exit leads to
   */
  inline void setToRoom(std::string toRoom) { exitToRoom = toRoom; }
  
  /**
   * @return The Room this Exit leads to
   */
  inline std::string getToRoom() const { return exitToRoom; }
  
protected:
  std::string exitToRoom = "";
  bool isLocked = false;
  bool visible = true;
  
  friend boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<MapSite>(*this);
    ar & isLocked;
    ar & visible;
  }
};
#endif