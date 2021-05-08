/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 */
#include "ns3/log.h"
#include "ns3/stat-collector.h"

NS_LOG_COMPONENT_DEFINE ("StatCollector");

namespace ns3 {


//BEGIN juaase

NS_OBJECT_ENSURE_REGISTERED (SeqIdTag);

TypeId
SeqIdTag::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SeqIdTag")
    .SetParent<Tag> ()
    .AddConstructor<SeqIdTag> ()
  ;
  return tid;
}
TypeId
SeqIdTag::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}
uint32_t
SeqIdTag::GetSerializedSize (void) const
{
  //NS_LOG_FUNCTION (this);
  return 4;
}
void
SeqIdTag::Serialize (TagBuffer buf) const
{
  //NS_LOG_FUNCTION (this << &buf);
  buf.WriteU32 (m_seqId);
}
void
SeqIdTag::Deserialize (TagBuffer buf)
{
  //NS_LOG_FUNCTION (this << &buf);
  m_seqId = buf.ReadU32 ();
}
void
SeqIdTag::Print (std::ostream &os) const
{
  //NS_LOG_FUNCTION (this << &os);
  os << "SeqId=" << m_seqId;
}
SeqIdTag::SeqIdTag ()
  : Tag ()
{
  //NS_LOG_FUNCTION (this);
}

SeqIdTag::SeqIdTag (uint32_t id)
  : Tag (),
    m_seqId (id)
{
  //NS_LOG_FUNCTION (this << id);
}
void
SeqIdTag::SetSeqId (uint32_t id)
{
  //NS_LOG_FUNCTION (this << id);
  m_seqId = id;
}
uint32_t
SeqIdTag::GetSeqId (void) const
{
  //NS_LOG_FUNCTION (this);
  return m_seqId;
}

uint32_t
SeqIdTag::AllocateSeqId (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  static uint32_t nextSeqId = 1;
  uint32_t seqId = nextSeqId;
  nextSeqId++;
  return seqId;
}


//////


NS_OBJECT_ENSURE_REGISTERED (SeqIdQueueTag);

TypeId
SeqIdQueueTag::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SeqIdQueueTag")
    .SetParent<Tag> ()
    .AddConstructor<SeqIdQueueTag> ()
  ;
  return tid;
}
TypeId
SeqIdQueueTag::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}
uint32_t
SeqIdQueueTag::GetSerializedSize (void) const
{
  //NS_LOG_FUNCTION (this);
  return 4;
}
void
SeqIdQueueTag::Serialize (TagBuffer buf) const
{
  //NS_LOG_FUNCTION (this << &buf);
  buf.WriteU32 (m_seqId);
}
void
SeqIdQueueTag::Deserialize (TagBuffer buf)
{
  //NS_LOG_FUNCTION (this << &buf);
  m_seqId = buf.ReadU32 ();
}
void
SeqIdQueueTag::Print (std::ostream &os) const
{
  //NS_LOG_FUNCTION (this << &os);
  os << "SeqId=" << m_seqId;
}
SeqIdQueueTag::SeqIdQueueTag ()
  : Tag ()
{
  //NS_LOG_FUNCTION (this);
}

SeqIdQueueTag::SeqIdQueueTag (uint32_t id)
  : Tag (),
    m_seqId (id)
{
  //NS_LOG_FUNCTION (this << id);
}
void
SeqIdQueueTag::SetSeqId (uint32_t id)
{
  //NS_LOG_FUNCTION (this << id);
  m_seqId = id;
}
uint32_t
SeqIdQueueTag::GetSeqId (void) const
{
  //NS_LOG_FUNCTION (this);
  return m_seqId;
}

uint32_t
SeqIdQueueTag::AllocateSeqId (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  static uint32_t nextSeqIdQueue = 1;
  uint32_t seqIdQueue = nextSeqIdQueue;
  nextSeqIdQueue++;
  return seqIdQueue;
}




//END juaase

NS_OBJECT_ENSURE_REGISTERED (StatCollector);

TypeId
StatCollector::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::StatCollector")
    .SetParent<Object> ()
    .AddConstructor<StatCollector> ()
    ;
  return tid;
}

StatCollector:: StatCollector ()
{

}


StatCollector::~StatCollector ()
{

}

vector<FourTuple> StatCollector::m_flowVector;
vector<int> StatCollector::m_sequenceVector;
int StatCollector::m_flowId;
int StatCollector::m_seqId;
float StatCollector::m_txTime;
float StatCollector::m_rxTime;

