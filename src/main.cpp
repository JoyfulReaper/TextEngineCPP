/*
 * TextEngine: main.cpp
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
 * @file main.cpp
 * @author Kyle Givler
 * 
 * Console implementation of a game based on the TextEngine game engine. 
 * I know this file is really ugly :(
 * 
 * Console looks like shit under windows, plans for a gui wrapper eventually.
 * 
 * Under *nix this is pretty sweet, uses GNU Readline and everything :)
 * 
 */

#include <iostream>
#include "config.h"
#include "textEngine.hpp"
#include "greedyWrap.hpp"

// Check for Linux/Unix
#ifdef __unix__
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// Check for windows
#ifdef _WIN32
#include <windows.h>
#endif

// Check for readline
#ifdef HAVE_LIBREADLINE

#include <boost/algorithm/string/case_conv.hpp>
// #include <boost/filesystem.hpp>
// #include <cstdio>
// #include <cstdlib>
#include <unordered_set>
// #include <fstream>
// #include "item.hpp"
// #include "room.hpp"
// #include "NPC.hpp"
// #include "player.hpp"
// #include "map.hpp"

#  if defined(HAVE_READLINE_READLINE_H)
#    include <readline/readline.h>
#  elif defined(HAVE_READLINE_H)
#    include <readline.h>
#  else /* !defined(HAVE_READLINE_H) */
extern char *readline ();
#  endif /* !defined(HAVE_READLINE_H) */
char *cmdline = NULL;
#else /* !defined(HAVE_READLINE_READLINE_H) */
/* no readline */
#endif /* HAVE_LIBREADLINE */

// Check for readline history
#ifdef HAVE_READLINE_HISTORY
#  if defined(HAVE_READLINE_HISTORY_H)
#    include <readline/history.h>
#  elif defined(HAVE_HISTORY_H)
#    include <history.h>
#  else /* !defined(HAVE_HISTORY_H) */
extern void add_history ();
extern int write_history ();
extern int read_history ();
#  endif /* defined(HAVE_READLINE_HISTORY_H) */
/* no history */
#endif /* HAVE_READLINE_HISTORY */

using namespace std;

#ifdef HAVE_LIBREADLINE
// Functions and variables only used if Getline is present
char* rl_gets (); // Readline gets()
void initialize_readline (); // Setup readline
char* dupstr (const char *s); // Copies a c string
char* completion_generator(const char* text, int state); // tab completion
void addToKnown(TextEngine &engine); // Add things we have seen to tab completion

static char *line_read = (char *)NULL;
static std::unordered_set<std::string> completion = 
{ "north", "south", "east", "west", "down", "up", "quit", "exit", "look", "observe",
  "go", "move", "walk", "run", "help", "commands", "self", "health", "money", "status",
  "get", "take", "steal", "loot", "obtain", "inv", "inventory", "drop", "throw", "say",
  "talk", "yell", "scream", "whisper", "use", "push", "pull", "activate", "put"
};
#endif

void showLicense(); // Show license
size_t getWidth(); // Attempt to get console width, defaults to 80

///////////////////////////////////////////////////////////////////////////////
// main()

