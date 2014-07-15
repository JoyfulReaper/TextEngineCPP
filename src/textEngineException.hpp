/*
 TextEngine: TextEngineException.hpp
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
 * @file TextEngineException.hpp
 * @author Kyle Givler
 * @brief Generic exception used to signal that something went wrong
 */

#ifndef _TEXT_ENGINE_EXCEPTION_H_
#define _TEXT_ENGINE_EXCEPTION_H_

#include <exception>
#include <iostream>
#include <string>

class TextEngineException : public std::exception
{
public:
  virtual ~TextEngineException() {}
  TextEngineException(std::string error) : msg(error)
  {
    msg.insert(0,"TextEngineException: ");
    msg.append("\n");
  }

  virtual const char *what() const throw()
  {
    return msg.c_str();
  }

private:
  std::string msg;
};

#endif