float StatCollector::m_delay;
float StatCollector::m_delayVariation;
float StatCollector::m_jitter;
bool  StatCollector::m_reordered;

float StatCollector::m_delayLossThreshold = 10;
bool  StatCollector::m_collectStats = false;
bool  StatCollector::m_collectStatsQueue = false;

bool  StatCollector::m_summaryOnly = false;

vector< vector<PacketStatistics> > StatCollector::m_statVector;


//Queues
 int StatCollector::m_queueId;
 int StatCollector::m_pHBQueueId;
 int StatCollector::m_seqIdQueue;
 int StatCollector::m_currentQueueSize;

 float StatCollector::m_enqueueTime;
 float StatCollector::m_dequeueTime;
 float StatCollector::m_queuedTime;
vector< vector<  vector< PacketStatisticsQueue> >  > StatCollector::m_statVectorQueue;
vector<  vector<int> >  StatCollector::m_sequenceVectorQueue;

 vector< vector< float> > StatCollector::averageQueueLengthVector;
 vector< vector< float> > StatCollector::lastEnqueueDequeueTime;



uint32_t StatCollector::AllocateFlowId (void)
{
  static uint32_t nextFlowId = 0;
  uint32_t flowId = nextFlowId;
  nextFlowId++;
  return flowId;
}


void StatCollector::SetDelayLossThreshold(float thresholdTime)
{
 m_delayLossThreshold = thresholdTime;
}


void StatCollector::EnableEndToEndStatCollection(void)
{
 m_collectStats = true;
}

void StatCollector::EnableQueueStatCollection(void)
{
 m_collectStatsQueue = true;
}


void StatCollector:: ClassifyPacket( Ipv4Address scrAddress, Ipv4Address destAddress , int scrPort, int destPort)
{
NS_LOG_INFO("ClassifyPacket:");

FourTuple tuple;
tuple.scrAddress = scrAddress;
tuple.destAddress = destAddress;
tuple.scrPort = scrPort;
tuple.destPort = destPort;



if (m_flowVector.empty())
{
NS_LOG_INFO("First Classification: "<< " srcAddress: "<<tuple.scrAddress<< " destAddress: " << tuple.destAddress<<" sport: "<< tuple.scrPort <<" dport: "<<tuple.destPort);
m_flowId = StatCollector::AllocateFlowId();
m_flowVector.push_back(tuple);
m_sequenceVector.push_back(0);

//Rx setup
vector<PacketStatistics> packetStatVector1;
m_statVector.push_back(packetStatVector1);
NS_LOG_INFO("Given FlowId: " << m_flowId);
return;
}



FourTuple tupleVector;

for ( uint32_t i = 0 ; i < m_flowVector.size() ; i++)
 {


tupleVector = m_flowVector.at(i);

if ( (tuple.scrAddress == tupleVector.scrAddress) && (tuple.destAddress == tupleVector.destAddress) && (tuple.scrPort == tupleVector.scrPort) && (tuple.destPort ==  tupleVector.destPort) )
  {
   NS_LOG_INFO("Flow already classified");
   m_flowId = i;
   NS_LOG_INFO("FlowId: " << m_flowId);
   return;
  }

 }



NS_LOG_INFO("Flow not classified: "<< " srcAddress: "<<tuple.scrAddress<< " destAddress: " << tuple.destAddress<<" sport: "<< tuple.scrPort <<" dport: "<<tuple.destPort);

m_flowId = StatCollector::AllocateFlowId();
m_flowVector.push_back(tuple);
m_sequenceVector.push_back(0);

//Rx setup
vector<PacketStatistics> packetStatVector2;
m_statVector.push_back(packetStatVector2);
NS_LOG_INFO("Given FlowId: " << m_flowId);
return;
}




