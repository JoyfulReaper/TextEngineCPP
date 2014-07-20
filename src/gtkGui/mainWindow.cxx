/*
 TextEngine: mainWindow.cxx
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

#include "mainWindow.hpp"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  engine("sampleGame"),
  m_refGlade(refGlade),
  pButton(0),
  pEntry(0),
  pTextView(0),
  pTextBuffer(0)
{
  m_refGlade->get_widget("button", pButton);
  if(pButton)
  {
    pButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::do_command) );
  }
  
  m_refGlade->get_widget("entry", pEntry);
  if(pEntry)
  {
    pEntry->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::do_command) );
  }
  
  m_refGlade->get_widget("textview", pTextView);
  if(pTextView)
  {
    pTextView->set_wrap_mode(Gtk::WRAP_WORD);
  }
  
  pTextBuffer = pTextView->get_buffer();
  pTextBuffer->insert_at_cursor(engine.getAllMessages());
}

MainWindow::~MainWindow() {}

void MainWindow::do_command()
{
  std::string command;
  command = pEntry->get_text();
  pEntry->set_text("");
  
  engine.processCommand(command);
  
  pTextBuffer->insert_at_cursor(engine.getAllMessages());
  
}