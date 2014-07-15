bin_PROGRAMS = textEngine
textEngine_SOURCES = item.cxx inventory.cxx player.cxx textEngine.cxx character.cxx main.cpp greedyWrap.cxx parser.cxx playerParser.cxx playerBuilder.cxx
textEngine_LDADD = $(LUA_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB)
textEngine_LDFLAGS = $(BOOST_LDFLAGS)
textEngine_CPPFLAGS = $(LUA_INCLUDE) $(BOOST_CPPFLAGS) -Wall
