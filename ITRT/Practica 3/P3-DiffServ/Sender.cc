// Author: Juan I. Asensio (ETSIT Telecomunicación -
// Universidad de Valladolid - juaase@tel.uva.es)
// 28/April/2014
// Parts based on code by M. Lacage published in
// E. Altman and T. Jiménez, "NS Simulation for Beginners", Morgan & Claypool, 2012.
//
// Simulation of a UDP traffic source with arbitrary interarrival time distribution


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <string>
#include <sstream>
#include "Sender.h"



using namespace ns3;
NS_LOG_COMPONENT_DEFINE("Sender");


namespace etsit {

Sender::Sender()
: m_fixedPacketSize(0)
{}

void
Sender::DoSend (void)
{

	Ptr<Packet> p;
	if(m_fixedPacketSize==0){
		p = Create<Packet> (m_packetSize.GetValue());
	} else {
		p = Create<Packet> (m_fixedPacketSize);
	}
	if(m_stream != NULL) {
		*m_stream->GetStream() << Simulator::Now ().GetNanoSeconds() << "\t" << p->GetSize() << std::endl;  //In simulation Time Now() a packet of p-GetSize() bytes has been generated
	}
	m_socket->Send(p);
	m_counter++;
	double sendInterval = m_creationInterval.GetValue ();
	m_sending = Simulator :: Schedule (Seconds (sendInterval),
			&Sender::DoSend,this );
}

long
Sender::GetPacketCounter() {
	return m_counter;
}


void
Sender::SetUdpSocket(Ptr<Socket> socket) {

	m_socket = socket;
}


void
Sender::SetStream(Ptr<OutputStreamWrapper> stream) {

	m_stream = stream;
}

void
Sender::SetPacketSize (RandomVariable v)
{
	m_packetSize = v;
}

void
Sender::SetFixedPacketSize (int v)
{
	m_fixedPacketSize = v;
}

void
Sender::SetCreationInterval (RandomVariable v)
{
	m_creationInterval = v;
}


void
Sender::Start (void)
{
	m_counter=0;
	DoSend ();
}

void
Sender::Stop(void)
{
	m_sending.Cancel ();
}

void
Sender::HandleRead (Ptr<Socket> socket)
{
	//NS_LOG_FUNCTION (this << socket);
	Ptr<Packet> packet;
	Address from;
	while (packet = socket->RecvFrom (from))
	{
		if (InetSocketAddress::IsMatchingType (from))
		{
			InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
			NS_LOG_INFO ("Received " << packet->GetSize() << " bytes from " <<
					address.GetIpv4());
		}
	}
}

} //namespace etsit
