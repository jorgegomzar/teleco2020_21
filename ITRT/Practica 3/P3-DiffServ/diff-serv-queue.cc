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

#include "ns3/log.h"
#include "ns3/enum.h"
#include "ns3/uinteger.h"


#include "ns3/diff-serv-queue.h"
#include "ipv4-header.h"
#include "ns3/ppp-header.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"





NS_LOG_COMPONENT_DEFINE ("DiffServQueue");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (DiffServQueue);

TypeId DiffServQueue::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DiffServQueue")
    .SetParent<Queue> ()
    .AddConstructor<DiffServQueue> ()
    .AddTraceSource ("DropNonConformantAFBE", "Drop of AF, BE non-conformant packets",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropNonConformantAFBE))


	.AddTraceSource ("DropNonConformantEF", "Drop of EF non-conformant packets",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropNonConformantEF))


	.AddTraceSource ("AQMDropAF1", "Drop of AF1 queue (AQM)",
			MakeTraceSourceAccessor (&DiffServQueue::m_AQMDropAF1))
	.AddTraceSource ("AQMDropAF2", "Drop of AF2 queue (AQM)",
			MakeTraceSourceAccessor (&DiffServQueue::m_AQMDropAF2))
	.AddTraceSource ("AQMDropAF3", "Drop of AF3 queue (AQM)",
			MakeTraceSourceAccessor (&DiffServQueue::m_AQMDropAF3))
	.AddTraceSource ("AQMDropAF14", "Drop of AF4 queue (AQM)",
			MakeTraceSourceAccessor (&DiffServQueue::m_AQMDropAF4))


	.AddTraceSource ("DropTailAF1", "Drop of AF1 queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailAF1))
	.AddTraceSource ("DropTailAF2", "Drop of AF2 queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailAF2))
	.AddTraceSource ("DropTailAF3", "Drop of AF3 queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailAF3))
	.AddTraceSource ("DropTailAF4", "Drop of AF4 queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailAF4))


	.AddTraceSource ("DropTailEF", "Drop of EF queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailEF))

	.AddTraceSource ("DropTailBE", "Drop of be queue (Queue Full)",
			MakeTraceSourceAccessor (&DiffServQueue::m_DropTailBE))
    ; //Traces added by juaase

  return tid;
}

DiffServQueue::DiffServQueue ()

{

//m_queueId = StatCollector::AllocateQueueId();

m_queueMode = "Core";


//MaxPackets

   m_AF1_maxPackets = 100;
   m_AF2_maxPackets = 100;
   m_AF3_maxPackets = 100;
   m_AF4_maxPackets = 100;
   m_EF_maxPackets = 100;
   m_BestEffort_maxPackets = 100;

//WRR Weights

   m_AF1_weightTemp = 0 ;
   m_AF2_weightTemp = 0;
   m_AF3_weightTemp = 0 ;
   m_AF4_weightTemp = 0 ;
   m_BestEffort_weightTemp = 0 ;

   m_AF1_weight = 1 ;
   m_AF2_weight = 1;
   m_AF3_weight = 1 ;
   m_AF4_weight = 1 ;
   m_BestEffort_weight = 1 ;

m_AF1_AQMId = "DropTail";
m_AF2_AQMId = "DropTail";
m_AF3_AQMId = "DropTail";
m_AF4_AQMId = "DropTail";


 m_EF_lastPacketArrivalTime = 0;
 m_EF_committedBucketSize = 5000 ;
 m_EF_cBS = 5000;
 m_EF_cIR = 10000000;

  NS_LOG_FUNCTION_NOARGS ();
}

DiffServQueue::~DiffServQueue ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

  bool DiffServQueue::m_enableMetering = false;
  bool DiffServQueue::m_enableClassification = false ;
vector< Ptr<DiffServFlow> > DiffServQueue::m_flowVector;
vector< Ptr<DiffServMeter> > DiffServQueue::m_meterVector;


bool
DiffServQueue::DoEnqueue (Ptr<Packet> p)
{
NS_LOG_INFO ("DiffServQueue_Enqueue "<<" QueueId: "<<m_queueId<<" Queue Mode: "<<m_queueMode);
NS_LOG_INFO(*p);

//Classfiy and Condition packet

if( (m_queueMode == "Edge") && (m_enableClassification == true) )
{
 ClassifyAndCondition(p);


// Non conformant packets dropped

if (m_drop == true)
    {

      NS_LOG_INFO("Dropper:");
      NS_LOG_INFO("Packet Dropped");
      NS_LOG_INFO("");
      NS_LOG_INFO("");
      Drop (p);
      m_DropNonConformantAFBE(p); //added by juaase
      return false;
    }

}
  return BA_Classifier(p);
}

Ptr<Packet>
DiffServQueue::DoDequeue (void)
{
NS_LOG_LOGIC ("DiffServQueue_Dequeue");

loop:

if(!m_EFqueue.empty())
    {
     return EF_DoDequeue ();
    }


if(!m_AF1queue.empty())
    {
       if( m_AF1_weightTemp > 0)
         {
           m_AF1_weightTemp--;
           return AF1_DoDequeue ();
         }
     }


if(!m_AF2queue.empty())
    {
       if( m_AF2_weightTemp > 0)
         {
           m_AF2_weightTemp--;
           return AF2_DoDequeue ();
         }
     }


if(!m_AF3queue.empty())
    {
       if( m_AF3_weightTemp > 0)
         {
           m_AF3_weightTemp--;
           return AF3_DoDequeue ();
         }
     }


if(!m_AF4queue.empty())
    {
       if( m_AF4_weightTemp > 0)
         {
           m_AF4_weightTemp--;
           return AF4_DoDequeue ();
         }
     }

if(!m_BestEffortqueue.empty())
    {
       if( m_BestEffort_weightTemp > 0)
         {
           m_BestEffort_weightTemp--;
           return BestEffort_DoDequeue ();
         }
     }


  if(!m_AF4queue.empty() || !m_AF3queue.empty() || !m_AF2queue.empty() || !m_AF1queue.empty() || !m_BestEffortqueue.empty())
 { NS_LOG_LOGIC ("RESET WEIGHTS");
   m_AF1_weightTemp = m_AF1_weight ;
   m_AF2_weightTemp = m_AF2_weight ;
   m_AF3_weightTemp = m_AF3_weight ;
   m_AF4_weightTemp =  m_AF4_weight ;
   m_BestEffort_weightTemp = m_BestEffort_weight ;
   goto loop;
 }

return 0;


}

Ptr<const Packet>
DiffServQueue::DoPeek (void) const
{
  //NS_LOG_FUNCTION (this);

  if (m_AF1queue.empty())
    {
      NS_LOG_LOGIC ("Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_AF1queue.front ();

  NS_LOG_LOGIC ("Number packets " << m_AF1queue.size ());

  return p;
}



//BA_Classifier

bool DiffServQueue:: BA_Classifier(Ptr<Packet> p)
{
NS_LOG_INFO ("BA Classifier :");

//Getting the ipv4header
Ipv4Header ipv4Header;
PppHeader pppHeader;

Ptr<Packet> q = p->Copy ();
q->RemoveHeader (pppHeader);
q->RemoveHeader (ipv4Header);

//Getting DS field from ipv4header
  m_DS = ipv4Header.GetTos();


//filtering packets

if ((m_DS == 40 ) || (m_DS == 48) || (m_DS== 56)  )
{
 return AF1_DoEnqueue (p);
}

if ((m_DS == 72 ) || (m_DS == 80) || (m_DS== 88)  )
{
 return AF2_DoEnqueue (p);
}

if ((m_DS == 104 ) || (m_DS == 112) || (m_DS== 120)  )
{
 return AF3_DoEnqueue (p);
}

if ((m_DS == 136 ) || (m_DS == 144) || (m_DS== 152)  )
{
  return AF4_DoEnqueue (p);
}

if (m_DS == 184)
{
   return EF_DoEnqueue (p);
}

if (m_DS == 0)
{
   return BestEffort_DoEnqueue (p);
}

   return BestEffort_DoEnqueue (p);

}

//AF1 Enqueue

bool DiffServQueue:: AF1_DoEnqueue (Ptr<Packet> p)

{
NS_LOG_INFO ("AF1_enqueue");

//NS_LOG_FUNCTION (this << p);


//If AQM is enabled for this queue

if(m_AF1_AQMId != "DropTail")
{
 m_aqmOutput = m_AF1_AQMPtr->DoAQM(m_AF1queue.size (), m_DS);

  if(m_aqmOutput == 0)
   {
    NS_LOG_INFO ("Packet Dropped by AQM :" << m_AF1_AQMId);
    NS_LOG_INFO("");
    Drop (p);
    m_AQMDropAF1(p); //juaase
    //StatCollector::Enqueue(m_queueId,0, p , 1 , m_AF1queue.size () );
    return false;
    }


    else
    {
     NS_LOG_INFO ("Packet to be Enqueue by AQM");

      if(m_AF1queue.size () >= m_AF1_maxPackets)
      {
       NS_LOG_INFO ("AF1 Queue full--dropping packet");
      Drop (p);
      m_DropTailAF1(p); //juaase
      //StatCollector::Enqueue(m_queueId,0, p , 1 , m_AF1queue.size () );
      return false;
      }

       NS_LOG_INFO("AF1 Packet Enqueued");
       NS_LOG_INFO("");
       //StatCollector::Enqueue(m_queueId,0, p , 0 , m_AF1queue.size () );
       m_AF1queue.push(p);
       return true;

    }

}//AQM


// Drop-tail


  if (m_AF1queue.size () >= m_AF1_maxPackets)
    {
      NS_LOG_LOGIC ("AF1 Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailAF1(p); //juaase
      //StatCollector::Enqueue(m_queueId,0, p , 1 , m_AF1queue.size () );
      return false;
    }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,0, p , 0 , m_AF1queue.size () );
   m_AF1queue.push(p);

   NS_LOG_LOGIC ("Number packets " << m_AF1queue.size ());
   return true;
}

//AF2 Enqueue

bool DiffServQueue:: AF2_DoEnqueue (Ptr<Packet> p)

{
NS_LOG_INFO ("AF2_enqueue");

//NS_LOG_FUNCTION (this << p);


//If AQM is enabled for this queue

if(m_AF2_AQMId != "DropTail")
{
 m_aqmOutput = m_AF2_AQMPtr->DoAQM(m_AF2queue.size (), m_DS);

  if(m_aqmOutput == 0)
   {
    NS_LOG_INFO ("Packet Dropped by AQM :" << m_AF2_AQMId);
    NS_LOG_INFO("");
    Drop (p);
    m_AQMDropAF2(p); //juaase
    //StatCollector::Enqueue(m_queueId,1, p , 1 , m_AF2queue.size () );
    return false;
    }


    else
    {
     NS_LOG_INFO ("Packet to be Enqueue by AQM");

      if(m_AF2queue.size () >= m_AF2_maxPackets)
      {
       NS_LOG_INFO ("AF2 Queue full--dropping packet");
      Drop (p);
      m_DropTailAF2(p); //juaase
      //StatCollector::Enqueue(m_queueId,1, p , 1 , m_AF2queue.size () );
      return false;
      }

       NS_LOG_INFO("AF2 Packet Enqueued");
       NS_LOG_INFO("");
       //StatCollector::Enqueue(m_queueId,1, p , 0 , m_AF2queue.size () );
       m_AF2queue.push(p);
       return true;

    }

}//AQM


// Drop-tail


  if (m_AF2queue.size () >= m_AF2_maxPackets)
    {
      NS_LOG_LOGIC ("AF2 Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailAF2(p); //juaase
      //StatCollector::Enqueue(m_queueId,1, p , 1 , m_AF2queue.size () );
      return false;
    }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,1, p , 0 , m_AF2queue.size () );
   m_AF2queue.push(p);

   NS_LOG_LOGIC ("Number packets " << m_AF2queue.size ());
   return true;
}


//AF3 Enqueue

bool DiffServQueue:: AF3_DoEnqueue (Ptr<Packet> p)

{
NS_LOG_INFO ("AF3_enqueue");

//NS_LOG_FUNCTION (this << p);


//If AQM is enabled for this queue

if(m_AF3_AQMId != "DropTail")
{
 m_aqmOutput = m_AF3_AQMPtr->DoAQM(m_AF3queue.size (), m_DS);

  if(m_aqmOutput == 0)
   {
    NS_LOG_INFO ("Packet Dropped by AQM :" << m_AF3_AQMId);
    NS_LOG_INFO("");
    Drop (p);
    m_AQMDropAF3(p); //juaase
    //StatCollector::Enqueue(m_queueId,2, p , 1 , m_AF3queue.size () );
    return false;
    }


    else
    {
     NS_LOG_INFO ("Packet to be Enqueue by AQM");

      if(m_AF3queue.size () >= m_AF3_maxPackets)
      {
       NS_LOG_INFO ("AF3 Queue full--dropping packet");
      Drop (p);
      m_DropTailAF3(p); //juaase
      //StatCollector::Enqueue(m_queueId,2, p , 1 , m_AF3queue.size () );
      return false;
      }

       NS_LOG_INFO("AF3 Packet Enqueued");
       NS_LOG_INFO("");
       //StatCollector::Enqueue(m_queueId,2, p , 0 , m_AF3queue.size () );
       m_AF3queue.push(p);
       return true;

    }

}//AQM


// Drop-tail


  if (m_AF3queue.size () >= m_AF3_maxPackets)
    {
      NS_LOG_LOGIC ("AF3 Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailAF3(p); //juaase
      //StatCollector::Enqueue(m_queueId,2, p , 1 , m_AF3queue.size () );
      return false;
    }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,2, p , 0 , m_AF3queue.size () );
   m_AF3queue.push(p);

   NS_LOG_LOGIC ("Number packets " << m_AF3queue.size ());
   return true;
}


//AF4 Enqueue

bool DiffServQueue::AF4_DoEnqueue (Ptr<Packet> p)

{
NS_LOG_INFO ("AF4_enqueue");

//NS_LOG_FUNCTION (this << p);


//If AQM is enabled for this queue

if(m_AF4_AQMId != "DropTail")
{
 m_aqmOutput = m_AF4_AQMPtr->DoAQM(m_AF4queue.size (), m_DS);

  if(m_aqmOutput == 0)
   {
    NS_LOG_INFO ("Packet Dropped by AQM :" << m_AF4_AQMId);
    NS_LOG_INFO("");
    Drop (p);
    m_AQMDropAF4(p); //juaase
    //StatCollector::Enqueue(m_queueId,3, p , 1 , m_AF4queue.size () );
    return false;
    }


    else
    {
     NS_LOG_INFO ("Packet to be Enqueue by AQM");

      if(m_AF4queue.size () >= m_AF4_maxPackets)
      {
       NS_LOG_INFO ("AF4 Queue full--dropping packet");
      Drop (p);
      m_DropTailAF4(p); //juaase

      //StatCollector::Enqueue(m_queueId,3, p , 1 , m_AF4queue.size () );
      return false;
      }

       NS_LOG_INFO("AF4 Packet Enqueued");
       NS_LOG_INFO("");
       //StatCollector::Enqueue(m_queueId,3, p , 0 , m_AF4queue.size () );
       m_AF4queue.push(p);
       return true;

    }

}//AQM


// Drop-tail


  if (m_AF4queue.size () >= m_AF4_maxPackets)
    {
      NS_LOG_LOGIC ("AF4 Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailAF4(p); //juaase

      //StatCollector::Enqueue(m_queueId,3, p , 1 , m_AF4queue.size () );
      return false;
    }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,3, p , 0 , m_AF4queue.size () );
   m_AF4queue.push(p);

   NS_LOG_LOGIC ("Number packets " << m_AF4queue.size ());
   return true;
}


//EF Enqueue

bool DiffServQueue:: EF_DoEnqueue (Ptr<Packet> p)

{
NS_LOG_INFO ("EF_enqueue");

//NS_LOG_FUNCTION (this << p);

  if (m_EFqueue.size () >= m_EF_maxPackets)
    {
      NS_LOG_LOGIC ("EF Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailEF(p);
      //StatCollector::Enqueue(m_queueId,4, p , 1 , m_EFqueue.size () );
      return false;
    }


   int EF = EFRateLimiterTokenBucket(p);
   if(EF==conformanceLevel_2)
   {
     efDropped++;
     NS_LOG_INFO ("Packet exceeds EF profile-- droppping pkt"<<", Total dropped: "<<efDropped);
     NS_LOG_INFO("");
     Drop (p);
     m_DropNonConformantEF(p); //juaase
     //StatCollector::Enqueue(m_queueId,4, p , 1 , m_EFqueue.size () );
     return false;
   }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,4, p , 0 , m_EFqueue.size () );
   m_EFqueue.push(p);

  NS_LOG_LOGIC ("Number packets " << m_EFqueue.size ());


  return true;
}


//BE Enqueue

bool DiffServQueue::BestEffort_DoEnqueue (Ptr<Packet> p)

{
 NS_LOG_INFO ("BestEffort_enqueue");

//NS_LOG_FUNCTION (this << p);

  if (m_BestEffortqueue.size () >= m_BestEffort_maxPackets)
    {
      NS_LOG_LOGIC ("BE Queue full (at max packets) -- droppping pkt");
      Drop (p);
      m_DropTailBE(p); //juaase
      //StatCollector::Enqueue(m_queueId,5, p , 1 , m_BestEffortqueue.size () );
      return false;
    }

   NS_LOG_INFO("Packet Enqueued");
   NS_LOG_INFO("");
   //StatCollector::Enqueue(m_queueId,5, p , 0 , m_BestEffortqueue.size () );
   m_BestEffortqueue.push(p);

  NS_LOG_LOGIC ("Number packets " << m_BestEffortqueue.size ());


  return true;
}


//DeQueue Functions
//
//


//AF1 Dequeue

Ptr<Packet> DiffServQueue:: AF1_DoDequeue (void)
{
NS_LOG_LOGIC ("AF1_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_AF1queue.empty())
    {
      NS_LOG_LOGIC ("AF1 Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_AF1queue.front ();
  m_AF1queue.pop ();
  //StatCollector::Dequeue(m_queueId,0, p,m_AF1queue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_AF1queue.size ());


  return p;
}


//AF2 Dequeue

Ptr<Packet> DiffServQueue:: AF2_DoDequeue (void)
{
NS_LOG_LOGIC ("AF2_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_AF2queue.empty())
    {
      NS_LOG_LOGIC ("AF2 Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_AF2queue.front ();
  m_AF2queue.pop ();
  //StatCollector::Dequeue(m_queueId,1, p,m_AF2queue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_AF2queue.size ());


  return p;
}



//AF3 Dequeue

Ptr<Packet> DiffServQueue:: AF3_DoDequeue (void)
{
NS_LOG_LOGIC ("AF3_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_AF3queue.empty())
    {
      NS_LOG_LOGIC ("AF3 Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_AF3queue.front ();
  m_AF3queue.pop ();
  //StatCollector::Dequeue(m_queueId,2, p,m_AF3queue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_AF3queue.size ());


  return p;
}



//AF4 Dequeue

Ptr<Packet> DiffServQueue:: AF4_DoDequeue (void)
{
 NS_LOG_LOGIC ("AF4_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_AF4queue.empty())
    {
      NS_LOG_LOGIC ("AF4 Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_AF4queue.front ();
  m_AF4queue.pop ();
  //StatCollector::Dequeue(m_queueId,3, p,m_AF4queue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_AF4queue.size ());


  return p;
}


//EF Dequeue

Ptr<Packet> DiffServQueue:: EF_DoDequeue (void)
{
NS_LOG_LOGIC ("EF_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_EFqueue.empty())
    {
      NS_LOG_LOGIC ("EF Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_EFqueue.front ();
  m_EFqueue.pop ();
  //StatCollector::Dequeue(m_queueId,4, p,m_EFqueue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_EFqueue.size ());


  return p;
}



//BE Dequeue

Ptr<Packet> DiffServQueue:: BestEffort_DoDequeue (void)
{
 NS_LOG_LOGIC ("BestEffort_dequeue");

 //NS_LOG_FUNCTION (this);

  if (m_BestEffortqueue.empty())
    {
      NS_LOG_LOGIC ("BE Queue empty");
      return 0;
    }

  Ptr<Packet> p = m_BestEffortqueue.front ();
  m_BestEffortqueue.pop ();
  //StatCollector::Dequeue(m_queueId,5, p,m_BestEffortqueue.size ());

  NS_LOG_LOGIC ("Popped " << p);

  NS_LOG_LOGIC ("Number packets " << m_BestEffortqueue.size ());


  return p;
}


// Set WRR Weights


void DiffServQueue::SetWRRWeights(int AF1, int AF2, int AF3 , int AF4 , int BE)
{
m_AF1_weight = AF1 ;
m_AF2_weight = AF2 ;
m_AF3_weight = AF3 ;
m_AF4_weight = AF4 ;
m_BestEffort_weight = BE ;
}


//Set Queue size

void DiffServQueue::SetQueueSize(int AF1, int AF2, int AF3 , int AF4 , int EF, int BE)
{
m_AF1_maxPackets = AF1;
m_AF2_maxPackets = AF2;
m_AF3_maxPackets = AF3;
m_AF4_maxPackets = AF4;
m_EF_maxPackets = EF;
m_BestEffort_maxPackets = BE;
}


//Set EF Profile

void DiffServQueue::SetEFProfile(int cir, int cbs)
{
m_EF_cIR = cir;
m_EF_cBS = cbs;
m_EF_committedBucketSize = m_EF_cBS;
}


//Set AQM
void DiffServQueue::SetDiffServAQM(vector< Ptr<DiffServAQM> > aqmVector, string AF1_AQMId,string AF2_AQMId,string AF3_AQMId,string AF4_AQMId)
{

if(aqmVector.empty() )
{
 NS_LOG_INFO("AQM Vector does not contain any aqm -- 'droptail' buffer management will be performed on each queue");
 return;
}


m_aqmVector = aqmVector;

NS_LOG_INFO ("DiffServQueue_AQM "<<"QueueId: "<<m_queueId);

string aqmId_AQMVector;

for (uint32_t k = 0; k < m_aqmVector.size();k++)
 {

  aqmId_AQMVector = ( m_aqmVector.at(k) )->m_aqmId;

  if ( AF1_AQMId == aqmId_AQMVector)
  {
    m_AF1_AQMId = AF1_AQMId;
    m_AF1_AQMPtr = m_aqmVector.at(k);
   NS_LOG_INFO("AF1 AQM identified:" << m_AF1_AQMId );
  }


 if ( AF2_AQMId == aqmId_AQMVector)
  {
    m_AF2_AQMId = AF2_AQMId;
    m_AF2_AQMPtr = m_aqmVector.at(k);
   NS_LOG_INFO("AF2 AQM identified:" << m_AF2_AQMId );
  }



  if ( AF3_AQMId == aqmId_AQMVector)
  {
    m_AF3_AQMId = AF3_AQMId;
    m_AF3_AQMPtr = m_aqmVector.at(k);
   NS_LOG_INFO("AF3 AQM identified:" << m_AF3_AQMId );
  }


 if ( AF4_AQMId == aqmId_AQMVector)
  {
    m_AF4_AQMId = AF4_AQMId;
    m_AF4_AQMPtr = m_aqmVector.at(k);
   NS_LOG_INFO("AF4 AQM identified:" << m_AF4_AQMId );
  }


 }//end loop





}


//EF Rate Limiter Token Bucket

bool DiffServQueue::EFRateLimiterTokenBucket(Ptr<Packet> p)
{

NS_LOG_INFO("EFRateLimiterTokenBucket :");


NS_LOG_INFO("lastPacketArrivalTime: "<<m_EF_lastPacketArrivalTime);
NS_LOG_INFO("committedBucketSize : "<<m_EF_committedBucketSize);
NS_LOG_INFO("cBS: "<<m_EF_cBS);
NS_LOG_INFO("cIR: "<<m_EF_cIR);



// Calculating bytes to add to bucket

m_EF_currentPacketArrivalTime = (Simulator::Now()).GetSeconds();

NS_LOG_INFO("currentPacketArrivalTime: "<<m_EF_currentPacketArrivalTime);

NS_LOG_INFO("Time Difference: "<<m_EF_currentPacketArrivalTime - m_EF_lastPacketArrivalTime);

m_EF_bytesToAdd = (m_EF_currentPacketArrivalTime - m_EF_lastPacketArrivalTime) * (m_EF_cIR/8);

NS_LOG_INFO("bytesToAdd: "<<m_EF_bytesToAdd);

m_EF_lastPacketArrivalTime = m_EF_currentPacketArrivalTime;




//Adding bytes to bucket

if (m_EF_committedBucketSize + m_EF_bytesToAdd >= m_EF_cBS)
    {
       m_EF_committedBucketSize = m_EF_cBS;
    }

else {
       m_EF_committedBucketSize = m_EF_committedBucketSize + m_EF_bytesToAdd;
     }

NS_LOG_INFO("committedBucketSizeAfterAdding: "<<m_EF_committedBucketSize);


//Getting the size of the packet in bytes
PppHeader pppHeader;

Ptr<Packet> q = p->Copy ();

q->RemoveHeader (pppHeader);

 m_EF_packetSize = q->GetSize();

NS_LOG_INFO("packetSize: "<<m_EF_packetSize);


//Testing conformance

if ( m_EF_committedBucketSize - m_EF_packetSize >= 0)
    {
      m_EF_committedBucketSize = m_EF_committedBucketSize - m_EF_packetSize;



     NS_LOG_INFO("Packet conformant: YES");

     NS_LOG_INFO("committedBucketSizeAfterRemoving: "<<m_EF_committedBucketSize);

     return conformanceLevel_1;
    }

else
    {
       NS_LOG_INFO("Packet conformant: NO");

       NS_LOG_INFO("NO tokens removed");


       return 0;
    }


}



//Traffic conditioning functions


void DiffServQueue:: Marker(Ptr<Packet> p, int DS)
 {
 NS_LOG_INFO("Marker:");

 NS_LOG_INFO("DS field set to :"<<DS);


//Creating containers for packet headers
Ipv4Header ipv4HeaderNew;
PppHeader pppHeaderNew;
Ipv4Header ipv4HeaderOld;
PppHeader pppHeaderOld;

//Getting the headers from a copy of packet
Ptr<Packet> q = p->Copy ();
q->RemoveHeader (pppHeaderNew);
q->RemoveHeader (ipv4HeaderNew);

//Marking the Tos field
ipv4HeaderNew.SetTos(DS);

//Removing headers from the real packet
p->RemoveHeader (pppHeaderOld);
p->RemoveHeader (ipv4HeaderOld);

//Attaching new marked header
p->AddHeader (ipv4HeaderNew);
p->AddHeader (pppHeaderNew);

return ;
}

void DiffServQueue:: ClassifyAndCondition(Ptr<Packet> p)
{

 NS_LOG_INFO("ClassificationAndConditionining:");

 NS_LOG_INFO("STEP 1: MF Classifier:");

//Getting the ipv4 and transport headers from packet  and Getting required information

Ipv4Header ipv4Header;
PppHeader pppHeader;
UdpHeader udpHeader;
TcpHeader tcpHeader;


NS_LOG_INFO("STEP 1a: About to copy:");

Ptr<Packet> q = p->Copy ();
NS_LOG_INFO("STEP 1a: Copied");


NS_LOG_INFO("STEP 1b: About to remove:");

q->RemoveHeader (pppHeader);
q->RemoveHeader (ipv4Header);

NS_LOG_INFO("STEP 1b: Removed");


Ipv4Address scrAddressPacket = ipv4Header.GetSource();
Ipv4Address destAddressPacket = ipv4Header.GetDestination();
int protocolNumber = ipv4Header.GetProtocol();

NS_LOG_INFO("STEP 1c: Getters OK");


int scrPortPacket;
int destPortPacket;

if (protocolNumber == 17)
{
 NS_LOG_INFO("STEP 1c: Protocol 17 (UDP) OK");
 q->RemoveHeader (udpHeader);
 scrPortPacket = udpHeader.GetSourcePort();
 destPortPacket = udpHeader.GetDestinationPort();
}

if (protocolNumber == 6)
{
	NS_LOG_INFO("STEP 1c: Protocol 6 OK");
 q->RemoveHeader (tcpHeader);
 scrPortPacket = tcpHeader.GetSourcePort();
 destPortPacket = tcpHeader.GetDestinationPort();
}

NS_LOG_INFO("STEP 1d: Ok...");


//filtering packets

m_flow = 0;
m_drop = false;

for (uint32_t i = 0; i < m_flowVector.size();i++)
{

Ipv4Address scrAddressFlow = (m_flowVector.at(i))->GetSourceAddress();
Ipv4Address destAddressFlow = (m_flowVector.at(i))->GetDestinationAddress();
int scrPortFlow = (m_flowVector.at(i))->GetSourcePort();
int destPortFlow = (m_flowVector.at(i))->GetDestinationPort();



if( scrAddressFlow.Get() ==0)
{
 scrAddressFlow = scrAddressPacket;
}

if( destAddressFlow.Get() ==0)
{
 destAddressFlow = destAddressPacket;
}

if( scrPortFlow ==0)
{
 scrPortFlow = scrPortPacket;
}

if( destPortFlow ==0)
{
 destPortFlow = destPortPacket;
}



if ((scrAddressPacket == scrAddressFlow) && (destAddressPacket == destAddressFlow) && (scrPortPacket == scrPortFlow) && (destPortPacket == destPortFlow))
  {
  m_flow =  m_flowVector.at(i);

  NS_LOG_INFO("flowId: "<<(m_flow->GetFlowId()));
  NS_LOG_INFO("slaId: "<<(m_flow->GetSla())->GetSlaId());
  break;
  }

}//end loop



//If flow is not identified

if(m_flow == 0)
{
 NS_LOG_INFO("No classification found--packet does not belong to a SLA");
 NS_LOG_INFO("Forwarding packet to BA Classifier ");
 return;
}




NS_LOG_INFO("STEP 2: Meter:");

//If metering is enabled for DiffServQueues

if(m_enableMetering == true)
{

//If metering is enabled for this SLA

if( ( m_flow->GetSla() )->GetSlaMeter() == true)
{

//Getting meterID to determine which Meter to use

string meterID_SLA;
string meterID_MeterVector;
m_meterIdentified = false;

meterID_SLA = ( (m_flow->GetSla() )->m_mSpec).meterID;

for (uint32_t j = 0; j < m_meterVector.size();j++)
{

meterID_MeterVector = ( m_meterVector.at(j) )->m_meterID;

if ( meterID_SLA == meterID_MeterVector)
  {
    NS_LOG_INFO("Meter identified: " << meterID_MeterVector );
    m_meter = m_meterVector.at(j);
    m_meterIdentified = true;
    break;
  }

}//end loop


//If meter identified --Calling meter object to meter packet

 if ( m_meterIdentified == true)
 {
 NS_LOG_INFO("Metering Packet using: "<<meterID_MeterVector);
 m_conformance =  m_meter->MeterPacket(p, m_flow->GetSla() );
 NS_LOG_INFO("Conformance Level: "<< m_conformance);
 }

else
 {
  NS_LOG_INFO("Meter not found for SLA--setting packet DS field to inital codepoint");
  m_conformance = conformanceLevel_1;
  NS_LOG_INFO("Conformance Level: "<< m_conformance);
 }


}//end SLA meter state if


else
{
 NS_LOG_INFO("This SLA requires no metering--setting packet DS field to inital codepoint");

 m_conformance = conformanceLevel_1;
 NS_LOG_INFO("Conformance Level: "<< m_conformance);
}

}// end metering enable if


else
{
 NS_LOG_INFO("Metering Disabled--setting packet DS field to inital codepoint");

 m_conformance = conformanceLevel_1;
 NS_LOG_INFO("Conformance Level: "<< m_conformance);
}




 NS_LOG_INFO("STEP 3: Enforcer:");

//Taking appropiate action as specified in the SLA - 3 conformance levels


//Conformance Level 1 -- marking packet to inital codepoint

if ( m_conformance == conformanceLevel_1)
{
 Marker(p, ( (m_flow->GetSla() )->m_cSpec).initialCodePoint );
}


//Conformance Level 2 -- marking packet to downgraded codepoint or dropping

if (m_conformance == conformanceLevel_2)
 {
  if ( ( (m_flow->GetSla() )->m_cSpec).nonConformantActionI == 256)
     {
       m_drop = true;
       return;
     }

  else
     {
       Marker(p, ( (m_flow->GetSla() )->m_cSpec).nonConformantActionI );
     }
 }

//Conformance Level 3 -- marking packet to downgraded codepoint or dropping

if (m_conformance == conformanceLevel_3)
 {
  if ( ( (m_flow->GetSla() )->m_cSpec).nonConformantActionII == 256)
     {
       m_drop = true;
       return;
     }

  else
     {
       Marker(p, ( (m_flow->GetSla() )->m_cSpec).nonConformantActionII );
     }
 }





}// ClassifyAndCondition end



void DiffServQueue::SetDiffServFlows( vector< Ptr<DiffServFlow> > flowVector)
{

if(flowVector.empty())
  {
   NS_LOG_INFO("Flow Vector does not contain any flows -- traffic classification and conditioning will not be performed--Core Queue");
   return;
  }

m_enableClassification = true;

//Error checking for duplicate flows

vector< Ptr<DiffServFlow> > flowVectorCopy = flowVector;
int counter;


for (uint32_t i = 0; i < flowVector.size();i++)
{

counter = 0;

Ipv4Address scrAddressFlow = (flowVector.at(i))->GetSourceAddress();
Ipv4Address destAddressFlow = (flowVector.at(i))->GetDestinationAddress();
int scrPortFlow = (flowVector.at(i))->GetSourcePort();
int destPortFlow = (flowVector.at(i))->GetDestinationPort();


for (uint32_t j = 0; j < flowVectorCopy.size();j++)
 {

Ipv4Address scrAddressFlowCopy = (flowVectorCopy.at(j))->GetSourceAddress();
Ipv4Address destAddressFlowCopy = (flowVectorCopy.at(j))->GetDestinationAddress();
int scrPortFlowCopy = (flowVectorCopy.at(j))->GetSourcePort();
int destPortFlowCopy = (flowVectorCopy.at(j))->GetDestinationPort();

if ((scrAddressFlow == scrAddressFlowCopy) && (destAddressFlow == destAddressFlowCopy) && (scrPortFlow == scrPortFlowCopy) && (destPortFlow == destPortFlowCopy))
  {
    counter++;

  }

NS_ASSERT( counter <= 1);


 }

}

m_flowVector = flowVector;

}

void DiffServQueue :: SetDiffServMeters ( vector< Ptr<DiffServMeter> > meterVector)
{
  if(meterVector.empty())
  {
    NS_LOG_INFO("Meter Vector does not contain any meters -- no metering will be performed on packets");
    return;
  }
m_enableMetering = true;

m_meterVector = meterVector;

}


void DiffServQueue::SetQueueMode(string mode)
{
 m_queueMode = mode;
}




} // namespace ns3


