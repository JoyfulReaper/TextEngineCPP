/*
 * TextEngine: item.cxx
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
 * @file item.cxx
 * @author Kyle Givler
 */


#include <boost/algorithm/string/case_conv.hpp>
#include <fstream>
#include <functional>
#include "thirdParty/luawrapper/LuaContext.hpp"
#include "item.hpp"
#include "textEngineException.hpp"

Item::Item() {}

Item::Item(const Item &obj)
{
  this->obtainable = obj.obtainable;
  this->visible = obj.visible;
  this->name = obj.name;
  this->uppercaseName = obj.uppercaseName;
  this->description = obj.description;
  this->filename = obj.filename;
  this->quantity = obj.quantity;
}

void Item::setName(std::string name)
{ 
  this->name = name; 
  boost::to_upper(name);
  this->uppercaseName = name;
}

void Item::setFilename(std::string filename)
{
  this->filename = filename;
}

bool Item::setQuantity(size_t number)
{
  if(number < 0)
    return false;
  
  this->quantity = number;
  return true;
}

bool Item::removeQuantity(size_t number)
{
  if(quantity - number <= 0)
    return false;
  
  quantity -= number;
  return true;
}

void Item::useItem(std::string command)
{
//   LuaContext *lua = engine->getLuaContext();
//   assert(lua);
//   try {
//     std::ifstream itemFile(filename);
//     lua->executeCode(itemFile);
//     const auto onUse = lua->readVariable<std::function<void (std::string)>>("onUse");
//     onUse(command);
//     itemFile.close();
//   } catch (const LuaContext::WrongTypeException &wte) {
//     engine->addMessage("You can't use that...\n");
//   } catch (const LuaContext::SyntaxErrorException &see) {
//     std::cerr << see.what();
//   } catch (const LuaContext::ExecutionErrorException &eee) {
//     std::cerr << eee.what();
//   }
//   lua->writeVariable("onUse", nullptr);
}

void Item::useHelp()
{
//   LuaContext *lua = engine->getLuaContext();
//   try{
//     std::ifstream itemFile(filename);
//     lua->executeCode(itemFile);
//     lua->executeCode("onHelp()");
//     itemFile.close();
//   } catch (const LuaContext::WrongTypeException &wte) {
//     wte.what();
//   } catch (const LuaContext::SyntaxErrorException &see) {
//     see.what();
//   } catch (const LuaContext::ExecutionErrorException &eee) {
//     engine->addMessage("No help provided\n");
//   }
//   lua->writeVariable("onHelp", nullptr);
}

void Item::onTake()
{
//   LuaContext *lua = engine->getLuaContext();
//   try{
//     std::ifstream itemFile(filename);
//     lua->executeCode(itemFile);
//     lua->executeCode("onTake()");
//     itemFile.close();
//   } catch (const LuaContext::WrongTypeException &wte) {
//     wte.what();
//   } catch (const LuaContext::SyntaxErrorException &see) {
//     see.what();
//   } catch (const LuaContext::ExecutionErrorException &eee) {
//     if(!obtainable)
//       engine->addMessage("You try to take the " + name + ", but it doesn't budge.\n");
//   }
//   lua->writeVariable("onTake", nullptr);
}