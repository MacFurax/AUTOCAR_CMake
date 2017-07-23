#ifndef OKAR_NODE
#define OKAR_NODE

#include <iostream>
#include <string>

// Poco Network
#include "Poco/Net/Net.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetworkInterface.h"

//oscpack OSC packet manipulation
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"


using namespace std;
using namespace Poco::Net;

namespace OKAR
{

class Node 
{
public:

  Node() 
  {
    // add default constructor code
  }

  Node(string name) : 
    mName{ name }, 
    mGroup{ "239.255.1.2", 12345 },
    mIf{ findInterface() }, 
    mStop{ false }
  {
    // create socket to receive/send multicast packet
    mSocket.bind(SocketAddress(IPAddress(), mGroup.port()), true);
    // join multicast group
    mSocket.joinGroup(mGroup.host(), mIf);
  }

  ~Node() 
  {
    mSocket.leaveGroup(mGroup.host(), mIf);
    mSocket.close();
  }

  void run() {

    char buffer[1024];
        
    while (!mStop)
    {
      Poco::Timespan span(250000);
      if (mSocket.poll(span, Socket::SELECT_READ))
      {
        try
        {
          
          SocketAddress sender;
          int n = mSocket.receiveFrom(buffer, sizeof(buffer), sender);
          cout << " Receive " << n << " bytes from " << sender.toString() << " [" << buffer << "]\n";
          mSocket.sendTo(buffer, n, sender);
        }
        catch (Poco::Exception& exc)
        {
          cerr << "MulticastEchoServer: " << exc.displayText() << std::endl;
        }
      }
    }

  }

  NetworkInterface findInterface()
  {
    NetworkInterface::Map m = NetworkInterface::map();
    for (NetworkInterface::Map::const_iterator it = m.begin(); it != m.end(); ++it)
    {
      if (it->second.supportsIPv4() &&
        it->second.firstAddress(IPAddress::IPv4).isUnicast() &&
        !it->second.isLoopback() &&
        !it->second.isPointToPoint())
      {
        return it->second;
      }
    }
    return NetworkInterface();
  }


private:
  string mName;

  MulticastSocket  mSocket;
  SocketAddress    mGroup;
  NetworkInterface mIf;
  osc::OutboundPacketStream mOSCOutPacketStream;

  bool mStop;
};

}// namespace OKAR

#endif // OKAR_NODE