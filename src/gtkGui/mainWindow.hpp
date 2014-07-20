/*
 TextEngine: mainWindow.hpp
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

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <gtkmm.h>
#include "../textEngine.hpp"

class MainWindow : public Gtk::Window 
{
public:
  MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~MainWindow();
  
protected:
  void do_command();
  
  TextEngine engine;
  Glib::RefPtr<Gtk::Builder> m_refGlade;
  Gtk::Button *pButton;
  Gtk::Entry *pEntry;
  Gtk::TextView *pTextView;
  Glib::RefPtr<Gtk::TextBuffer> pTextBuffer;
};

#endif