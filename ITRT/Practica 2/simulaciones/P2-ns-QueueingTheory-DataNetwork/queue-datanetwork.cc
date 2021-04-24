// Author: Juan I. Asensio (ETSIT Telecomunicaci�n -
// Universidad de Valladolid - juaase@tel.uva.es)
// 22/March/2015 - Last update 4/March/2021
// Parts based on code by M. Lacage published in
// E. Altman and T. Jim�nez, "NS Simulation for Beginners", Morgan & Claypool, 2012.
//
// Simulation of a simple UDP network. Comparison with queueing theory.


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <string>
#include <sstream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("QueueDataNetwork");

/////////////////////////////////////////////////////////////////////
// SENDER CLASS (UDP Application with arbitrary traffic pattern)
/////////////////////////////////////////////////////////////////////
class Sender
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



////////////////////////////////////////////////////////////////////
//Global Variables for calculating Average Buffer use
Ptr<DropTailQueue> senderqueue;
double lengthIntegrator=0;
double lastEvent=0;



////////////////////////////////////////////////////////////////////
//Queue Tracing callbacks
static void
senderDrop (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	//If this message is displayed, DNSE3 fails...
	//NS_LOG_UNCOND("sender QueueDrop: " << Simulator::Now ().GetNanoSeconds ());
	*stream->GetStream () << Simulator::Now ().GetNanoSeconds () << std::endl;
}

static void
senderEnqueue (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	//IMPORTANT: the Queue class invokes this callback BEFORE the size of the Queue is updated
	//see queue.cc (Enqueue method)
	*stream->GetStream () << Simulator::Now().GetNanoSeconds() << "\t\t" << senderqueue->GetNPackets() +1 << std:: endl;
	lengthIntegrator += (senderqueue->GetNPackets() )*(Simulator::Now().GetNanoSeconds() - lastEvent);
	lastEvent = Simulator::Now().GetNanoSeconds();
}

static void
senderDequeue (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	//IMPORTANT: the Queue class invokes this callback AFTER the size of the Queue is updated
	//see queue.cc (Enqueue method)
	*stream->GetStream () << Simulator::Now().GetNanoSeconds() << "\t\t" << senderqueue->GetNPackets() << std:: endl;
	lengthIntegrator += (senderqueue->GetNPackets() +1)*(Simulator::Now().GetNanoSeconds() - lastEvent);
	lastEvent = Simulator::Now().GetNanoSeconds();
}

//This variable will store a "snapshot" of the number
//of packets at a given time (e.g., almost at the end
//of the simulation
double finalQueueLength=0;

//This callback will be invoked by the simulator
//at a given time to register the number of packets
//in the buffer
void
SetFinalQueueLength(ns3::Ptr<ns3::DropTailQueue> senderqueue)
{
	finalQueueLength = senderqueue->GetNPackets();
}


////////////////////////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////////////////////////

