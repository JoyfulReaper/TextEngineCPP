/*
 TextEngine: containerItem.cxx
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
 * @file containerItem.cxx
 * @author Kyle Givler
 * @brief An item that has an Inventory
 */

#include "containerItem.hpp"

ContainerItem::ContainerItem() {}

ContainerItem::ContainerItem(const ContainerItem &obj) : Item(obj), inventory(Inventory(obj.inventory))
{
  this->locked = obj.locked;
}