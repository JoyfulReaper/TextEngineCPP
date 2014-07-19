/*
 TextEngine: npc.hpp
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
 * @brief This class represents a non-playable Character.
 * @file npc.hpp
 * @author Kyle Givler
 */

#ifndef _NPC_H_
#define _NPC_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "character.hpp"

class TextEngine;

class NonPlayableCharacter : public Character
{
public:
  // Constuctor
  NonPlayableCharacter();
  
  // Copy Constuctor
  NonPlayableCharacter(const NonPlayableCharacter &obj);
  
  /**
   * @param killable Set weather or not this NPC can be killed 
   */
  inline void setKillable(bool killable)
  {
    this->canBeKilled = killable;
  }
  
  /**
   * @return true if this NPC can be killed, false otherwise
   */
  inline bool getKillable() const
  {
    return this->canBeKilled;
  }
  
  /**
   * @return the chance for this NPC to respawn if killed
   */
  inline size_t getRespawnChance() const
  {
    return this->respawnChance;
  }
  
  /**
   * @param chance The chance of the NPC to respawan when the room it was killed in is reentered (0-100%)
   */
  bool setRespawnChance(size_t chance);
  
  /**
   * @param ammount Amount of health to give the npc (0-100)
   */
  void setHealth(double amount, TextEngine &engine);
  
  /**
   * Set health without requiring a TextEngine object, but doesn't run onAttack()
   * @param amount Amount of health to set Npc health to (0-100)
   */
  void setHealthNoAttack(double amount);
  
  /**
   * The Player spoke to this NonPlayableCharacter
   */
  void processSpeech(std::string speech, TextEngine &engine);
  
private:  
  bool canBeKilled = true;
  size_t respawnChance = 0;
  
   /**
   * This NPC was attacked
   */
  void wasAttacked(TextEngine &engine);
  
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar & boost::serialization::base_object<Character>(*this);
    ar & canBeKilled;
    ar & respawnChance;
  }
  
};
#endif