int main(void)
{
  #ifdef HAVE_LIBREADLINE
  initialize_readline ();
  #endif
  
  GreedyWrap wrap;
  showLicense();
  
  std::string game;
  int choice = 1;
  while (choice < 1 || choice > 2)
  {
    std::cout << "Games:\n";
    std::cout << "1) sampleGame\n";
    std::cout << "2) derekGame\n";
    std::cout << "Choose game: ";
    //std::cin >> choice;
  }
  
  switch(choice)
  {
    case 1:
      game = "sampleGame";
      break;
    case 2:
      game = "derekGame";
      break;
    default:
    {
      std::cerr << "Error";
      exit(1);
    }
  }
  
  TextEngine engine(game);
  
  // Main game loop, wheeeeeeee!!
  while(!engine.isGameOver())
  {
    wrap.setLineWidth(getWidth());
    std::cout << wrap.lineWrap(engine.getAllMessages());
    
    std::string command = "";
    do {
      std::cout << wrap.lineWrap(engine.getAllMessages());
      #ifdef HAVE_LIBREADLINE
      addToKnown(engine);
      command = rl_gets();
      #else
      std::cout << "\nEnter Command: ";
      std::getline(std::cin, command);
      #endif
    } while (!engine.processCommand(command));
  }
  
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

#ifdef HAVE_LIBREADLINE

void addToKnown(TextEngine &engine)
{
//   auto playerInvItems = engine->getPlayer()->getInventory()->getAllItems();
//   auto roomInvItems = engine->getMap()->getRoom(engine->getPlayer()->getLocation())->getInventory()->getAllItems();
//   auto roomNpcs = engine->getMap()->getRoom(engine->getPlayer()->getLocation())->getAllNpcs();
//   
//   for(auto it = playerInvItems.begin(); it != playerInvItems.end(); ++it)
//   {
//     const Item *item = *it;
//     if( !completion.count(item->getName()) )
//       completion.insert(item->getName());
//   }
//   
//   for(auto it = roomInvItems.begin(); it != roomInvItems.end(); ++it)
//   {
//     const Item *item = *it;
//     if (item->isVisible() && !completion.count(item->getName()) )
//       completion.insert(item->getName());
//   }
//   
//   for(auto it = roomNpcs.begin(); it != roomNpcs.end(); ++it)
//   {
//     const NonPlayableCharacter *npc = *it;
//     if(!completion.count(npc->getName()))
//       completion.insert(npc->getName());
//   }
}

void initialize_readline ()
{
  /* Allow conditional parsing of the ~/.inputrc file. */
  rl_readline_name = "textEngine";
  rl_completion_entry_function = completion_generator;
}

/* Read a string, and return a pointer to it.
 *  Returns NULL on EOF. */
char* rl_gets ()
{
  /* If the buffer has already been allocated,
   *    return the memory to the free pool. */
  if (line_read)
  {
    free (line_read);
    line_read = (char *)NULL;
  }
  
  /* Get a line from the user. */
  line_read = readline ("Enter Command: ");
  #ifdef HAVE_READLINE_HISTORY
  /* If the line has any text in it,
   *    save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);
  #endif
  
  return (line_read);
}

char* completion_generator(const char* text, int state)
{
  static int len;
  static std::unordered_set<std::string>::iterator it;
  
  if(!state)
  {
    it = completion.begin();
    len = strlen(text);
  }
  
  while(it != completion.end())
  {
    std::string name = *it;
    std::string ctext = text;
    boost::to_upper(ctext);
    boost::to_upper(name);
    ++it;
    if( strncmp(name.c_str(), ctext.c_str(), len) == 0 )
      return (dupstr(name.c_str()));
  }
  
  return ((char *)NULL);
}

char* dupstr (const char *s)
{
  char *r;
  r = (char *) malloc (strlen (s) + 1);
  if(r == NULL)
  {
    std::cerr << "Unable to allocate memory";
    exit(1);
  }
  strcpy (r, s);
  return (r);
}

#endif

//////////////////////////////////////////////////////////////////////////////////////////////

void showLicense()
{
  std::cout << "\nTextEngine Copyright (C) 2014 Kyle Givler \n";
  std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details see the GPLv3.\n";
  std::cout << "This is free software, and you are welcome to redistribute it\n";
  std::cout << "under certain conditions; see the GPLv3 for details.\n\n";
}

size_t getWidth()
{
  size_t cols = 80;
  
  #ifdef __linux__
  #ifdef TIOCGSIZE
  struct ttysize ts;
  ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
  cols = ts.ts_cols;
  //lines = ts.ts_lines;
  #elif defined(TIOCGWINSZ)
  struct winsize ts;
  ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
  cols = ts.ws_col;
  //lines = ts.ws_row;
  #endif /* TIOCGSIZE */
  #endif
  
  
  #ifdef _WIN32
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  //rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  #endif
  
  return cols;
}