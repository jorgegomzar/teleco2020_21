// Author: Juan I. Asensio (ETSIT Telecomunicación -
// Universidad de Valladolid - juaase@tel.uva.es)
// 28/April/2014
// Parts based on code by M. Lacage published in
// E. Altman and T. Jiménez, "NS Simulation for Beginners", Morgan & Claypool, 2012.
//
// Simulation of a UDP traffic source with arbitrary interarrival time distribution



#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/network-module.h"
#include "ns3/packet-sink.h"
#include "ns3/tcp-socket-factory.h"


using namespace ns3;

namespace etsit {

/////////////////////////////////////////////////////////////////////
// SENDER CLASS (UDP Application with arbitrary traffic pattern)
/////////////////////////////////////////////////////////////////////
class Sender : public Application
{
	public:
		Sender();
		void SetCreationInterval (RandomVariable v);
		void SetPacketSize (RandomVariable v);
		void SetFixedPacketSize(int size);
		void SetStream(Ptr<OutputStreamWrapper> stream);
		void SetUdpSocket(Ptr<Socket>);
		void HandleRead (Ptr<Socket> socket);
		long GetPacketCounter();
		void Start (void);
		void Stop (void);
	private:
		void DoSend (void);
		RandomVariable m_creationInterval;
		//Callback <void ,Ptr <Packet> > m_receiver;
		EventId m_sending;
		RandomVariable m_packetSize;
		int m_fixedPacketSize;
		Ptr<Socket> m_socket;
		Ptr<OutputStreamWrapper> m_stream;
		unsigned long m_counter;


};

} //namespace etsit
