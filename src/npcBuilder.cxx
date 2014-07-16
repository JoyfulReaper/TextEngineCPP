/*
 * TextEngine: NPCBuilder.cxx
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
 * @file NPCBuilder.cxx
 * @author Kyle Givler
 */

#include <boost/algorithm/string.hpp>
#include "npcBuilder.hpp"
#include "textEngineException.hpp"
#include "npc.hpp"

using namespace boost;

void NPCBuilder::buildObjects(std::vector<std::map<std::string,std::string>> &npcConfig)
{
  for(auto it = npcConfig.begin(); it != npcConfig.end(); ++it)
  {
    auto config = *it;
    NonPlayableCharacter npc;
    
    size_t health;
    double money;
    size_t canBeKilled;
    size_t respawnChance;
    
    try{
      canBeKilled = std::stoi(config["canBeKilled"]);
      
      if(config["health"] == "")
	health = 100;
      else
	health = std::stod(config["health"]);
      
      if (config["money"] == "")
	money = 0;
      else 
	money = std::stod(config["money"]);
      
      if(config["respawnProbablity"] == "")
	respawnChance = std::stoi(config["respawnProbablity"]);
      else
	respawnChance = 0;
      
    } catch (const std::invalid_argument &ia) {
      throw(TextEngineException("NPC Configuration is invalid: " + config["filename"]));
    }
    
    npc.setFilename(config["filename"]);
    npc.setName(config["name"]);
    npc.setDescription(config["description"]);
    npc.setLocation(config["location"]);
    npc.setHealth(health);
    npc.setMoney(money);
    npc.setKillable(canBeKilled);
    if(!npc.setRespawnChance(respawnChance))
      throw(TextEngineException(config["filename"] + ": Invalid respawnChance: " + std::to_string(respawnChance)));
    
    //engine->registerNPC(config["name"], config["location"]);
    
    std::vector<std::string> locVec;
    split(locVec, config["location"], is_any_of(":"));
    if(locVec.size() == 0)
      throw(TextEngineException("Invalid location string: " + config["filename"]));
    
    for(size_t i = 0; i < locVec.size(); i++)
    {
//       std::string addRoom = locVec[i];
//       if(!engine->getMap()->roomExists(addRoom))
// 	throw(TextEngineException("Trying to add NPC to non-existant room: " + config["filename"]));
//       
//       engine->getMap()->getRoom(addRoom)->addNPC(npc);
      npc = NonPlayableCharacter(npc);
    }
    
  }
}