/*
 TextEngine: commandParser.hpp
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
 * @file commandParser.hpp
 * @author Kyle Givler
 */

#ifndef _COMMAND_PARSER_H_
#define _COMMAND_PARSER_H_

#include <vector>
#include <map>
#include <boost/filesystem.hpp>

// namespace boost {
//   namespace filesystem {
//     class path;
//   }
// }

class TextEngine;
typedef std::vector<std::string> vector;

class CommandParser
{
public:
  CommandParser() {}
  
  /**
   * @param command The command to process
   */
  bool doCommand(std::string command, TextEngine &engine);
  
  /**
   * @param command the command to register
   * @param script the lua file under /scripts to run
   * @return true on success, false on failure
   */
  bool registerCommand(std::string command, std::string script, TextEngine &engine);
  
  /**
   * @return the last command processed
   */
  std::string getLastCommand() const { return lastCommand; }
  
private:
  std::map<std::string, boost::filesystem::path> commands;
  std::string lastCommand = "";
  
  bool processSave(const vector &command, TextEngine &engine);
  
  bool processLoad(const vector &command, TextEngine &engine);
  
  bool processScript(vector &command, TextEngine &engine);
  
  bool processLook(const vector &command, TextEngine &engine);
  
  bool processGo(const vector &command, TextEngine &engine);
  
  bool processHelp(const vector &command, TextEngine &engine);
  
  bool processSelf(TextEngine &engine);
  
  bool processGet(vector &command, TextEngine &engine);
  
  bool processInv(vector &command, TextEngine &engine);
  
  bool processDrop(vector &command, TextEngine &engine);
  
  bool processSay(vector &command, TextEngine &engine);
  
  bool processUse(vector &command, TextEngine &engine);
  
  bool processPut(vector &command, TextEngine &engine);
  
  std::string getObjectName(const vector &command);
};

#endif