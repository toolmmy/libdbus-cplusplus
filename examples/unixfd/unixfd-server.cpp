#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "unixfd-server.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>

static const char* UNIX_CHANNEL_SERVER_NAME = "org.freedesktop.DBus.Examples.UnixChannelDemo";
static const char* UNIX_CHANNEL_SERVER_PATH = "/org/freedesktop/DBus/Examples/UnixChannel";

class UnixChannelServer:
		public ::org::freedesktop::DBus::UnixChannelDemo_adaptor,
		public DBus::IntrospectableAdaptor,
		public DBus::ObjectAdaptor
{
private:

	int _fd;

public:
	UnixChannelServer(DBus::Connection &connection) :
		DBus::ObjectAdaptor(connection, UNIX_CHANNEL_SERVER_PATH)
	{
		this->_fd = open("client_msg.txt", O_RDWR|O_CREAT, 0644);
	}

	~UnixChannelServer() {

		if(this->_fd != -1) {
			close(this->_fd);
		}
	}

	::DBus::UnixFd Aquire()
	{
		int fd = dup( this->_fd);
		printf("Aquire(): Returning fd [%d] from origin [%d]\n", fd, this->_fd);

		return DBus::UnixFd(fd, true);
	}

	void Release()
	{
		printf("Release()\n");
		if(this->_fd != -1) {
			close(this->_fd);
			this->_fd = -1;
		}


	}

	std::map<std::string, std::string> GetProperties()
	{
		std::map<std::string, std::string> props;
		props["key"] = "value";
		return props;
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
	conn.request_name(UNIX_CHANNEL_SERVER_NAME);

	UnixChannelServer server(conn);
	std::cout << "Starting UnixChannelServer" << std::endl;
	dispatcher.enter();
	std::cout << "Stopping UnixChannelServer" << std::endl;

	return 0;
}
