bin_PROGRAMS =  textEngineGTK
textEngineGTK_SOURCES = main_gtk.cpp mainWindow.cxx
textEngineGTK_LDADD = $(LUA_LIB) $(BOOST_SERIALIZATION_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_SYSTEM_LIB) $(gtkmm_LIBS) ../libtextengine.a
textEngineGTK_LDFLAGS = $(BOOST_LDFLAGS)
textEngineGTK_CPPFLAGS = $(LUA_INCLUDE) $(BOOST_CPPFLAGS) $(gtkmm_CFLAGS) -Wall
