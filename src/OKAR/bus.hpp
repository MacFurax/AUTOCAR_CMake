#ifndef OKAR_BUS
#define OKAR_BUS

#include "Poco/Net/Net.h"

#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/NetworkInterface.h"
//#include "Poco/Thread.h"
//#include "Poco/Event.h"

#include <iostream>
#include <string>
#include <thread>
#include <memory>

using namespace std;

namespace OKAR {

  class Node;
  class Bus;

  class Node {
  public:
    Node() : 
      mNameId{"/default"},
      mBusSet{false}
    {}

    Node(string nameId) : mNameId{ nameId } {}

    void setBus(Bus& bus) 
    { 
      mBus = bus;
      mBusSet = true;
    }

  private:
    string mNameId;
    Bus mBus;
    bool mBusSet;

  };

  class Bus {
  public:
    Bus():
      mGrpIp{ "235.0.0.254" },
      mGrpPort{9000},
      mNodeSet{false},
      mRun{false}
    {

    }

    Bus(string grpIp, int grpPort) : Bus()
    {
      mGrpIp = grpIp;
      mGrpPort = grpPort;
    }

    void addNode(Node& node) 
    { 
      mNode = node; 
      mNodeSet = true;
    }

  private:

    int start()
    {
      if (!mNodeSet) return -1;

      mRun = true;
      if (!mThread)
      {
        mThread = make_unique<thread>(&run);
      }
      return 1;
    }

    void stop()
    {
      mRun = false;
    }

    void run()
    {
      if (mRun)
      {

      }
    }

    Node mNode;
    bool mNodeSet;
    string mGrpIp;
    int mGrpPort;
    bool mRun;
    unique_ptr<thread> mThread;

   
      
  };


}

#endif // OKAR_BUS