/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 University of Washington
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
 */

#ifndef DiffServQueue_H
#define DiffServQueue_H

#include <queue>
#include "ns3/packet.h"
#include "ns3/queue.h"

#include "stat-collector.h"
#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "diff-serv-flow.h"
#include "diff-serv-meter.h"
#include "diff-serv-aqm.h"

#include <vector>

using namespace std;

namespace ns3 {



/**
 *
 *
 * \A Queue of the Diffserv architecture
 */
class DiffServQueue : public Queue {
public:
	static TypeId GetTypeId (void);
	/**
	 * \brief DiffServQueue Constructor
	 *
	 */
	DiffServQueue ();

	virtual ~DiffServQueue();

	//Traffic conditioning functions

	void Marker(Ptr<Packet> p, int DS);
	void ClassifyAndCondition(Ptr<Packet> p);

	static void SetDiffServFlows( vector< Ptr<DiffServFlow> > flowVector);
	static void SetDiffServMeters( vector< Ptr<DiffServMeter> > meterVector);
	void SetQueueMode(string mode);

	static bool m_enableMetering;
	static bool m_enableClassification;
	static vector< Ptr<DiffServFlow> > m_flowVector;
	static vector< Ptr<DiffServMeter> > m_meterVector;

	int m_queueId;
	int m_conformance;
	bool m_drop;
	string m_queueMode;
	bool m_meterIdentified;
	int m_DS;
	Ptr<DiffServFlow> m_flow;
	Ptr<DiffServMeter> m_meter;


	//Core functionality

	bool BA_Classifier(Ptr<Packet> p);
	bool EFRateLimiterTokenBucket(Ptr<Packet> p);

	void SetDiffServAQM(vector< Ptr<DiffServAQM> > aqmVector, string AF1_AQMId,string AF2_AQMId,string AF3_AQMId,string AF4_AQMId);
	void SetWRRWeights(int AF1, int AF2, int AF3 , int AF4 , int BE);
	void SetQueueSize(int AF1, int AF2, int AF3 , int AF4 , int EF, int BE);
	void SetEFProfile(int cir, int cbs);



	// PHB Queues enqueue and dequeue
	bool AF1_DoEnqueue (Ptr<Packet> p);
	bool AF2_DoEnqueue (Ptr<Packet> p);
	bool AF3_DoEnqueue (Ptr<Packet> p);
	bool AF4_DoEnqueue (Ptr<Packet> p);
	bool EF_DoEnqueue  (Ptr<Packet> p);
	bool BestEffort_DoEnqueue (Ptr<Packet> p);

	Ptr<Packet> AF1_DoDequeue (void);
	Ptr<Packet> AF2_DoDequeue (void);
	Ptr<Packet> AF3_DoDequeue (void);
	Ptr<Packet> AF4_DoDequeue (void);
	Ptr<Packet> EF_DoDequeue (void);
	Ptr<Packet> BestEffort_DoDequeue (void);


private:
	virtual bool DoEnqueue (Ptr<Packet> p);
	virtual Ptr<Packet> DoDequeue (void);
	virtual Ptr<const Packet> DoPeek (void) const;

	std::queue<Ptr<Packet> > m_AF1queue;
	std::queue<Ptr<Packet> > m_AF2queue;
	std::queue<Ptr<Packet> > m_AF3queue;
	std::queue<Ptr<Packet> > m_AF4queue;
	std::queue<Ptr<Packet> > m_EFqueue;
	std::queue<Ptr<Packet> > m_BestEffortqueue;

	uint32_t m_AF1_maxPackets;
	uint32_t m_AF2_maxPackets;
	uint32_t m_AF3_maxPackets;
	uint32_t m_AF4_maxPackets;
	uint32_t m_EF_maxPackets;
	uint32_t m_BestEffort_maxPackets;

	uint32_t m_AF1_weight ;
	uint32_t m_AF2_weight ;
	uint32_t m_AF3_weight ;
	uint32_t m_AF4_weight ;
	uint32_t m_BestEffort_weight ;

	uint32_t m_AF1_weightTemp ;
	uint32_t m_AF2_weightTemp ;
	uint32_t m_AF3_weightTemp ;
	uint32_t m_AF4_weightTemp ;
	uint32_t m_BestEffort_weightTemp ;

	//juaase
	TracedCallback<Ptr<const Packet> > m_DropNonConformantAFBE;

	TracedCallback<Ptr<const Packet> > m_DropNonConformantEF;

	TracedCallback<Ptr<const Packet> > m_AQMDropAF1;
	TracedCallback<Ptr<const Packet> > m_AQMDropAF2;
	TracedCallback<Ptr<const Packet> > m_AQMDropAF3;
	TracedCallback<Ptr<const Packet> > m_AQMDropAF4;

	TracedCallback<Ptr<const Packet> > m_DropTailAF1;
	TracedCallback<Ptr<const Packet> > m_DropTailAF2;
	TracedCallback<Ptr<const Packet> > m_DropTailAF3;
	TracedCallback<Ptr<const Packet> > m_DropTailAF4;


	TracedCallback<Ptr<const Packet> > m_DropTailEF;
	TracedCallback<Ptr<const Packet> > m_DropTailBE;



	//AQM variables

	bool m_aqmOutput;

	vector< Ptr<DiffServAQM> > m_aqmVector;

	string m_AF1_AQMId;
	string m_AF2_AQMId;
	string m_AF3_AQMId;
	string m_AF4_AQMId;

	Ptr<DiffServAQM> m_AF1_AQMPtr;
	Ptr<DiffServAQM> m_AF2_AQMPtr;
	Ptr<DiffServAQM> m_AF3_AQMPtr;
	Ptr<DiffServAQM> m_AF4_AQMPtr;


	//EF Rate Limiter Token Bucket

	float m_EF_lastPacketArrivalTime;
	float m_EF_currentPacketArrivalTime;

	float m_EF_committedBucketSize ;
	int m_EF_cBS;

	float m_EF_bytesToAdd;
	int m_EF_cIR ;
	int m_EF_packetSize;

	int efDropped;
};

}; // namespace ns3

#endif /* DiffServQueue_H */
