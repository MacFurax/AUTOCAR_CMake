#include <iostream>

#include "mcastSend.hpp"

#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/IPAddressImpl.h"
#include "Poco/Timespan.h"
#include "Poco/Stopwatch.h"


using Poco::Net::Socket;
using Poco::Net::MulticastSocket;
using Poco::Net::SocketAddress;
using Poco::Net::IPAddress;
using Poco::Timespan;
using Poco::Stopwatch;
using Poco::TimeoutException;
using Poco::InvalidArgumentException;
using Poco::IOException;

MulticastSocketTest::MulticastSocketTest()
{
}


MulticastSocketTest::~MulticastSocketTest()
{
}


void MulticastSocketTest::testMulticast()
{
	//MulticastEchoServer echoServer;
    SocketAddress group("239.255.1.2", 12345);
	//MulticastSocket ms( SocketAddress::IPv4 );
    MulticastSocket ms();
	
    int n = ms.sendTo("hello", 5, group);

	char buffer[256];
	n = ms.receiveBytes(buffer, sizeof(buffer));

	ms.close();
}


int main()
{
    MulticastSocketTest mct;
    mct.testMulticast();

    return 0;
}