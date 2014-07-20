/**
 * @author Kyle Givler
 * This is my "I have never done GUI programming" GUI,
 * with a little help from Glade
 */

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

//#include "textEngine.hpp"

Gtk::Window* pWindow = 0;

static void do_command()
{
}


int main(int argc, char **argv)
{
  //TextEngine engine("sampleGame");
  
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.kgivler.TextEngine");
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  
  try{
    refBuilder->add_from_file("gui.glade");
  } catch (const Glib::FileError &ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  } catch (const Glib::MarkupError &ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  } catch (const Gtk::BuilderError &ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
  
  refBuilder->get_widget("window", pWindow);
  if(pWindow)
  {
    Gtk::Button* pButton = 0;
    refBuilder->get_widget("button", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(do_command) );
    }
    
    Gtk::Entry* pEntry = 0;
    refBuilder->get_widget("entry", pEntry);
    if(pEntry)
    {
      pEntry->signal_activate().connect( sigc::ptr_fun(do_command) );
    }
    
    Gtk::TextView* pTextView = 0;
    refBuilder->get_widget("textview", pTextView);
    if(pTextView)
    {
    }
    
    
    app->run(*pWindow);
  }
  
  delete pWindow;
  return 0;
}
