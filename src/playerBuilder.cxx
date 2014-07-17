/*
 TextEngine: playerBuilder.cxx
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
 * @file playerBuilder.cxx
 * @author Kyle Givler
 */

#include "playerBuilder.hpp"
#include "player.hpp"
#include "textEngineException.hpp"

PlayerBuilder::PlayerBuilder(Player &player) : player(player) {}

void PlayerBuilder::buildObjects(std::vector<std::map<std::string,std::string>> &playerConfig)
{
  auto config = playerConfig.front();
  size_t health;
  double money;
  
  try{
    if(config["health"] == "")
      health = 100;
    else
      health = std::stod(config["health"]);
    
    if(config["money"] == "")
      money = 0;
    else
      money = std::stod(config["money"]);
    
     if(config["invCapacity"] != "")
       player.getInventory().setCapacity(std::stod(config["invCapacity"]));
    
  } catch (const std::invalid_argument &ia) {
    throw(TextEngineException("Configuration is invalid: " + config["filename"]));
  }
  
  player.setHealth(health);
  player.setMoney(money);
  player.setLocation(config["location"]);
  player.setName(config["name"]);
  player.setDescription(config["description"]);
  player.setFilename(config["filename"]);
}