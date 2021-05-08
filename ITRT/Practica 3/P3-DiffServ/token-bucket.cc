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
#include "ns3/token-bucket.h"



NS_LOG_COMPONENT_DEFINE ("TokenBucket");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TokenBucket);

TypeId TokenBucket::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TokenBucket")
    .SetParent<DiffServMeter> ()
    .AddConstructor<TokenBucket> ()

    ;

  return tid;
}

TokenBucket::TokenBucket ()
{
  m_meterID = "TokenBucket";
}

TokenBucket::~TokenBucket ()
{
  NS_LOG_FUNCTION_NOARGS ();
}


int TokenBucket :: MeterPacket(Ptr<Packet> p, Ptr<DiffServSla> SLA)
{


NS_LOG_INFO("TokenBucket Meter:");

//Getting info from SLA

   m_lastPacketArrivalTime = (SLA->m_mSpec).lastPacketArrivalTime;
   m_committedBucketSize  = (SLA->m_mSpec).committedBucketSize;
   m_cBS = (SLA->m_mSpec).cBS;
   m_cIR = (SLA->m_mSpec).cIR;

NS_LOG_INFO("slaId: "<<SLA->GetSlaId());
NS_LOG_INFO("lastPacketArrivalTime: "<<m_lastPacketArrivalTime);
NS_LOG_INFO("committedBucketSize : "<<m_committedBucketSize);
NS_LOG_INFO("cBS: "<<m_cBS);
NS_LOG_INFO("cIR: "<<m_cIR);



// Calculating bytes to add to bucket

m_currentPacketArrivalTime = (Simulator::Now()).GetSeconds();

NS_LOG_INFO("currentPacketArrivalTime: "<<m_currentPacketArrivalTime);

NS_LOG_INFO("Time Difference: "<<m_currentPacketArrivalTime - m_lastPacketArrivalTime);

m_bytesToAdd = (m_currentPacketArrivalTime - m_lastPacketArrivalTime) * (m_cIR/8);

NS_LOG_INFO("bytesToAdd: "<<m_bytesToAdd);

m_lastPacketArrivalTime = m_currentPacketArrivalTime;

(SLA->m_mSpec).lastPacketArrivalTime = m_lastPacketArrivalTime;


//Adding bytes to bucket

if (m_committedBucketSize + m_bytesToAdd >= m_cBS)
    {
       m_committedBucketSize = m_cBS;
    }

else {
       m_committedBucketSize = m_committedBucketSize + m_bytesToAdd;
     }

(SLA->m_mSpec).committedBucketSize = m_committedBucketSize;

NS_LOG_INFO("committedBucketSizeAfterAdding: "<<m_committedBucketSize);


//Getting the size of the packet in bytes
PppHeader pppHeader;

Ptr<Packet> q = p->Copy ();

q->RemoveHeader (pppHeader);

 m_packetSize = q->GetSize();

NS_LOG_INFO("packetSize: "<<m_packetSize);


//Testing conformance

if ( m_committedBucketSize - m_packetSize >= 0)
    {
      m_committedBucketSize = m_committedBucketSize - m_packetSize;

     (SLA->m_mSpec).committedBucketSize = m_committedBucketSize;

     NS_LOG_INFO("Packet conformant: YES");

     NS_LOG_INFO("committedBucketSizeAfterRemoving: "<<m_committedBucketSize);

     return conformanceLevel_1;
    }

else
    {
       NS_LOG_INFO("Packet conformant: NO");

       NS_LOG_INFO("NO tokens removed");

       return conformanceLevel_2;
    }
}



} // namespace ns3


