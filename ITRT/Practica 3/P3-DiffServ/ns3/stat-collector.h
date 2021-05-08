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
#ifndef STATCOLLECTOR_H
#define STATCOLLECTOR_H
#include "ns3/object.h"
#include "ns3/ipv4-address.h"
#include "ns3/tag.h"
#include "ns3/flow-id-tag.h"
//#include "ns3/seq-id-queue-tag.h"
#include "ns3/packet.h"
#include <vector>
#include <fstream>
#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include <iomanip>

using namespace std;


namespace ns3 {


//juaase

class SeqIdTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer buf) const;
  virtual void Deserialize (TagBuffer buf);
  virtual void Print (std::ostream &os) const;
  SeqIdTag ();
  SeqIdTag (uint32_t seqId);
  void SetSeqId (uint32_t seqId);
  uint32_t GetSeqId (void) const;
  static uint32_t AllocateSeqId (void);
private:
  uint32_t m_seqId;
};

class SeqIdQueueTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer buf) const;
  virtual void Deserialize (TagBuffer buf);
  virtual void Print (std::ostream &os) const;
  SeqIdQueueTag ();
  SeqIdQueueTag (uint32_t seqIdQueue);
  void SetSeqId (uint32_t seqIdQueue);
  uint32_t GetSeqId (void) const;
  static uint32_t AllocateSeqId (void);
private:
  uint32_t m_seqId;
};



enum{ undefined = 999};

struct PacketStatistics
{
int sequenceNumber;
float txTime;
float rxTime;
float delay;
float delayVariation;
float jitter;
bool  loss;
float packetSize;
};


struct FourTuple{

Ipv4Address scrAddress;
Ipv4Address destAddress;
int scrPort;
int destPort;
};

struct PacketStatisticsQueue
{
 int sequenceNumber;
 float enqueueTime;
 float dequeueTime;
 float queuedTime;
 bool  drop;
 int currentQueueSize;
float packetSize;
};


class StatCollector : public Object
{
public:
  static TypeId GetTypeId (void);

  StatCollector ();

  virtual ~StatCollector();

static void PrepareTx(Ptr<Packet> packet, Ipv4Address scrAddress, Ipv4Address destAddress , int scrPort, int destPort);
static void RecordRx(Ptr<Packet> packet);
static void ClassifyPacket(Ipv4Address scrAddress, Ipv4Address destAddress , int scrPort, int destPort);
static uint32_t AllocateFlowId (void);
static void SetDelayLossThreshold(float thresholdTime);
static void EnableEndToEndStatCollection(void);
static void EnableQueueStatCollection(void);

static void OutputEndToEndStats(void);
static void OutputQueueStats(void);

private:

static float m_delayLossThreshold;
static bool m_collectStats;
static bool m_collectStatsQueue;


//Tx
static vector<FourTuple>  m_flowVector;
static int m_flowId;
static int m_seqId;
static float m_txTime;
static float m_rxTime;
static float m_delay;
static float m_delayVariation;
static float m_jitter;
static bool m_reordered;
static vector <int> m_sequenceVector;

//Rx
static vector< vector<PacketStatistics> > m_statVector;






//Queues
public:

static uint32_t AllocateQueueId (void);
static void Enqueue(int queueId , int pHBQueueId, Ptr<Packet> packet, bool drop , int currentQueueSize);
static void Dequeue(int queueId , int pHBQueueId, Ptr<Packet> packet, int currentQueueSize);

static int m_queueId;
static int m_pHBQueueId;
static int m_seqIdQueue;
static int m_currentQueueSize;

static float m_enqueueTime;
static float m_dequeueTime;
static float m_queuedTime;
static vector< vector<  vector< PacketStatisticsQueue> >  > m_statVectorQueue;
static vector<  vector< int> >  m_sequenceVectorQueue;

static vector< vector< float> > averageQueueLengthVector;
static vector< vector< float> > lastEnqueueDequeueTime;



//Sorting

static void ShellSort(vector <float> &num);
static float Get50THPercentile(vector <float> &num);

static bool m_summaryOnly;
};

} // namespace ns3

#endif /* STATCOLLECTOR_H */
