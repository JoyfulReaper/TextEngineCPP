# I know this is shitty, but I'm learning!
# Think the best solution is to use a convience lib with the TextEngine stuff

bin_PROGRAMS = textEngine

# noinst_LTLIBRARIES = libtextengine.la
# libtextengine_la_SOURCES = luaAPI.cxx map.cxx mapBuilder.cxx containerItem.cxx npc.cxx npcBuilder.cxx npcParser.cxx roomParser.cxx itemParser.cxx itemBuilder.cxx commandParser.cxx room.cxx exit.cxx roof.cxx floor.cxx wall.cxx mapsite.cxx item.cxx inventory.cxx player.cxx textEngine.cxx character.cxx greedyWrap.cxx parser.cxx playerParser.cxx playerBuilder.cxx

noinst_LIBRARIES = libtextengine.a
libtextengine_a_SOURCES = luaAPI.cxx map.cxx mapBuilder.cxx containerItem.cxx npc.cxx npcBuilder.cxx npcParser.cxx roomParser.cxx itemParser.cxx itemBuilder.cxx commandParser.cxx room.cxx exit.cxx roof.cxx floor.cxx wall.cxx mapsite.cxx item.cxx inventory.cxx player.cxx textEngine.cxx character.cxx greedyWrap.cxx parser.cxx playerParser.cxx playerBuilder.cxx

textEngine_SOURCES = main.cpp
textEngine_LDADD = $(LUA_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB) libtextengine.a
textEngine_LDFLAGS = $(BOOST_LDFLAGS)
textEngine_CPPFLAGS = $(LUA_INCLUDE) $(BOOST_CPPFLAGS) -Wall

# textEngineGTK_SOURCES = gtkGui.cpp
# textEngineGTK_LDADD = $(LUA_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB) $(gtkmm_LIBS) libtextengine.a
# textEngineGTK_LDFLAGS = $(BOOST_LDFLAGS)
# textEngineGTK_CPPFLAGS = $(LUA_INCLUDE) $(BOOST_CPPFLAGS) $(gtkmm_CFLAGS) -Wall