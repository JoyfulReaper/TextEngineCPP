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

/**
 * @file mainWindow.cxx
 * @author Kyle Givler
 * 
 * I know the way things done here are inconsistent, this is the first
 * time I have done a GTK Gui. BTW, Glade is sweet.
 */

#include "mainWindow.hpp"

MainWindow::MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  engine(0),
  glade(refGlade),
  pButton(0),
  pEntry(0),
  pTextView(0),
  pTextBuffer(0),
  pAboutDialog(0),
  pFolderChooser(0)
{
  // Basics
  glade->get_widget("button", pButton);
  if(pButton)
    pButton->signal_clicked().connect( sigc::mem_fun(*this, &MainWindow::do_command) );
  
  glade->get_widget("entry", pEntry);
  if(pEntry)
    pEntry->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::do_command) );
  
  glade->get_widget("textview", pTextView);
  if(pTextView)
    pTextView->set_wrap_mode(Gtk::WRAP_WORD);
  
  glade->get_widget("aboutdialog", pAboutDialog);
  if(pAboutDialog)
    pAboutDialog->signal_response().connect( sigc::mem_fun(*this, &MainWindow::on_about_dialog_response) );
  
  // Menu Stuff
  Gtk::MenuItem *pQuitItem = 0;
  glade->get_widget("quitMenuItem", pQuitItem);
  if(pQuitItem)
    pQuitItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::quit) );
  
  Gtk::MenuItem *pAboutItem = 0;
  glade->get_widget("aboutMenuItem", pAboutItem);
  if(pAboutItem)
    pAboutItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::show_about) );
  
  Gtk::MenuItem *pOpenItem = 0;
  glade->get_widget("openMenuItem", pOpenItem);
  if(pOpenItem)
    pOpenItem->signal_activate().connect( sigc::mem_fun(*this, &MainWindow::show_open) );
  
  //File chooser
  glade->get_widget("folderchooserdialog", pFolderChooser);
  if(pFolderChooser)
  {
    pFolderChooser->add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    pFolderChooser->add_button("Select", Gtk::RESPONSE_OK);
  }
  
  // Lets get started!
  pTextBuffer = pTextView->get_buffer();
  pTextBuffer->insert(pTextBuffer->end(), "Open the folder containing your game to begin!\n");
  //pTextBuffer->insert(pTextBuffer->end(), engine.getAllMessages());
}

MainWindow::~MainWindow() 
{
  if(engine)
    delete engine;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::do_command()
{
  if(!engine)
  {
    pTextBuffer->insert(pTextBuffer->end(), "Open the folder containing your game to begin!\n");
    pEntry->set_text("");
    return;
  }
  
  std::string command;
  command = pEntry->get_text();
  pEntry->set_text("");
  
  engine->processCommand(command);
  if(engine->isGameOver())
    this->hide();
  
  pTextBuffer->insert(pTextBuffer->end(), engine->getAllMessages());
  
  auto pos = pTextBuffer->create_mark(pTextBuffer->end());
  pTextView->scroll_to(pos, 0.0);
  return;
}

void MainWindow::quit()
{
  this->hide();
  return;
}

void MainWindow::show_about()
{
  pAboutDialog->show();
  pAboutDialog->present();
  return;
}

void MainWindow::on_about_dialog_response(int response_id)
{
  if( (response_id == Gtk::RESPONSE_CLOSE) || (response_id == Gtk::RESPONSE_CANCEL) )
  {
    pAboutDialog->hide();
  }
  return;
}

void MainWindow::show_open()
{
  pFolderChooser->set_transient_for(*this);
  int result = pFolderChooser->run();
  
  switch(result)
  {
    case(Gtk::RESPONSE_CANCEL):
    {
      pFolderChooser->hide();
      break;
    }
    case(Gtk::RESPONSE_OK):
    {
      if(engine)
	delete engine;
      
      pFolderChooser->hide();
      engine = new TextEngine(pFolderChooser->get_filename());
      pTextBuffer->insert(pTextBuffer->end(), engine->getAllMessages());
      break;
    }
  }
  return;
}