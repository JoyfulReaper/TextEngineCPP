#include <iostream>
#include "mainWindow.hpp"

int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.kgivler.textengine");
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
 
  try
  {
    refBuilder->add_from_file("gui.glade");
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