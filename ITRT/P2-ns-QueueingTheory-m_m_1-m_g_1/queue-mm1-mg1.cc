// Author: Juan I. Asensio (ETSIT Telecomunicaci�n -
// Universidad de Valladolid - juaase@tel.uva.es)
// 22/March/2017 - Updated 04/March/2021
// Based on code by M. Lacage published in
// E. Altman and T. Jim�nez, "NS Simulation for Beginners", Morgan & Claypool, 2012.
//
// Simulation of a M/M/1 or M/G/1 queue

#include <string>
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "ns3/random-variable.h"
#include "ns3/callback.h"
#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "ns3/command-line.h"
#include "ns3/point-to-point-module.h"

#include <list>


using namespace ns3;
using namespace std;
class UVAQueue
{
	public:
		UVAQueue();
		void SetBitRate(double bitrate);
		void SetAfterProcessed (Callback <void,Ptr <Packet> > receiver);
		void SetStreamQueue(Ptr<OutputStreamWrapper> stream);
		void SetStreamEndWork(Ptr<OutputStreamWrapper> stream);
		void Enqueue(Ptr<Packet> p);
		double GetLengthIntegrator();
		double GetFinalLength();
		void SetFinalLength();
	private:
		void StartWork (void );
		void EndWork (Ptr<Packet> work );
		Callback<void,Ptr<Packet> > m_receiver;
		std::list<Ptr<Packet> > m_queue;
		EventId m_working;
		double m_bitRate; //(bps)
		Ptr<OutputStreamWrapper> m_streamQueue;
		Ptr<OutputStreamWrapper> m_streamEndWork;
		//These variable are for computing Average QueueLength
		long m_clientsCount;
		double m_lengthIntegrator;
		double m_queueLength;
		double m_lastEvent;
		double m_lastEnqueue; //Since the queue is emptied even after the
							//end of the simulation time, we will register
							//in this variable the number of clients
							//in the queue in a previous moment
							//(e.g., at 98% of tmax)
};


UVAQueue::UVAQueue()
	: m_clientsCount(0),
	m_lengthIntegrator(0),
	m_queueLength(0),
	m_lastEvent(0)
	{}


void
UVAQueue::SetBitRate (double bitRate)
{
	m_bitRate = bitRate;
}

void
UVAQueue::SetAfterProcessed (Callback <void ,Ptr <Packet> > receiver)
{
	m_receiver = receiver;
}

void
UVAQueue::SetStreamQueue(Ptr<OutputStreamWrapper> stream) {

	m_streamQueue = stream;
}

void
UVAQueue::SetStreamEndWork(Ptr<OutputStreamWrapper> stream) {

	m_streamEndWork = stream;
}

void
UVAQueue :: Enqueue (Ptr <Packet> p)
{
	//Updating the "integrator" for calculating average queue size
	//std::cout<< Simulator::Now().GetNanoSeconds() << "\t\tm_lastEvent: " << m_lastEvent << "\tqueue: " << m_queue.size() << "\tm_lengthIntegrator: " << m_lengthIntegrator << "\n" << std::endl;
	m_lengthIntegrator += m_queue.size()*(Simulator::Now().GetNanoSeconds() - m_lastEvent);
	m_lastEvent = Simulator::Now().GetNanoSeconds();


	m_queue.push_back (p);

	//This is a change wrt original code. It is important to print the
	//queue size AFTER its size has been updated.
	if(m_streamQueue != NULL) {
		*m_streamQueue->GetStream() << Simulator::Now().GetNanoSeconds() << "\t\t" << m_queue.size () << std:: endl;
	}
	if (! m_working.IsRunning ()) //If there are no packets being processed right now... i.e., this packet is at first position in the queue and the server is "idle"
	{
		StartWork ();
	}
}

void
UVAQueue :: StartWork (void)
{
	double serviceDuration;

	//Updating the "integrator" for calculating average queue size
	//std::cout<< Simulator::Now().GetNanoSeconds() << "\t\tm_lastEvent: " << m_lastEvent << "\tqueue: " << m_queue.size() << "\tm_lengthIntegrator: " << m_lengthIntegrator << "\n" << std::endl;
	m_lengthIntegrator += m_queue.size()*(Simulator::Now().GetNanoSeconds() - m_lastEvent);
	m_lastEvent = Simulator::Now().GetNanoSeconds();

	Ptr <Packet> work = m_queue.front ();
	m_queue.pop_front ();
	serviceDuration = (work->GetSize() * 8)/m_bitRate;


	//This is a change wrt original code. It is important to print the
	//queue size AFTER its size has been updated.
	if(m_streamQueue != NULL) {
		*m_streamQueue->GetStream()  << Simulator::Now().GetNanoSeconds() << "\t\t" << m_queue.size () << std:: endl;
	}

	m_working = Simulator :: Schedule (Seconds (serviceDuration),
		&UVAQueue::EndWork, this, work);
}


void
UVAQueue :: EndWork (Ptr <Packet> work)
{
	if(m_streamEndWork != NULL) {
		*m_streamEndWork->GetStream()  << Simulator::Now().GetNanoSeconds() <<  std:: endl;
	}
	m_receiver (work);
	if (!m_queue.empty ())
	{
		StartWork ();
	}
}

double
UVAQueue :: GetLengthIntegrator()
{
		return m_lengthIntegrator;
}

double
UVAQueue :: GetFinalLength()
{
		return m_lastEnqueue;
}

