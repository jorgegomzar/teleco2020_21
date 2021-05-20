// Author: Juan I. Asensio (ETSIT Telecomunicaci�n -
// Universidad de Valladolid - juaase@tel.uva.es)
// 5/May/2014 (updated 8/May/2015)
// Based on code from http://www.eng.uwi.tt/depts/elec/staff/rvadams/sramroop/
//
// Simulation of a DiffServ network


#include <string>
#include <sstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/diff-serv-queue.h"
#include "ns3/token-bucket.h"
#include "ns3/srtcm.h"
#include "ns3/trtcm.h"
#include "ns3/diff-serv-sla.h"
#include "ns3/wred.h"
#include "ns3/stat-collector.h"
#include "Sender.h"


using namespace std;
using namespace ns3;
using namespace etsit; //For Sender Class (see sender.cc)

NS_LOG_COMPONENT_DEFINE ("diffservtest");


//Global definition of trace file for the packet sink...
AsciiTraceHelper asciiTraceHelper;
Ptr<OutputStreamWrapper> streamArrivals_s2_9 = asciiTraceHelper.CreateFileStream ("P3-DiffServ-s2-arrivals_9.trace");
Ptr<OutputStreamWrapper> streamArrivals_s2_10 = asciiTraceHelper.CreateFileStream ("P3-DiffServ-s2-arrivals_10.trace");

//Callback for Packet sinking at s2
static void
receiverRx (Ptr<const Packet> p, const Address &addr)
{
        *streamArrivals_s2_9->GetStream() << Simulator::Now().GetNanoSeconds() << "\t" << p->GetSize() << std::endl;
}
static void
receiverRx_p (Ptr<const Packet> p, const Address &addr)
{
        *streamArrivals_s2_10->GetStream() << Simulator::Now().GetNanoSeconds() << "\t" << p->GetSize() << std::endl;
}

//Callback for Packets dropped at policy point in DS router (AF and BE traffic)
static void
r1_DropNonConformantAFBE_callback (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	*stream->GetStream () << Simulator::Now ().GetNanoSeconds () << "\t" << p->GetSize() << std::endl;
}

static void
r1_AQMDropAF1_callback (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	*stream->GetStream () << Simulator::Now ().GetNanoSeconds () << "\t" << p->GetSize() << std::endl;
}

static void
r1_DropTailAF1_callback (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	*stream->GetStream () << Simulator::Now ().GetNanoSeconds () << "\t" << p->GetSize() << std::endl;
}

static void
r1_DropTailBE_callback (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> p)
{
	*stream->GetStream () << Simulator::Now ().GetNanoSeconds () << "\t" << p->GetSize() << std::endl;
}

