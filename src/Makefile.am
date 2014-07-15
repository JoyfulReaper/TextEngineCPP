bin_PROGRAMS = textEngine
#textEngine_SOURCES = textEngine.cxx playerBuilder.cxx NPC.cxx containerItem.cxx luaAPI.cxx NPCParser.cxx NPCBuilder.cxx room.cxx exit.cxx wall.cxx roof.cxx character.cxx floor.cxx inventory.cxx greedyWrap.cxx mapBuilder.cxx item.cxx map.cxx parser.cxx itemParser.cxx itemBuilder.cxx commandParser.cxx roomParser.cxx playerParser.cxx main.cpp
textEngine_SOURCES = textEngine.cxx main.cpp greedyWrap.cxx
textEngine_LDADD = $(LUA_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB)
textEngine_LDFLAGS = $(BOOST_LDFLAGS)
textEngine_CPPFLAGS = $(LUA_INCLUDE) $(BOOST_CPPFLAGS) -Wall -Wextra
