/*
 * TextEngine: parser.cxx
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
 * @file parser.cxx
 * @author Kyle Givler
 */

#include <algorithm>
#include <fstream>
#include <boost/algorithm/string/case_conv.hpp>
#include "thirdParty/luawrapper/LuaContext.hpp"
#include "textEngineException.hpp"
#include "parser.hpp"

using namespace boost;

static const std::string ALL_FILES = "ALL";

std::vector<filesystem::path> Parser::getAllFiles(const std::string &path)
{
  return getAllFilesWithExt(path, ALL_FILES);
}

std::vector<filesystem::path> Parser::getAllFilesWithExt(const std::string &path, const std::string &ext)
{
  filesystem::path fullPath(path);
  std::vector<filesystem::path> files; // all files in path
  
  // Get all files in path
  try {
    if(!(exists(fullPath) && is_directory(fullPath)))
      throw (TextEngineException("Can't find path '" + fullPath.string() + "'\n"));
  } catch(const filesystem::filesystem_error &ex) {
    throw (TextEngineException(ex.what()));
  }
  
  copy(filesystem::directory_iterator(fullPath), filesystem::directory_iterator(), std::back_inserter(files));
  sort(files.begin(), files.end());
  
  if(ext != ALL_FILES)
  {
    std::vector<filesystem::path> extFiles;
    for(auto it = files.begin(); it != files.end(); ++it)
    {
      filesystem::path file = *it;
      std::string name = file.string();
      std::string ext = file.extension().string();
      to_lower(ext);
      if (ext != ext || name[name.length() - 1] == '~') // ignore .ext~ files
	continue;
      
      extFiles.push_back(file);
    }
    return extFiles;
  }
  return files;
}

std::vector<filesystem::path> Parser::getFile(const std::string &path)
{
  filesystem::path fullPath(path);
  std::vector<filesystem::path> fileV;
  
  try {
    if(!(exists(fullPath) && is_regular_file(fullPath)))
      throw (TextEngineException("Can't find file '" + fullPath.string() + "'\n"));
  } catch(const filesystem::filesystem_error &ex) {
    throw (TextEngineException(ex.what()));
  }
  
  fileV.push_back(fullPath);
  return fileV;
}

std::vector<std::map<std::string,std::string>> Parser::parseFiles(std::vector<filesystem::path> files, std::map<std::string,bool> options)
{
  std::vector<std::map<std::string,std::string>> resultVec;
  for(auto it = files.begin(); it != files.end(); ++it)
  {
    std::map<std::string,std::string> objectConfig;
    filesystem::path file = *it;
    std::ifstream fileStream(file.native());
    LuaContext lua;
    try{
      lua.executeCode(fileStream);
      fileStream.close();
    } catch(const LuaContext::SyntaxErrorException &see) {
      std::string luaError = see.what();
      throw(TextEngineException("File: " + file.string() + ": " + luaError));
    }
    
    for (auto itt = options.begin(); itt != options.end(); ++itt)
    {
      if(itt->second)
      {
	try {
	  objectConfig[itt->first] = lua.readVariable<std::string>(itt->first);
	} catch (const LuaContext::WrongTypeException &ex) { 
	  objectConfig[itt->first] = "";
	}
      } else {
	try {
	  objectConfig[itt->first] = lua.readVariable<std::string>(itt->first);
	} catch (const LuaContext::WrongTypeException &ex) {
	  throw (TextEngineException("Parser: Required option not found: " + itt->first));
	}
      }
    }
    objectConfig["filename"] = file.native();
    
    resultVec.push_back(objectConfig);
  }
  return resultVec;
}