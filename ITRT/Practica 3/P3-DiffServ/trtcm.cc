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
#include "ns3/trtcm.h"



NS_LOG_COMPONENT_DEFINE ("TRTCM");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TRTCM);

TypeId TRTCM::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TRTCM")
    .SetParent<DiffServMeter> ()
    .AddConstructor<TRTCM> ()

    ;

  return tid;
}

TRTCM::TRTCM ()
{
 m_meterID = "TRTCM";
}

TRTCM::~TRTCM ()
{
  NS_LOG_FUNCTION_NOARGS ();
}


int TRTCM :: MeterPacket(Ptr<Packet> p, Ptr<DiffServSla> SLA)
{


NS_LOG_INFO("trTCM Meter:");

//Getting info from SLA

   m_lastPacketArrivalTime = (SLA->m_mSpec).lastPacketArrivalTime;
   m_committedBucketSize  = (SLA->m_mSpec).committedBucketSize;
   m_peakBucketSize  = (SLA->m_mSpec).peakBucketSize;
   m_cBS = (SLA->m_mSpec).cBS;
   m_cIR = (SLA->m_mSpec).cIR;
   m_pBS = (SLA->m_mSpec).pBS;
   m_pIR = (SLA->m_mSpec).pIR;

NS_LOG_INFO("slaId: "<<SLA->GetSlaId());
NS_LOG_INFO("lastPacketArrivalTime: "<<m_lastPacketArrivalTime);
NS_LOG_INFO("committedBucketSize : "<<m_committedBucketSize);
NS_LOG_INFO("peakBucketSize : "<<m_peakBucketSize);
NS_LOG_INFO("cBS: "<<m_cBS);
NS_LOG_INFO("pBS: "<<m_pBS);
NS_LOG_INFO("cIR: "<<m_cIR);
NS_LOG_INFO("pIR: "<<m_pIR);




// Calculating bytes to add to Committed Bucket

m_currentPacketArrivalTime = (Simulator::Now()).GetSeconds();

NS_LOG_INFO("currentPacketArrivalTime: "<<m_currentPacketArrivalTime);

NS_LOG_INFO("Time Difference: "<<m_currentPacketArrivalTime - m_lastPacketArrivalTime);

m_bytesToAdd = (m_currentPacketArrivalTime - m_lastPacketArrivalTime) * (m_cIR/8);

NS_LOG_INFO("bytesToAdd to committed bucket: "<<m_bytesToAdd);


//Adding bytes to Committed bucket

if (m_committedBucketSize + m_bytesToAdd >= m_cBS)
     {
       m_committedBucketSize = m_cBS;
     }

else {
       m_committedBucketSize = m_committedBucketSize + m_bytesToAdd;
     }




// Calculating bytes to add to Peak Bucket

m_bytesToAdd = (m_currentPacketArrivalTime - m_lastPacketArrivalTime) * (m_pIR/8);

NS_LOG_INFO("bytesToAdd to peak bucket: "<<m_bytesToAdd);

m_lastPacketArrivalTime = m_currentPacketArrivalTime;

(SLA->m_mSpec).lastPacketArrivalTime = m_lastPacketArrivalTime;


//Adding bytes to Peak bucket

if (m_peakBucketSize + m_bytesToAdd >= m_pBS)
     {
       m_peakBucketSize = m_pBS;
     }

else {
       m_peakBucketSize = m_peakBucketSize + m_bytesToAdd;
     }



(SLA->m_mSpec).committedBucketSize = m_committedBucketSize;

(SLA->m_mSpec).peakBucketSize = m_peakBucketSize;

NS_LOG_INFO("committedBucketSizeAfterAdding: "<<m_committedBucketSize);

NS_LOG_INFO("peakBucketSizeAfterAdding: "<<m_peakBucketSize);


//Getting the size of the packet in bytes
PppHeader pppHeader;

Ptr<Packet> q = p->Copy ();

q->RemoveHeader (pppHeader);


 m_packetSize = q->GetSize();

NS_LOG_INFO("packetSize: "<<m_packetSize);


//Testing conformance

if ( m_peakBucketSize - m_packetSize < 0)
    {
     NS_LOG_INFO("Packet non-conformant: RED");
     NS_LOG_INFO("NO tokens removed");
     NS_LOG_INFO("committedBucketSize: "<<m_committedBucketSize);
     NS_LOG_INFO("peakBucketSize: "<<m_peakBucketSize);




     return conformanceLevel_3;
    }




if (m_committedBucketSize - m_packetSize < 0)
    {
      m_peakBucketSize = m_peakBucketSize - m_packetSize;

(SLA->m_mSpec).peakBucketSize = m_peakBucketSize;

     NS_LOG_INFO("Packet non-conformant: YELLOW");

     NS_LOG_INFO("peakBucketSizeAfterRemoving: "<<m_peakBucketSize);

     return conformanceLevel_2;
    }



else
     {
      m_committedBucketSize = m_committedBucketSize - m_packetSize;

      m_peakBucketSize = m_peakBucketSize - m_packetSize;

(SLA->m_mSpec).committedBucketSize = m_committedBucketSize;

(SLA->m_mSpec).peakBucketSize = m_peakBucketSize;

     NS_LOG_INFO("Packet conformant: GREEN");

     NS_LOG_INFO("committedBucketSizeAfterRemoving: "<<m_committedBucketSize);

     NS_LOG_INFO("peakBucketSizeAfterRemoving: "<<m_peakBucketSize);

     return conformanceLevel_1;
    }


}

} // namespace ns3


