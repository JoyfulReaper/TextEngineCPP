/*
    GreedyWrap: greedyWrap.hpp
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
 * @file GreedyWrap.hpp
 * @author Kyle Givler
 * 
 * Greedy word wrapping class
 */

#ifndef _GREEDY_WRAP_H
#define _GREEDY_WRAP_H

#include <string>
#include <sstream>
#include <iostream>

class GreedyWrap
{
public:
  
  /**
   * @param lineWidth The width to perform word wrap at
   */
  GreedyWrap(size_t lineWidth = 80) : lineWidth(lineWidth) {}
  
  /**
   * Set the line width
   * @param width The width to perform word wrap at
   */
  void setLineWidth(size_t width) { this->lineWidth = width; }
  
  /**
   * @return The width to perform word wrap at
   */
  size_t getLineWidth() const { return lineWidth; }
  
  /**
   * @param ss stringstrem to word wrap
   * @return A word wrapped string
   */
  std::string lineWrap(std::stringstream &ss);
  
  /**
   * @param string The string to word wrap
   * @return A word wrapped string
   */
  std::string lineWrap(std::string string);
  
private:
  size_t lineWidth;
  size_t spaceLeft;
  bool getWord(std::stringstream &ss, std::string &outWord);
};

#endif