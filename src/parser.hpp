/*
 TextEngine: parser.hpp
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
 * @file parser.hpp
 * @author Kyle Givler
 */

#ifndef _PARSER_H_
#define _PARSER_H_

#include <vector>
#include <map>
#include <boost/filesystem.hpp>

class Parser
{
public:
  virtual ~Parser() {}
  
  /**
   * Setup a map with the key being a global string in a Lua file, and the value
   * being a bool. If true the value is optional, if false the value is required.
   * @return the map to use for parsing the lua files
   */
  virtual std::map<std::string,bool> setObjectConfig() = 0;
  
  /**
   * @param path The path to get a vector of files from
   * @return A vector of all files in the given path
   */
  virtual std::vector<boost::filesystem::path> getAllFiles(const std::string &path);
  
  /**
   * @param path The path to get a vector of files from
   * @param ext The extension of the files you want in the vector. (".lua")
   * @return A vector of all files in the given path with the given extension
   */
  virtual std::vector<boost::filesystem::path> getAllFilesWithExt(const std::string &path, const std::string &ext);
  
  /**
   * Get the file at the given path.
   */
  virtual std::vector<boost::filesystem::path> getFile(const std::string &path);
  
  /**
   * @param files A vector of files to parse
   * @param options The map set by setObjectConfig()
   * @return an map with the key being the lua global and the value being the value of that global, as set by options paramater
   */
  virtual std::vector<std::map<std::string,std::string>> parseFiles(std::vector<boost::filesystem::path> files, std::map<std::string,bool> options);
};

#endif