void
UVAQueue :: SetFinalLength()
{
	m_lastEnqueue = m_queue.size(); //Length of the queue
}


class Sender
{
	public:
		Sender();
		void SetCreationInterval (RandomVariable v);
		void SetPacketSize (RandomVariable v);
		void SetFixedPacketSize(int size);
		void SetReceiver (Callback <void,Ptr <Packet> > receiver);
		void SetStream(Ptr<OutputStreamWrapper> stream);
		void Start (void);
		void Stop (void);
	private:
		void DoSend (void);
		RandomVariable m_creationInterval;
		Callback <void ,Ptr <Packet> > m_receiver;
		EventId m_sending;
		RandomVariable m_packetSize;
		int m_fixedPacketSize;
		Ptr<OutputStreamWrapper> m_stream;

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
	m_receiver (p);
	double sendInterval = m_creationInterval.GetValue ();
	m_sending = Simulator :: Schedule (Seconds (sendInterval),
		&Sender::DoSend,this );
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
Sender::SetReceiver (Callback <void,Ptr <Packet> >  receiver)
{
	m_receiver = receiver;
}

void
Sender::Start (void)
{
	DoSend ();
}

void
Sender::Stop(void)
{
	m_sending.Cancel ();
}


//Function to call (Callback) when receiving a packet for servicing

static void funcAfterProcessed (Ptr <Packet> p)
{
	//NOT NEEDED FOR THIS EXAMPLE
}



int main (int argc, char *argv[]) {
	bool tracing = false;
	bool averaging = false;
	bool fixedlength = false;
	unsigned int rep = 1;
	double lambda = 11.0; //service requests per second
	double tmax = 2000.0;
	double meanPacketSize = 1000.0; //(bytes)
	double bitRate = 100000.0; //(bps)
	double ro;

	AsciiTraceHelper asciiTraceHelper;
	Ptr<OutputStreamWrapper> streamArrivals = NULL;
	Ptr<OutputStreamWrapper> streamClientsInQueue = NULL;
	Ptr<OutputStreamWrapper> streamOutputs = NULL;


	CommandLine cmd;
	cmd.AddValue ("tracing", "Tracing", tracing);
	cmd.AddValue ("averaging", "Calculating average Q or not (not by default)", averaging);
	cmd.AddValue ("rep","Rep",rep);
	cmd.AddValue ("lambda","Lambda",lambda );
	cmd.AddValue ("meanPacketSize","MeanPacketSize (bytes)",meanPacketSize);
	cmd.AddValue ("bitRate", "BitRate (bps)", bitRate);
	cmd.AddValue ("tmax","Simulation time (seconds)",tmax );
	cmd.AddValue ("fixedlength","Using fixed or exponential packet lengths (1=fixed, 0=exponential). Default: exponential", fixedlength);
	cmd.Parse(argc,argv);

	ro = lambda/(bitRate/(meanPacketSize*8));

	streamArrivals = asciiTraceHelper.CreateFileStream ("P2-ns-QueueingTheory-arrivals.trace");
	streamClientsInQueue = asciiTraceHelper.CreateFileStream("P2-ns-QueueingTheory-clientsinqueue.trace");
	streamOutputs = asciiTraceHelper.CreateFileStream("P2-ns-QueueingTheory-outputs.trace");

	SeedManager::SetRun(rep);
	UVAQueue *queue = new UVAQueue ();
	queue->SetBitRate (bitRate);
	queue->SetAfterProcessed(MakeCallback(& funcAfterProcessed ));
	queue->SetStreamQueue(streamClientsInQueue);
	queue->SetStreamEndWork(streamOutputs);

	Sender *sender = new Sender ();
	sender->SetCreationInterval(ExponentialVariable (1.0/ lambda ));
	if(!fixedlength){
		sender->SetPacketSize (ExponentialVariable (meanPacketSize));
	}else{
		sender->SetFixedPacketSize(meanPacketSize);
	}
	sender->SetReceiver(MakeCallback (&UVAQueue::Enqueue, queue));
	sender->SetStream(streamArrivals);

	Simulator::Schedule(Seconds (0.0001), &Sender::Start, sender);
	//This event will invoke the callback to register
	//the number of packets in the buffer (e.g., at
	//the 98% of the simulation time)
	Simulator::Schedule(Seconds (0.98*tmax), &UVAQueue::SetFinalLength, queue);
	Simulator::Schedule(Seconds (tmax), &Sender::Stop, sender);
	Simulator::Run();


	if(tracing) {
		if(!fixedlength){
			std::cout << "Expected Average Queue Size (M/M/1): ";
			std::cout << (ro*ro)/(1-ro) << "\n";
		}else{
			std::cout << "Expected Average Queue Size (M/G/1): ";
			std::cout << ((lambda*lambda)*((meanPacketSize*8)/bitRate)*((meanPacketSize*8)/bitRate))/(2*(1-ro)) << "\n";

		}
		std::cout << queue->GetFinalLength() << " Packets in the buffer at the end of the simulation\n";
		std::cout << "Average Buffer Utilization: " << (queue->GetLengthIntegrator()/1000000000/tmax) << " Packets\n";

	} else {
		if(averaging) {
		  	std::cout<< (queue->GetLengthIntegrator()/1000000000/tmax) << std::endl;
		} else {
			std::cout<< queue->GetFinalLength() << std::endl;
		}
	}


	Simulator::Destroy();
	delete sender;
	delete queue;
	return 0;
}
