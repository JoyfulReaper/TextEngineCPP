/*
 TextEngine: main_gtk.cpp
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
 * @file main_gtk.cpp
 * @author Kyle Givler
 */

#include <iostream>
#include "mainWindow.hpp"

int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.kgivler.textengine");
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
 
  try
  {
    refBuilder->add_from_file("../gui.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
  
  MainWindow *pWindow = 0;
  refBuilder->get_widget_derived("window", pWindow);
  
  if(pWindow)
  {
    app->run(*pWindow);
  }
  
  delete pWindow;
  return 0;
}