#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "unixfd-client.h"
#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

using namespace std;

static const char* UNIX_CHANNEL_SERVER_NAME = "org.freedesktop.DBus.Examples.UnixChannelDemo";
static const char* UNIX_CHANNEL_SERVER_PATH = "/org/freedesktop/DBus/Examples/UnixChannel";

class UnixChannelClient:
		public org::freedesktop::DBus::UnixChannelDemo_proxy,
		public DBus::IntrospectableProxy,
		public DBus::ObjectProxy
{

public:
	UnixChannelClient(DBus::Connection &connection, const char *path, const char *name) :
			DBus::ObjectProxy(connection, path, name)
	{
	}

};

DBus::BusDispatcher dispatcher;

void niam(int sig)
{
  dispatcher.leave();
}

int main()
{
	signal(SIGTERM, niam);
	signal(SIGINT, niam);

	DBus::default_dispatcher = &dispatcher;
	DBus::Connection conn = DBus::Connection::SessionBus();

	UnixChannelClient client(conn, UNIX_CHANNEL_SERVER_PATH, UNIX_CHANNEL_SERVER_NAME);

	std::cout << "Client: Aquire file descriptor from server." << std::endl;
	DBus::UnixFd fd = client.Aquire();
	if(fd.isOpen()) {

		std::cout << "Client: Wrtiting some stuff" << std::endl;
		char msg[] = "Client: hi server!\n";
		write(fd.getFileDescriptor(), msg, sizeof(msg));
	}

	client.Release();
	std::cout << "Client: Bye." << std::endl;

	return 0;
}