void StatCollector::PrepareTx(Ptr<Packet> packet, Ipv4Address scrAddress, Ipv4Address destAddress , int scrPort, int destPort)
{
NS_LOG_INFO("PrepareTx");

if (m_collectStats == false)
{
 NS_LOG_INFO("Tx: End To End Stat Collector not enabled");
 return;
}

ClassifyPacket(scrAddress, destAddress, scrPort, destPort);

FlowIdTag flowTag;
flowTag.SetFlowId(m_flowId);
packet->AddPacketTag (flowTag);
NS_LOG_INFO("Tx FlowIdTag: " << flowTag.GetFlowId());

m_seqId = m_sequenceVector.at(m_flowId);
m_seqId = m_seqId +1 ;
m_sequenceVector.at(m_flowId) = m_seqId;


SeqIdTag seqTag;
seqTag.SetSeqId(m_seqId);
packet->AddPacketTag (seqTag);
NS_LOG_INFO("Tx SeqIdTag: " << seqTag.GetSeqId());



PacketStatistics ps;
ps.sequenceNumber = m_seqId;
ps.txTime = (Simulator::Now()).GetSeconds();
ps.rxTime = undefined;
ps.delay  = undefined;
ps.delayVariation  = undefined;
ps.jitter = undefined;
ps.loss = 1;
ps.packetSize = packet->GetSize();
( m_statVector.at(m_flowId) ).push_back(ps);


}


void StatCollector::RecordRx(Ptr<Packet> packet)
{
NS_LOG_INFO("RecordRx");

if (m_collectStats == false)
{
 NS_LOG_INFO("Rx: End To End Stat Collector not enabled");
 return;
}

FlowIdTag flowTag;
packet->RemovePacketTag (flowTag);
m_flowId = flowTag.GetFlowId();
NS_LOG_INFO("Rx FlowId: " << m_flowId);



SeqIdTag seqTag;
packet->RemovePacketTag (seqTag);
m_seqId = seqTag.GetSeqId();
NS_LOG_INFO("Rx SeqId: " <<m_seqId);




m_txTime = ( (m_statVector.at(m_flowId) ).at(m_seqId-1) ).txTime;
NS_LOG_INFO("Tx time: " <<m_txTime);
m_rxTime = (Simulator::Now()).GetSeconds();
NS_LOG_INFO("Rx time: " <<m_rxTime);



//Delay
m_delay = m_rxTime - m_txTime;
NS_LOG_INFO("Delay: " <<m_delay);
NS_LOG_INFO("");

//DelayLoss check-if within threshold the packet is accepted,if not the packet is counted as lost
if (m_delay < m_delayLossThreshold)
{

PacketStatistics ps = (m_statVector.at(m_flowId) ).at(m_seqId-1);
ps.rxTime = m_rxTime;
ps.delay  = m_delay;
ps.loss = 0;

//Delay Variation
 if (m_seqId != 1)
 {
 PacketStatistics ps2 = (m_statVector.at(m_flowId) ).at(m_seqId-2);

  if(ps2.delay != undefined)
  {
  m_delayVariation = (ps.delay) - (ps2.delay);

  ps.delayVariation = fabs(m_delayVariation);
  }

 }


(m_statVector.at(m_flowId) ).at(m_seqId-1) = ps;

}//DelayLoss check


}



//Queues Stat Collection


uint32_t StatCollector::AllocateQueueId (void)
{
  static uint32_t nextQueueId = 0;
  uint32_t queueId = nextQueueId;
  nextQueueId++;

vector<  vector< PacketStatisticsQueue>  > queueVector;
vector< PacketStatisticsQueue> phbQueueVectorAF1;
vector< PacketStatisticsQueue> phbQueueVectorAF2;
vector< PacketStatisticsQueue> phbQueueVectorAF3;
vector< PacketStatisticsQueue> phbQueueVectorAF4;
vector< PacketStatisticsQueue> phbQueueVectorEF;
vector< PacketStatisticsQueue> phbQueueVectorBE;

queueVector.push_back(phbQueueVectorAF1);
queueVector.push_back(phbQueueVectorAF2);
queueVector.push_back(phbQueueVectorAF3);
queueVector.push_back(phbQueueVectorAF4);
queueVector.push_back(phbQueueVectorEF);
queueVector.push_back(phbQueueVectorBE);

m_statVectorQueue.push_back(queueVector);

//Sequence numbers

vector<int> seqVector;
seqVector.push_back(0);
seqVector.push_back(0);
seqVector.push_back(0);
seqVector.push_back(0);
seqVector.push_back(0);
seqVector.push_back(0);

m_sequenceVectorQueue.push_back(seqVector);

//Average Queue size

vector<float> avgPHBSize;
avgPHBSize.push_back(0);
avgPHBSize.push_back(0);
avgPHBSize.push_back(0);
avgPHBSize.push_back(0);
avgPHBSize.push_back(0);
avgPHBSize.push_back(0);

vector<float> avgPHBTime;
avgPHBTime.push_back(0);
avgPHBTime.push_back(0);
avgPHBTime.push_back(0);
avgPHBTime.push_back(0);
avgPHBTime.push_back(0);
avgPHBTime.push_back(0);


averageQueueLengthVector.push_back(avgPHBSize);
lastEnqueueDequeueTime.push_back(avgPHBTime);


  return queueId;
}




