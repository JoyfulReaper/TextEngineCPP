/*
 * TextEngine: NPC.cxx
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
 * @brief This class represents a non-playable Character.
 * @file NPC.cxx
 * @author Kyle Givler
 */

#include <fstream>
#include <functional>
#include "npc.hpp"
#include "thirdParty/luawrapper/LuaContext.hpp"
#include "textEngine.hpp"
#include "inventory.hpp"

NonPlayableCharacter::NonPlayableCharacter() {}

NonPlayableCharacter::NonPlayableCharacter(const NonPlayableCharacter &obj) : Character(obj)
{
  this->canBeKilled = obj.canBeKilled;
  this->respawnChance = obj.respawnChance;
}

bool NonPlayableCharacter::setRespawnChance(size_t chance)
{
  if (chance > 100 || chance < 0)
    return false;
  else
    respawnChance = chance;
  return true;
}

void NonPlayableCharacter::setHealth(double amount)
{
  if(!canBeKilled)
    return;
  
  double orgHealth = getHealth();
  if(amount > 100)
    amount = 100;
  
  this->health = amount;
  
  if(getHealth() < orgHealth && isAlive())
    wasAttacked();
}

void NonPlayableCharacter::processSpeech(std::string speech)
{
//   LuaContext *lua = engine->getLuaContext();
//   try {
//     std::ifstream npcFile(filename);
//     lua->executeCode(npcFile);
//     const auto onSay = lua->readVariable<std::function<void (std::string)>>("onSay");
//     onSay(speech);
//     npcFile.close();
//     
//   } catch (const LuaContext::WrongTypeException &wte) {
//     engine->addMessage("Your speech is greeted by a blank stare...\n");
//   } catch (const LuaContext::SyntaxErrorException &see) {
//     std::cerr << see.what();
//   } catch (const LuaContext::ExecutionErrorException &eee) {
//     std::cerr << eee.what();
//   }
//   lua->writeVariable("onSay", nullptr);
}


void NonPlayableCharacter::wasAttacked()
{
//   LuaContext *lua = engine->getLuaContext();
//   try {
//     std::ifstream npcFile(filename);
//     lua->executeCode(npcFile);
//     lua->executeCode("onAttack()");
//     npcFile.close();
//   } catch (const LuaContext::WrongTypeException &wte) {
//     // no onAttack()
//   } catch (const LuaContext::SyntaxErrorException &see) {
//     std::cerr << see.what();
//   } catch (const LuaContext::ExecutionErrorException &eee) {
//     std::cerr << eee.what();
//   }
//   lua->writeVariable("onAttack", nullptr);
}