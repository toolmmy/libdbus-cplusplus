
/*
 *	This file was automatically generated by dbusxx-xml2cpp; DO NOT EDIT!
 */

#ifndef __dbusxx__unixfd_client_h__PROXY_MARSHAL_H
#define __dbusxx__unixfd_client_h__PROXY_MARSHAL_H

#include <dbus-c++/dbus.h>
#include <cassert>

namespace org {
namespace freedesktop {
namespace DBus {

class UnixChannelDemo_proxy
: public ::DBus::InterfaceProxy
{
public:

    UnixChannelDemo_proxy()
    : ::DBus::InterfaceProxy("org.freedesktop.DBus.UnixChannelDemo")
    {
    }

public:

    /* properties exported by this interface */
public:

    /* methods exported by this interface,
     * this functions will invoke the corresponding methods on the remote objects
     */
    ::DBus::UnixFd Aquire()
    {
        ::DBus::CallMessage call;
        call.member("Aquire");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        ::DBus::UnixFd argout;
        ri >> argout;
        return argout;
    }

    void Release()
    {
        ::DBus::CallMessage call;
        call.member("Release");
        ::DBus::Message ret = invoke_method (call);
    }

    std::map< std::string, std::string > GetProperties()
    {
        ::DBus::CallMessage call;
        call.member("GetProperties");
        ::DBus::Message ret = invoke_method (call);
        ::DBus::MessageIter ri = ret.reader();

        std::map< std::string, std::string > argout;
        ri >> argout;
        return argout;
    }


public:

    /* signal handlers for this interface
     */

private:

    /* unmarshalers (to unpack the DBus message before calling the actual signal handler)
     */
};

} } } 
#endif //__dbusxx__unixfd_client_h__PROXY_MARSHAL_H