//MAIN
int main (int argc, char *argv[]) {

	//Labels...
	enum{drop = 256 };
	enum{ AF11 = 40, AF12 = 48, AF13 = 56, AF21 = 72, AF22 = 80, AF23 = 88, AF31 = 104, AF32 = 112, AF33 = 120, AF41 = 136, AF42 = 144, AF43 = 152, EF = 184, BE = 0};

	//LogComponentEnable("OnOffApplication", LOG_LEVEL_LOGIC);
	//LogComponentEnable("OnOffWebTrafficApplication", LOG_LEVEL_INFO);
	//LogComponentEnable("DiffServQueue", LOG_LEVEL_ALL);
	//LogComponentEnable("DiffServSla", LOG_LEVEL_ERROR);
	//LogComponentEnable("TokenBucket", LOG_LEVEL_INFO);
	//LogComponentEnable("SRTCM", LOG_LEVEL_INFO);
	//LogComponentEnable("TRTCM", LOG_LEVEL_INFO);
	//LogComponentEnable("WRED", LOG_LEVEL_INFO);

	//LogComponentEnable("UdpL4Protocol", LOG_LEVEL_ERROR);
	//LogComponentEnable("TcpL4Protocol", LOG_LEVEL_ERROR);
	//LogComponentEnable("StatCollector", LOG_LEVEL_INFO);

	//LogComponentEnable("PacketSink", LOG_LEVEL_INFO);

	////////////////////////////////////////////////
	//Command line arguments management and setting up trace files (similar to ITRT-P2)
	bool tracing = false;
	unsigned int rep = 1;
	double tmax = 1000.0; //simulation time length (default value might not be suitable)

	double lambda_s1 = 9.0; //service requests per second
	double meanPacketSize_s1 = 1000.0; //(bytes)
	bool fixedlength_s1 = true; //The DiffServ Implementation is not capable of dealing with UDP fragments!!!!!
	bool constantbitrate_s1 = true; //By default, the traffic is CBR (constant bit rate)...
	uint32_t IPBufferSize_s1 = 300; // In segments

	// Pesos WRR
	int AF1weight = 1;
	int AF2weight = 1;
	int AF3weight = 1;
	int AF4weight = 1;
	int BEweight  = 1; //Best effort traffic (i.e. traffic belonging to flows that are not classified in a class of traffic

	double bitRate_s1r1 = 10000000; //bps
	std::string linkDelay_s1r1 = "300ns";

	double bitRate_r2s2 = 10000000; //bps
	std::string linkDelay_r2s2 = "300ns";

	double bitRate_r1r2 = 100000; //bps
	std::string linkDelay_r1r2 = "30ms";

	/** LO NUEVO */
	double lambda_sPlus = 9.0;
	double meanPacketSize_sPlus = 1000.0; //(bytes)
	bool fixedlength_sPlus = true; //The DiffServ Implementation is not capable of dealing with UDP fragments!!!!!
	bool constantbitrate_sPlus = true; //By default, the traffic is CBR (constant bit rate)...
	uint32_t IPBufferSize_sPlus = 300; // In segments

	bool vip_sPlus = false;

	double bitRate_sPlusr1 = 10000000; //bps
	std::string linkDelay_sPlusr1 = "300ns";
	/** HASTA AQUI */

	CommandLine cmd;
	cmd.AddValue ("tracing", "Tracing. Default: 0", tracing);
	cmd.AddValue ("rep","Rep",rep);
	cmd.AddValue ("tmax","Simulation time (seconds). Default: 10000 sec.",tmax );
	cmd.AddValue ("lambda_s1","s1 Lambda. Default: 9 pkts/sec.",lambda_s1 );
	cmd.AddValue ("meanPacketSize_s1","s1 MeanPacketSize (bytes). Default: 1000 bytes.",meanPacketSize_s1);
	cmd.AddValue ("fixedlength_s1","Using fixed or exponential packet lengths for s1 (1=fixed, 0=exponential). Default: fixed (problems in DiffServ with UDP fragments", fixedlength_s1);
	cmd.AddValue ("constantbitrate_s1","Using fixed or exponential time intervals between packets in s1 (1=fixed, 0=exponential). Default: fixed", constantbitrate_s1);
	cmd.AddValue ("IPBufferSize_s1", "Number of IP packets the s1 IP entity should be able to store in its buffer for forwarding. Default: 300 packets)", IPBufferSize_s1);
	cmd.AddValue ("bitRate_s1r1", "Link s1->r1 BitRate (bps). Default: 10000000 bps", bitRate_s1r1);
	cmd.AddValue ("linkDelay_s1r1", "Delay of the s1->r1 p2p link. Default: 300ns.", linkDelay_s1r1);
	cmd.AddValue ("bitRate_r2s2", "Link r2->s2 BitRate (bps). Default: 10000000 bps", bitRate_r2s2);
	cmd.AddValue ("linkDelay_r2s2", "Delay of the r2->s2 p2p link. Default: 300ns.", linkDelay_r2s2);
	cmd.AddValue ("bitRate_r1r2", "Link r1->r2 BitRate (bps). Default: 100000 bps", bitRate_r1r2);
	cmd.AddValue ("linkDelay_r1r2", "Delay of the r1->r2 p2p link. Default: 30ms.", linkDelay_r1r2);

	/** LO NUEVO */
	cmd.AddValue ("lambda_sPlus","sPlus Lambda. Default: 9 pkts/sec.",lambda_sPlus );
	cmd.AddValue ("meanPacketSize_sPlus","sPlus MeanPacketSize (bytes). Default: 1000 bytes.",meanPacketSize_sPlus);
	cmd.AddValue ("fixedlength_sPlus","Using fixed or exponential packet lengths for sPlus (1=fixed, 0=exponential). Default: fixed (problems in DiffServ with UDP fragments", fixedlength_sPlus);
	cmd.AddValue ("constantbitrate_sPlus","Using fixed or exponential time intervals between packets in sPlus (1=fixed, 0=exponential). Default: fixed", constantbitrate_sPlus);
	cmd.AddValue ("IPBufferSize_sPlus", "Number of IP packets the sPlus IP entity should be able to store in its buffer for forwarding. Default: 300 packets)", IPBufferSize_sPlus);

	cmd.AddValue ("vip_sPlus", "Si 1, etiqueta el tráfico de sPlus como EF. Por defecto etiqueta el tráfico como BE)", vip_sPlus);

	cmd.AddValue ("AF1weight","Peso AF para el algoritmo WRR, por defecto: 1.", AF1weight);
	cmd.AddValue ("BEweight","Peso BE para el algoritmo WRR, por defecto: 1.", BEweight);

	cmd.AddValue ("bitRate_sPlusr1", "Link sPlus->r1 BitRate (bps). Default: 10000000 bps", bitRate_sPlusr1);
	cmd.AddValue ("linkDelay_sPlusr1", "Delay of the sPlus->r1 p2p link. Default: 300ns.", linkDelay_sPlusr1);
	/** HASTA AQUI */

	cmd.Parse(argc,argv);

	//Setting up trace files...
	AsciiTraceHelper asciiTraceHelper;
	Ptr<OutputStreamWrapper> streamArrivals_s1 = NULL, streamArrivals_sPlus = NULL;
	streamArrivals_s1 = asciiTraceHelper.CreateFileStream ("P3-DiffServ-s1-arrivals.trace");
	streamArrivals_sPlus = asciiTraceHelper.CreateFileStream ("P3-DiffServ-sPlus-arrivals.trace"); //  <------------ NUEVO

	SeedManager::SetRun(rep);

	////////////////////////////////////////////////
	//Topology

	NodeContainer nodes;

	//nodes.Create (4);
	nodes.Create (5); //  <------------ NUEVO

	PointToPointHelper pointToPoint_s1r1;
	std::stringstream bitRate_Stream_s1r1;
	bitRate_Stream_s1r1 << bitRate_s1r1/1000 << "Kbps\n";
	pointToPoint_s1r1.SetDeviceAttribute ("DataRate", StringValue(bitRate_Stream_s1r1.str()));
	pointToPoint_s1r1.SetChannelAttribute ("Delay", StringValue (linkDelay_s1r1));

	/** LO NUEVO */
	PointToPointHelper pointToPoint_sPlusr1;
	std::stringstream bitRate_Stream_sPlusr1;
	bitRate_Stream_sPlusr1 << bitRate_sPlusr1/1000 << "Kbps\n";
	pointToPoint_sPlusr1.SetDeviceAttribute ("DataRate", StringValue(bitRate_Stream_sPlusr1.str()));
	pointToPoint_sPlusr1.SetChannelAttribute ("Delay", StringValue (linkDelay_sPlusr1));
	/** HASTA AQUI */

	PointToPointHelper pointToPoint_r2s2;
	std::stringstream bitRate_Stream_r2s2;
	bitRate_Stream_r2s2 << bitRate_r2s2/1000 << "Kbps\n";
	pointToPoint_r2s2.SetDeviceAttribute ("DataRate", StringValue(bitRate_Stream_r2s2.str()));
	pointToPoint_r2s2.SetChannelAttribute ("Delay", StringValue (linkDelay_r2s2));

	NetDeviceContainer devices_s1r1;
	NetDeviceContainer devices_sPlusr1;  //  <------------ NUEVO
	NetDeviceContainer devices_r1r2;
	NetDeviceContainer devices_r2s2;

	devices_s1r1 = pointToPoint_s1r1.Install (nodes.Get(0),nodes.Get(1));
	devices_sPlusr1 = pointToPoint_sPlusr1.Install (nodes.Get(4),nodes.Get(1));  //  <------------ NUEVO
	devices_r2s2 = pointToPoint_r2s2.Install (nodes.Get(2),nodes.Get(3));

	Ptr<DiffServQueue> queue_r1 = CreateObject<DiffServQueue> ();
	Ptr<DropTailQueue> queue_rhelp = CreateObject<DropTailQueue> ();
	Ptr<OutputStreamWrapper> r1_DropNonConformantAFBE_Stream = asciiTraceHelper.CreateFileStream ("r1.DropNonConformantAFBE.trace");
	queue_r1->TraceConnectWithoutContext ("DropNonConformantAFBE", MakeBoundCallback(&r1_DropNonConformantAFBE_callback, r1_DropNonConformantAFBE_Stream));

	/** LO NUEVO */
	// AQMDropAF1
	Ptr<OutputStreamWrapper> r1_AQMDropAF1_Stream = asciiTraceHelper.CreateFileStream ("r1.AQMDropAF1.trace");
	queue_r1->TraceConnectWithoutContext ("AQMDropAF1", MakeBoundCallback(&r1_AQMDropAF1_callback, r1_AQMDropAF1_Stream));
	// DropTailAF1
	Ptr<OutputStreamWrapper> r1_DropTailAF1_Stream = asciiTraceHelper.CreateFileStream ("r1.DropTailAF1.trace");
	queue_r1->TraceConnectWithoutContext ("DropTailAF1", MakeBoundCallback(&r1_DropTailAF1_callback, r1_DropTailAF1_Stream));
	// DropTailBE
	Ptr<OutputStreamWrapper> r1_DropTailBE_Stream = asciiTraceHelper.CreateFileStream ("r1.DropTailBE.trace");
	queue_r1->TraceConnectWithoutContext ("DropTailBE", MakeBoundCallback(&r1_DropTailBE_callback, r1_DropTailBE_Stream));
	/** HASTA AQUI */

	Ptr<DropTailQueue> queue_r2 = CreateObject<DropTailQueue> ();
	Ptr<PointToPointChannel> channel_r1r2 = CreateObject<PointToPointChannel> ();
	Ptr<PointToPointNetDevice> dev_r1 = CreateObject<PointToPointNetDevice> ();
	Ptr<PointToPointNetDevice> dev_r2 = CreateObject<PointToPointNetDevice> ();

	dev_r1->SetQueue(queue_r1);
	dev_r2->SetQueue(queue_r2);
	dev_r1->SetAddress (Mac48Address::Allocate ());
	dev_r2->SetAddress (Mac48Address::Allocate ());

	Ptr<Node> r1 = nodes.Get(1);
	Ptr<Node> r2 = nodes.Get(2);

	r1->AddDevice (dev_r1);
	r2->AddDevice (dev_r2);

	dev_r1->Attach (channel_r1r2);
	dev_r2->Attach (channel_r1r2);

	devices_r1r2.Add (dev_r1);
	devices_r1r2.Add (dev_r2);

	dev_r1->SetDataRate(bitRate_r1r2);
	dev_r2->SetDataRate(bitRate_r1r2);

	channel_r1r2->SetAttribute("Delay",StringValue (linkDelay_r1r2));

	InternetStackHelper stack;
	stack.Install (nodes);

	Ipv4AddressHelper address_s1r1;
	address_s1r1.SetBase ("10.0.1.0", "255.255.255.0","0.0.0.1");
	Ipv4AddressHelper address_r1r2;
	address_r1r2.SetBase ("10.0.2.0", "255.255.255.0","0.0.0.1");
	Ipv4AddressHelper address_r2s2;
	address_r2s2.SetBase ("10.0.3.0", "255.255.255.0","0.0.0.1");
	Ipv4AddressHelper address_sPlusr1; //  <------------ NUEVO
	address_sPlusr1.SetBase ("10.0.4.0", "255.255.255.0","0.0.0.1"); //  <------------ NUEVO

	Ipv4InterfaceContainer interfaces_s1r1 = address_s1r1.Assign (devices_s1r1);
	Ipv4InterfaceContainer interfaces_r2s2 = address_r2s2.Assign (devices_r2s2);
	Ipv4InterfaceContainer interfaces_r1r2 = address_r1r2.Assign (devices_r1r2);
	Ipv4InterfaceContainer interfaces_sPlusr1 = address_sPlusr1.Assign (devices_sPlusr1); //  <------------ NUEVO

	////////////////////////////////////////////////

	//FOR INGRESS ROUTERS!!!!
	//1 - Flow Setup (how incoming packets are classified)
	Ptr<DiffServFlow> flow1Ptr = CreateObject<DiffServFlow> (001,"10.0.1.1","10.0.3.2",0,9); //Id, IP origin, IP dst, source port (0 for any), dst port.
	Ptr<DiffServFlow> flow2Ptr = CreateObject<DiffServFlow> (002,"10.0.4.1","10.0.3.2",0,10); //  <------------ NUEVO

	//2 - Conformance and Meter Specs (what to do when the traffic is not compliant with
	//the Metering Specification, e.g. how to remark or to drop a packet when there
	//are no available tokens in a token bucket... or when it is marked as "red"
	//in a srTCM...

	ConformanceSpec cSpec1;
	cSpec1.initialCodePoint = AF11; 		//Using the Assured Forwarding PHB (RFC 2597)
	//cSpec1.nonConformantActionI = AF12;	//We are very "strict" (if a packet is not compliant, we drop it... even
											//when there is no congestion... Uncomment this line for assigning
											//Non conformant packets to a different dropping probability
	cSpec1.nonConformantActionI = drop;
	cSpec1.nonConformantActionII = drop;

	/* Examples of other policies
	 * Another way of understanding this definitions:
	 * 		initialCodePoint = green packets
	 * 		nonConformantActionI = yellow packets
	 * 		nonConformantActionII = red packets
	 */
	/** LO NUEVO */
	ConformanceSpec cSpec2;
	cSpec2.initialCodePoint = BE;
	cSpec2.nonConformantActionI = drop;
	cSpec2.nonConformantActionII = drop;

	ConformanceSpec cSpec3;
	cSpec3.initialCodePoint = EF;
	cSpec3.nonConformantActionI = drop;
	cSpec3.nonConformantActionII = drop;
	/** HASTA AQUI */


	/*
	ConformanceSpec cSpec4;
	cSpec4.initialCodePoint = AF41;
	cSpec4.nonConformantActionI = AF42;
	cSpec4.nonConformantActionII = AF43;
	 */

	//3a - Meters setup (a way of telling the DiffServ router what Metering approaches can be used...

	Ptr<DiffServMeter> STB = Create<TokenBucket>();
	Ptr<DiffServMeter> srTCM = Create<SRTCM>();
	Ptr<DiffServMeter> trTCM = Create<TRTCM>();

	vector< Ptr<DiffServMeter> > myMeterVector;
	myMeterVector.push_back(STB);
	myMeterVector.push_back(srTCM);
	myMeterVector.push_back(trTCM);

	queue_r1->SetDiffServMeters(myMeterVector);

	//3b - Configuration of the actual metering functions to used (in this case, e.g., a tocket bucket)
	MeterSpec mSpec1;
	mSpec1.meterID = "TokenBucket"; //If the meter is a ToketBucket, only the cIR (int) and cBS (int) are used (cBS is the size of the token)
	mSpec1.cIR = 74016; //Commited Information Rate (bps)
						//This default value is equal to the average bitrate generated by s1
	mSpec1.cBS = 1028*9;	//Commited Burst Size (bytes)
	mSpec1.eBS = 0;		//Unused for "TokenBucket"
	mSpec1.pIR = 0;		//Unused for "TokenBucket"
	mSpec1.pBS = 0;		//Unused for "TokenBucket"

	/* Another example of a different meter (srTCM)
	MeterSpec mSpec2;
	mSpec2.meterID = "SRTCM"; //If the meter is a "SRTCM", only cIR/cBS/eBS are used
	mSpec2.cIR = 72000;
	mSpec2.cBS = 2000;
	mSpec2.eBS = 1500;
	mSpec2.pIR = 0;
	mSpec2.pBS = 0;
	*/


	//4 - SLA Setup
	Ptr<DiffServSla> sla2Ptr, sla1Ptr = CreateObject<DiffServSla>(001,cSpec1,mSpec1); //  <------------ NUEVO

	/** LO NUEVO */
	if  (!vip_sPlus)
		sla2Ptr = CreateObject<DiffServSla>(002,cSpec2,mSpec1); // BE
	else
		sla2Ptr = CreateObject<DiffServSla>(002,cSpec3,mSpec1); // EF
	/** HASTA AQUI */

	//5 - Which SLA is associated to each detected flow
	flow1Ptr->SetSla(sla1Ptr);
	flow2Ptr->SetSla(sla2Ptr); //  <------------ NUEVO

	//6 - Configuring the token bucket for the EF traffic (if we want to "enforce" the
	//agreement with the customer).
	int EFcIR = 72000; //bps
	int EFcBR = 2000; //bytes
	queue_r1->SetEFProfile(EFcIR,EFcBR);


	//7 - Passing all the above configuration to r1 (and setting up r1 as an "Edge" router)
	vector< Ptr<DiffServFlow> > myFlowVector;
	myFlowVector.push_back(flow1Ptr);
	myFlowVector.push_back(flow2Ptr); //Another Example
	queue_r1->SetDiffServFlows(myFlowVector);
	queue_r1->SetQueueMode("Edge"); //Ingress Router


	//FOR INGRESS AND CORE ROUTERS!!!!

	//1 - AQM (Active Queue Management)setup

	//WRED algorithm... It decides whether a packet is enqueue or dropped. That decision
	//depends on the DS field of the packet and of the current size of the queue.
	Ptr<WRED> AQM1Ptr = Create<WRED>();

	//This implementation only permits the setting up of dropped probabilities for the AF PHB
	//This implementation deals with 4 queues, one for each of the 3 AF classes (AF1, AF2, AF3, AF4)
	AQM1Ptr->SetAF1WRED(7, 10,50,100,  10,100,60,  10,100,30);
	AQM1Ptr->SetAF2WRED(7, 10,50,100,  10,100,60,  50,100,50);
	AQM1Ptr->SetAF3WRED(7, 10,50,100,  10,100,60,  50,100,50);
	AQM1Ptr->SetAF4WRED(7, 10,50,100,  10,100,60,  50,100,50);
	//EXPLANATION of the arguments (see http://www.eng.uwi.tt/depts/elec/staff/rvadams/sramroop/Class_DiffServAQM.htm)
	//arg1: exponential weight for calculating the current average queue length (the greater arg1, the more important
	//		the previous calculated average is.
	//arg2,arg3,arg4: configuration of class "red"
	//		arg2 (bytes): minimum threshold of the average queue length (if the current queue length < arg2, the packet is not dropped)
	//		arg3 (bytes): maximum threshold of the average queue length (if the current queue length > arg3, the packet is dropped)
	//		arg4 (%): maximum probability of packet drop. If  arg2 < current queue length < arg3, the packet is dropped
	//				with a probability which varies linearly between 0 and arg4 in the range (arg2,arg3)
	//arg5,arg6,arg7 configuration of class "yellow"
	//arg8,arg9,arg10: configuration of class "green"


	vector< Ptr<DiffServAQM> > myAQMVector;
	myAQMVector.push_back(AQM1Ptr);
	queue_r1->SetDiffServAQM (myAQMVector,"WRED","WRED","WRED","WRED");

	//2 - See http://www.eng.uwi.tt/depts/elec/staff/rvadams/sramroop/Core_Node_Design.htm
	//WRR,Queue size,
	//In each "round of the scheduler"
	// * If the EF queue is not empty, an EF packet is sent
	// * For each AF* queue and for the BE queue, if the corresponding weight>0, a packet is transmitted and weight-=1
	//int AF1weight = 1;
	//int AF2weight = 1;
	//int AF3weight = 1;
	//int AF4weight = 1;
	//int BEweight  = 1; //Best effort traffic (i.e. traffic belonging to flows that are not classified in a class of traffic
	queue_r1->SetWRRWeights(AF1weight,AF2weight,AF3weight,AF4weight,BEweight);


	int AF1queue = 100;
	int AF2queue = 100;
	int AF3queue = 100;
	int AF4queue = 100;
	int EFqueue  = 100; //Expedited Forwarding Class ("premium class", RFC 2598)
	int BEqueue  = 100; //Best effort traffic
	queue_r1->SetQueueSize(AF1queue,AF2queue,AF3queue,AF4queue,EFqueue,BEqueue);


	///////////////////////////////////////////////////////////////////////////////
	//Create Applications Here


	//Traffic sink at s2 (with callback)
	PacketSinkHelper receiverHelper_s2 ("ns3::UdpSocketFactory", InetSocketAddress(interfaces_r2s2.GetAddress(1), 9));
	ApplicationContainer serverApps_s2 = receiverHelper_s2.Install(nodes.Get(3)); //The packet sink is installed in s2 (nodes.Get(3))
	Ptr<Application> receiver = serverApps_s2.Get(0);
	Config::ConnectWithoutContext("/NodeList/3/ApplicationList/0/$ns3::PacketSink/Rx", MakeCallback(&receiverRx));

	/** LO NUEVO */
	PacketSinkHelper receiverHelper_s2_p ("ns3::UdpSocketFactory", InetSocketAddress(interfaces_r2s2.GetAddress(1), 10));
	ApplicationContainer serverApps_s2_p = receiverHelper_s2_p.Install(nodes.Get(3)); //The packet sink is installed in s2 (nodes.Get(3))
	Ptr<Application> receiver_p = serverApps_s2_p.Get(0);
	Config::ConnectWithoutContext("/NodeList/3/ApplicationList/1/$ns3::PacketSink/Rx", MakeCallback(&receiverRx_p));
	/** HASTA AQUI */
	//Traffic generation
	Sender *sender_s1 = new Sender (), *sender_sPlus = new Sender();

	//Is the traffic poissonian or CBR?
	if(!constantbitrate_s1) {
		sender_s1->SetCreationInterval(ExponentialVariable (1.0/lambda_s1 ));
	}else{
		sender_s1->SetCreationInterval(ConstantVariable(1.0/lambda_s1));
	}
	//Do the packets have fixed length... or are they distributed exponentially?
	if(!fixedlength_s1){
		sender_s1->SetPacketSize (ExponentialVariable (meanPacketSize_s1));
	}else{
		sender_s1->SetFixedPacketSize(meanPacketSize_s1);
	}
	sender_s1->SetStream(streamArrivals_s1);

	/** LO NUEVO */
	if(!constantbitrate_sPlus) {
		sender_sPlus->SetCreationInterval(ExponentialVariable (1.0/lambda_sPlus ));
	}else{
		sender_sPlus->SetCreationInterval(ConstantVariable(1.0/lambda_sPlus));
	}
	if(!fixedlength_sPlus){
		sender_sPlus->SetPacketSize (ExponentialVariable (meanPacketSize_sPlus));
	}else{
		sender_sPlus->SetFixedPacketSize(meanPacketSize_sPlus);
	}
	sender_sPlus->SetStream(streamArrivals_sPlus);
	/** HASTA AQUI */

	//Socket creation (obtained from udp-echo-client.cc
	TypeId tid_s1 = TypeId::LookupByName("ns3::UdpSocketFactory");
	Ptr<Socket> udp_socket_s1;
	udp_socket_s1 = Socket::CreateSocket(nodes.Get(0),tid_s1); //Connecting the transport entity with the network entity
	udp_socket_s1->Bind();
	udp_socket_s1->Connect(InetSocketAddress(interfaces_r2s2.GetAddress(1), 9));
	udp_socket_s1->SetRecvCallback(MakeCallback(&Sender::HandleRead, sender_s1));
	sender_s1->SetUdpSocket(udp_socket_s1); //Connecting the application with the transport entity

	/** LO NUEVO */
	TypeId tid_sPlus = TypeId::LookupByName("ns3::UdpSocketFactory");
	Ptr<Socket> udp_socket_sPlus;
	udp_socket_sPlus = Socket::CreateSocket(nodes.Get(4),tid_sPlus); //Connecting the transport entity with the network entity
	udp_socket_sPlus->Bind();
	udp_socket_sPlus->Connect(InetSocketAddress(interfaces_r2s2.GetAddress(1), 10));
	udp_socket_sPlus->SetRecvCallback(MakeCallback(&Sender::HandleRead, sender_sPlus));
	sender_sPlus->SetUdpSocket(udp_socket_sPlus); //Connecting the application with the transport entity
	/** HASTA AQUI */

	//Simulation Management
	Simulator::Schedule(Seconds (0.0001), &Sender::Start, sender_s1);
	Simulator::Schedule(Seconds (tmax), &Sender::Stop, sender_s1);
	serverApps_s2.Start (Seconds (0.0001));
	serverApps_s2.Stop (Seconds (tmax));

	/** LO NUEVO */
	Simulator::Schedule(Seconds (tmax/2), &Sender::Start, sender_sPlus);
	Simulator::Schedule(Seconds (tmax), &Sender::Stop, sender_sPlus);
	serverApps_s2_p.Start (Seconds (0.0001));
	serverApps_s2_p.Stop (Seconds (tmax));
	/** HASTA AQUI */

	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
	//pointToPoint_s1r1.EnablePcapAll("diffservtest"); //If needed...

	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}