int
main (int argc, char *argv[])
{


	bool tracing = false;
	bool averaging = false;
	bool fixedlength = false;
	unsigned int rep = 1;
	double lambda = 11.0; //service requests per second
	double tmax = 2000.0; //simulation time length (default value might not be suitable)
	double meanPacketSize = 1000.0; //(bytes)
	double bitRate = 100000; //bps
	uint32_t senderIPBufferSize = 300; // In segments
	std::string linkDelay = "300ns";


	CommandLine cmd;
	cmd.AddValue ("tracing", "Tracing. Default: 0", tracing);
	cmd.AddValue ("averaging", "Calculating average Q or not (not by default)", averaging);
	cmd.AddValue ("rep","Rep",rep);
	cmd.AddValue ("lambda","Lambda. Default: 11 pkts/sec.",lambda );
	cmd.AddValue ("meanPacketSize","MeanPacketSize (bytes). Default: 1000 bytes.",meanPacketSize);
	cmd.AddValue ("bitRate", "Link BitRate (bps). Default: 100000 bps", bitRate);
	cmd.AddValue ("tmax","Simulation time (seconds). Default: 10000 sec.",tmax );
	cmd.AddValue ("fixedlength","Using fixed or exponential packet lengths (1=fixed, 0=exponential). Default: exponential", fixedlength);
	cmd.AddValue ("senderIPBufferSize", "Number of IP packets the sender IP entity should be able to store in its buffer for forwarding. Default: 300 packets)", senderIPBufferSize);
	cmd.AddValue ("linkDelay", "Delay of the sender->r1 and r2->s2 p2p links. Default: 300ns.", linkDelay);

	cmd.Parse(argc,argv);



	//Setting up trace files...
	AsciiTraceHelper asciiTraceHelper;
	Ptr<OutputStreamWrapper> streamArrivals = NULL;
	streamArrivals = asciiTraceHelper.CreateFileStream ("P2-ns-QueueingTheory-arrivals.trace");



	SeedManager::SetRun(rep);


	//Setting up topology and communications architecture
	NodeContainer nodes;
	nodes.Create (2);

	PointToPointHelper pointToPoint;


	std::string bitRate_String;
	std::stringstream bitRate_Stream;
	bitRate_Stream << bitRate/1000 << "Kbps\n";
	pointToPoint.SetDeviceAttribute ("DataRate", StringValue(bitRate_Stream.str()));



	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

	NetDeviceContainer devices;
	devices = pointToPoint.Install (nodes);



	// Setting up queue at sender's device
	senderqueue = CreateObject<DropTailQueue>();
	senderqueue->SetAttribute("MaxPackets",UintegerValue(senderIPBufferSize));
	Ptr<PointToPointNetDevice> devsenderp2p = DynamicCast<PointToPointNetDevice> (devices.Get(0));
	devsenderp2p->SetQueue(senderqueue);

	//Setting callback for queue tracing
	Ptr<OutputStreamWrapper> senderstreamDrop = asciiTraceHelper.CreateFileStream ("sender.queuedropped.trace");
	senderqueue->TraceConnectWithoutContext ("Drop", MakeBoundCallback(&senderDrop, senderstreamDrop));
	Ptr<OutputStreamWrapper> senderstreamEnqueue = asciiTraceHelper.CreateFileStream ("sender.enqueue.trace");
	senderqueue->TraceConnectWithoutContext ("Enqueue", MakeBoundCallback(&senderEnqueue, senderstreamEnqueue));
	Ptr<OutputStreamWrapper> senderstreamDequeue = asciiTraceHelper.CreateFileStream ("sender.dequeue.trace");
	senderqueue->TraceConnectWithoutContext ("Dequeue", MakeBoundCallback(&senderDequeue, senderstreamDequeue));


	//Addressing, setting up the UDP server
	InternetStackHelper stack;
	stack.Install (nodes);

	Ipv4AddressHelper address;
	address.SetBase ("10.1.1.0", "255.255.255.0");

	Ipv4InterfaceContainer interfaces = address.Assign (devices);

	PacketSinkHelper receiverHelper ("ns3::UdpSocketFactory", InetSocketAddress(interfaces.GetAddress(1), 9));
	ApplicationContainer serverApps = receiverHelper.Install(nodes.Get(1));

	//Traffic generation
	Sender *sender = new Sender ();
	sender->SetCreationInterval(ExponentialVariable (1.0/ lambda ));
	if(!fixedlength){
		sender->SetPacketSize (ExponentialVariable (meanPacketSize));
	}else{
		sender->SetFixedPacketSize(meanPacketSize);
	}
	sender->SetStream(streamArrivals);


	//Socket creation (obtained from udp-echo-client.cc
	TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
	Ptr<Socket> udp_socket;
	udp_socket = Socket::CreateSocket(nodes.Get(0),tid);
	udp_socket->Bind();
	udp_socket->Connect(InetSocketAddress(interfaces.GetAddress(1), 9));
	udp_socket->SetRecvCallback(MakeCallback(&Sender::HandleRead, sender));
	sender->SetUdpSocket(udp_socket);


	//Simulation Management
	Simulator::Schedule(Seconds (0.0001), &Sender::Start, sender);
	//This event will invoke the callback to register
	//the number of packets in the buffer (e.g., at
	//the 98% of the simulation time)
	Simulator::Schedule(Seconds (0.98*tmax), &SetFinalQueueLength, senderqueue);
	Simulator::Schedule(Seconds (tmax), &Sender::Stop, sender);
	serverApps.Start (Seconds (0.0001));
	serverApps.Stop (Seconds (tmax));
	Simulator::Run();
	Simulator::Destroy();

	//Tracing
	if(tracing) {
		std::cout << sender->GetPacketCounter() << " UDP Datagrams Sent\n";
		std::cout << senderqueue->GetTotalReceivedPackets() << " Packets received by the sender queue\n";
		std::cout << senderqueue->GetTotalDroppedPackets() << " Packets dropped from the sender queue\n";
		std::cout << finalQueueLength << " Packets in the buffer at the end of the simulation\n";
		std::cout << "Average Buffer Utilization: " << (lengthIntegrator/1000000000/tmax) << " Packets\n";
	} else {
		if(averaging) {
			std::cout<< (lengthIntegrator/1000000000/tmax) << std::endl;
		} else {
			std::cout<< finalQueueLength << std::endl;
		}
	}
  	//Freeing resources
	delete sender;

	return 0;
}