void StatCollector::Enqueue(int queueId , int pHBQueueId, Ptr<Packet> packet, bool drop , int currentQueueSize )
{

NS_LOG_INFO("StatCollector::Enqueue");

if (m_collectStatsQueue == false)
{
 NS_LOG_INFO("Enqueue: Queue Stat Collector not enabled");
 return;
}

NS_LOG_INFO("QueueId: "<<queueId<<" PHB QueueId: "<<pHBQueueId<<" Drop: "<<drop);

m_queueId = queueId;
m_pHBQueueId = pHBQueueId;
m_currentQueueSize = currentQueueSize;

m_seqIdQueue = ((m_sequenceVectorQueue.at(m_queueId) ).at(m_pHBQueueId) );
m_seqIdQueue = m_seqIdQueue + 1;
((m_sequenceVectorQueue.at(m_queueId) ).at(m_pHBQueueId) ) = m_seqIdQueue;

NS_LOG_INFO("Sequence Number"<<m_seqIdQueue);

if (drop == 1)
{
 PacketStatisticsQueue psq;
 psq.sequenceNumber = m_seqIdQueue;
 psq.enqueueTime = (Simulator::Now()).GetSeconds();
 psq.dequeueTime = undefined;
 psq.queuedTime = undefined;
 psq.currentQueueSize = m_currentQueueSize;
 psq.drop = 1;
 psq.packetSize = packet->GetSize();

( (m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId) ).push_back(psq);

NS_LOG_INFO("Vector Size: "<<((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).size());
NS_LOG_INFO("");

return;
}


SeqIdQueueTag seqIdQueueTag(m_seqIdQueue);
packet->AddPacketTag (seqIdQueueTag);
NS_LOG_INFO("Enqueue: seqIdQueueTag: " << seqIdQueueTag.GetSeqId());


PacketStatisticsQueue psq2;
 psq2.sequenceNumber = m_seqIdQueue;
 psq2.enqueueTime = (Simulator::Now()).GetSeconds();
 psq2.dequeueTime = undefined;
 psq2.queuedTime = undefined;
 psq2.currentQueueSize = m_currentQueueSize;
 psq2.drop = 0;
 psq2.packetSize = packet->GetSize();

( (m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId) ).push_back(psq2);

NS_LOG_INFO("Vector Size: "<<((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).size());
NS_LOG_INFO("");


//Average Queue Size
float lastEnqueueDequeue = (lastEnqueueDequeueTime.at(queueId) ).at(pHBQueueId);
float timeNow = (Simulator::Now()).GetSeconds();
float avgQueueSizeOld = ( averageQueueLengthVector.at(queueId) ).at(pHBQueueId);
NS_LOG_ERROR(" Time now "<<timeNow<<" time last "<<lastEnqueueDequeue<<" oldAVG "<<avgQueueSizeOld);
float avgQueueSizeNew = avgQueueSizeOld + ( currentQueueSize *(timeNow - lastEnqueueDequeue) );
NS_LOG_ERROR("newAVG"<<avgQueueSizeNew);
//update

(lastEnqueueDequeueTime.at(queueId) ).at(pHBQueueId) = timeNow;
( averageQueueLengthVector.at(queueId) ).at(pHBQueueId) = avgQueueSizeNew;

}





void StatCollector::Dequeue(int queueId , int pHBQueueId, Ptr<Packet> packet , int currentQueueSize)
{

NS_LOG_INFO("StatCollector:Dequeue");

if (m_collectStatsQueue == false)
{
 NS_LOG_INFO("Dequeue: Queue Stat Collector not enabled");
 return;
}

NS_LOG_INFO("QueueId: "<<queueId<<" PHB QueueId: "<<pHBQueueId);

m_queueId = queueId;
m_pHBQueueId = pHBQueueId;

SeqIdQueueTag seqIdQueueTag;
packet->RemovePacketTag (seqIdQueueTag);
m_seqIdQueue = seqIdQueueTag.GetSeqId();
NS_LOG_INFO("Dequeue: Packet SeqId: " <<m_seqIdQueue);



m_enqueueTime = (  ((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).at(m_seqIdQueue-1) ).enqueueTime;
NS_LOG_INFO("Dequeue: Packet Enqueue time: " <<m_enqueueTime);
m_dequeueTime = (Simulator::Now()).GetSeconds();
NS_LOG_INFO("Dequeue: Packet Dequeue time: " <<m_dequeueTime);

//Queued Time

m_queuedTime = m_dequeueTime - m_enqueueTime;
NS_LOG_INFO("Dequeue: Packet Queued time: " <<m_queuedTime);

NS_LOG_INFO("Size of Vector: " <<((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).size());
NS_LOG_INFO("Accessed field: " << m_seqIdQueue -1);
NS_LOG_INFO("");

PacketStatisticsQueue psq3 = ((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).at(m_seqIdQueue-1);

psq3.dequeueTime = m_dequeueTime;
psq3.queuedTime = m_queuedTime;

((m_statVectorQueue.at(m_queueId) ).at(m_pHBQueueId)).at(m_seqIdQueue-1) = psq3;



//Average Queue Size
float lastEnqueueDequeue = (lastEnqueueDequeueTime.at(queueId) ).at(pHBQueueId);
float timeNow = (Simulator::Now()).GetSeconds();
float avgQueueSizeOld = ( averageQueueLengthVector.at(queueId) ).at(pHBQueueId);
NS_LOG_ERROR(" Time now "<<timeNow<<" time last "<<lastEnqueueDequeue<<" oldAVG "<<avgQueueSizeOld);
float avgQueueSizeNew = avgQueueSizeOld + ( currentQueueSize *(timeNow - lastEnqueueDequeue) );
NS_LOG_ERROR("newAVG"<<avgQueueSizeNew);
//update

(lastEnqueueDequeueTime.at(queueId) ).at(pHBQueueId) = timeNow;
( averageQueueLengthVector.at(queueId) ).at(pHBQueueId) = avgQueueSizeNew;
}









//OutPut

 void StatCollector::OutputEndToEndStats(void)
{

ofstream myfile;
myfile.open("mytextfile.txt");

myfile<<endl<<setw(90)<<"****STATISTICS COLLECTOR****"<<endl<<endl<<endl;

myfile<<left;

myfile<<"Total number of flows: "<<m_statVector.size()<<endl;


for (uint32_t j = 0; j<m_statVector.size(); j++)
{
myfile<<"----------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

myfile<<"Flow number: "<<j<<endl;

myfile<<"Source IP Address:       "<<(m_flowVector.at(j) ).scrAddress<<endl;
myfile<<"Destination IP Address:  "<<(m_flowVector.at(j) ).destAddress<<endl;
myfile<<"Source Port Number:      "<<(m_flowVector.at(j) ).scrPort<<endl;
myfile<<"Destination Port Number: "<<(m_flowVector.at(j) ).destPort<<endl<<endl;


vector<PacketStatistics> psVector = m_statVector.at(j);

    myfile<<"Flow Summary: "<<endl;

    //Packet Loss

    float numberOfPacketsDropped = 0;
    bool packetDrop = 0;
    float percentageLoss = 0;

   for (uint32_t l = 0; l< psVector.size(); l++)
   {
    packetDrop = (psVector.at(l) ).loss;
    if (packetDrop == 1)
    {
     numberOfPacketsDropped++;
    }

   }

   percentageLoss = (numberOfPacketsDropped/psVector.size() )*100 ;

   myfile<<"Number of packets sent:     "<<psVector.size()<<endl;
   myfile<<"Number of packets dropped:  "<<numberOfPacketsDropped<<endl;
   myfile<<"Percentage of packets lost: "<<percentageLoss<<"%"<<endl;


/*
   //Delay

  int delayCount = 0;
  float packetDelay;
  float totalPacketDelay = 0;
  float averagePacketDelay = 0;

  for (uint32_t m = 0; m< psVector.size(); m++)
   {
    packetDelay = (psVector.at(m) ).delay;
    if (packetDelay != undefined)
    {
     totalPacketDelay = totalPacketDelay + (psVector.at(m) ).delay;
     delayCount++;
    }

   }

   averagePacketDelay = totalPacketDelay / delayCount;
   myfile<<"Average packet delay:       "<<averagePacketDelay<<endl;

*/



vector<float> mySortingVector;

mySortingVector.clear();

for(uint32_t a = 0 ; a < psVector.size(); a++)
{
  mySortingVector.push_back((psVector.at(a) ).delay);
}

StatCollector::ShellSort(mySortingVector);

float delayPercentile = StatCollector::Get50THPercentile(mySortingVector);

myfile<<"Delay 50th percentile:      "<<delayPercentile<<endl;




/*
  //Delay Variation

  int delayVariationCount = 0;
  float packetDelayVariation;
  float totalPacketDelayVariation = 0;
  float averagePacketDelayVariation = 0;

  for (uint32_t n = 0; n< psVector.size(); n++)
   {
    packetDelayVariation = (psVector.at(n) ).delayVariation;
    if (packetDelayVariation != undefined)
    {
     totalPacketDelayVariation = totalPacketDelayVariation + fabs ((psVector.at(n) ).delayVariation);
     delayVariationCount++;
    }

   }

   averagePacketDelayVariation = totalPacketDelayVariation / delayVariationCount;
   myfile<<"Average delay variation:    "<<averagePacketDelayVariation<<endl<<endl<<endl;
*/

vector<float> mySortingVector2;

mySortingVector2.clear();

for(uint32_t b = 0 ; b < psVector.size(); b++)
{
  mySortingVector2.push_back((psVector.at(b) ).delayVariation);
}

StatCollector::ShellSort(mySortingVector2);

float delayVPercentile = StatCollector::Get50THPercentile(mySortingVector2);

myfile<<"DelayVar 50th percentile:   "<<delayVPercentile<<endl;




if(m_summaryOnly == false)
{

myfile<<setw(21)<<"Sequence Numbers"<<setw(21)<<"Tx Time"<<setw(21)<<"Rx Time"<<setw(21)<<"Delay"<<setw(21)<<"Delay Variation"<<setw(21)<<"Packet Loss"<<setw(21)<<"Packet Size"<<endl<<endl;

   for (uint32_t k = 0; k< psVector.size(); k++)
   {
    myfile<<setw(21)<<(psVector.at(k) ).sequenceNumber;
    myfile<<setw(21)<<(psVector.at(k) ).txTime;
    myfile<<setw(21)<<(psVector.at(k) ).rxTime;
    myfile<<setw(21)<<(psVector.at(k) ).delay;
    myfile<<setw(21)<<(psVector.at(k) ).delayVariation;
    myfile<<setw(21)<<(psVector.at(k) ).loss;
    myfile<<setw(21)<<(psVector.at(k) ).packetSize<<endl;
   }
    myfile<<endl<<endl;

}

myfile<<"-----------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
myfile<<endl<<endl<<endl<<endl<<endl<<endl;

}


myfile.close();




}

 void StatCollector::OutputQueueStats(void)
{

//Output Queue

ofstream myfile2;
myfile2.open("mytextfile2.txt");

myfile2<<endl<<setw(90)<<"****STATISTICS COLLECTOR****"<<endl<<endl<<endl;

myfile2<<left;

myfile2<<"Total number of DiffServQueues: "<<m_statVectorQueue.size()<<endl;



 for (uint32_t i = 0; i<m_statVectorQueue.size(); i++)
 {
myfile2<<"******************************************************************************************************************************************************"<<endl<<endl;


vector < vector<PacketStatisticsQueue> > queueVector = m_statVectorQueue.at(i);
vector<float> queueVectorAVG = averageQueueLengthVector.at(i);

  for (uint32_t j = 0; j<queueVector.size(); j++)
  {

myfile2<<"DiffServQueue number: "<<i<<endl<<endl;

   switch(j)
   {

   case 0:
   myfile2<<"PHB Queue number: "<<j<<"--AF1 Queue"<<endl<<endl;
   break;

   case 1:
   myfile2<<"PHB Queue number: "<<j<<"--AF2 Queue"<<endl<<endl;
   break;

   case 2:
   myfile2<<"PHB Queue number: "<<j<<"--AF3 Queue"<<endl<<endl;
   break;

   case 3:
   myfile2<<"PHB Queue number: "<<j<<"--AF4 Queue"<<endl<<endl;
   break;

   case 4:
   myfile2<<"PHB Queue number: "<<j<<"--EF Queue"<<endl<<endl;
   break;

   case 5:
   myfile2<<"PHB Queue number: "<<j<<"--BE Queue"<<endl<<endl;
   break;

   default:
   myfile2<<"PHB Queue not found "<<endl<<endl;
   }


   vector<PacketStatisticsQueue> pHBQueueVector = queueVector.at(j);


    myfile2<<"PHB Queue Summary: "<<endl;

    //Packet Loss

    float numberOfPacketsDropped = 0;
    bool packetDrop = 0;
    float percentageLoss = 0;

   for (uint32_t l = 0; l< pHBQueueVector.size(); l++)
   {
    packetDrop = (pHBQueueVector.at(l) ).drop;
    if (packetDrop == 1)
    {
     numberOfPacketsDropped++;
    }

   }

   percentageLoss = (numberOfPacketsDropped/pHBQueueVector.size() )*100 ;

   myfile2<<"Total number of packets to be enqueued: "<<pHBQueueVector.size()<<endl;
   myfile2<<"Total number of packets dropped:        "<<numberOfPacketsDropped<<endl;
   myfile2<<"Percentage of packets dropped:          "<<percentageLoss<<"%"<<endl;

/*
  //Queued Time

  int queueCount = 0;
  float queuedTime = 0;
  float totalQueueTime = 0;
  float averageQueuedTime = 0;

  for (uint32_t m = 0; m< pHBQueueVector.size(); m++)
   {
    queuedTime = (pHBQueueVector.at(m) ).queuedTime;
    if (queuedTime != undefined)
    {
     totalQueueTime = totalQueueTime + (pHBQueueVector.at(m) ).queuedTime;
     queueCount++;
    }

   }

   averageQueuedTime = totalQueueTime / queueCount;
   myfile2<<"Average queued time:                    "<<averageQueuedTime<<endl<<endl<<endl;
*/



vector<float> mySortingVector3;

mySortingVector3.clear();

for(uint32_t c = 0 ; c < pHBQueueVector.size(); c++)
{
  mySortingVector3.push_back((pHBQueueVector.at(c) ).queuedTime);
}

StatCollector::ShellSort(mySortingVector3);

float queuedDelayPercentile = StatCollector::Get50THPercentile(mySortingVector3);

myfile2<<"Queueing Delay 50th percentile:         "<<queuedDelayPercentile<<endl;



// Average Queue Length

float avg = queueVectorAVG.at(j)/ (Simulator::Now()).GetSeconds();
myfile2<<"Average Queue Length          :         "<<avg<<endl;




if(m_summaryOnly == false)
{


       myfile2<<setw(21)<<"Sequence Numbers"<<setw(21)<<"Enqueue Time"<<setw(21)<<"Dequeue Time"<<setw(21)<<"Queued Time"<<setw(21)<<"Packet drop"<<setw(21)<<"Current Queue Size"<<setw(21)<<"Packet Size"<<endl<<endl;

   for (uint32_t k = 0; k< pHBQueueVector.size(); k++)
   {
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).sequenceNumber;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).enqueueTime;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).dequeueTime;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).queuedTime;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).drop;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).currentQueueSize;
    myfile2<<setw(21)<<(pHBQueueVector.at(k) ).packetSize<<endl;
   }
    myfile2<<endl<<endl<<endl;


}


myfile2<<"------------------------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;



  }

myfile2<<"******************************************************************************************************************************************************"<<endl<<endl;
myfile2<<endl<<endl<<endl<<endl<<endl<<endl;


 }


myfile2.close();


}



void StatCollector::ShellSort(vector <float> &num)
{
       float i, temp, flag = 1, numLength = num.size( );
     float d = numLength;
     while( flag || (d > 1))      // boolean flag (true when not equal to 0)
     {
          flag = 0;           // reset flag to 0 to check for future swaps
          d = (d+1) / 2;
          for (i = 0; i < (numLength - d); i++)
        {
               if (num[i + d] > num[i])
              {
                      temp = num[i + d];      // swap positions i+d and i
                      num[i + d] = num[i];
                      num[i] = temp;
                      flag = 1;                  // tells swap has occurred
              }
         }
     }
     return;
}




float StatCollector::Get50THPercentile(vector <float> &num)
{

int vectorSize;
float percentile;

vectorSize = num.size();

if(vectorSize == 0)
{
 return 0;
}

if(vectorSize % 2 == 0)
{
percentile = num.at( ( (vectorSize/2) +1 )-1);
}

else
{
percentile = num.at( ( ( (vectorSize-1) /2) + 1)-1 );
}


return percentile;

}




} // namespace ns3

