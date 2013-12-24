EXTRA_DIST = unixfd-introspect.xml

AM_CPPFLAGS = -I$(top_srcdir)/include

noinst_PROGRAMS = unixfd-server

unixfd_server_SOURCES = unixfd-server.cpp
unixfd_server_LDADD = $(top_builddir)/src/libdbus-c++-1.la

$(top_builddir)/tools/dbusxx-xml2cpp $^ --adaptor=$@

noinst_PROGRAMS += unixfd-client

unixfd_client_SOURCES = unixfd-client.cpp 
unixfd_client_LDADD = $(top_builddir)/src/libdbus-c++-1.la

$(top_builddir)/tools/dbusxx-xml2cpp $^ --proxy=$@
	
CLEANFILES = $(BUILT_SOURCES)