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

#ifndef TokenBucket_H
#define TokenBucket_H

#include "ns3/packet.h"
#include "diff-serv-meter.h"

#include "ns3/simulator.h"
#include "ns3/nstime.h"
#include "ns3/ppp-header.h"


namespace ns3 {


class TokenBucket : public DiffServMeter {
public:
  static TypeId GetTypeId (void);

  TokenBucket ();

  virtual ~TokenBucket();




  virtual int MeterPacket (Ptr<Packet> p, Ptr<DiffServSla> SLA);

private:

  float m_lastPacketArrivalTime;
  float m_currentPacketArrivalTime;

  float m_committedBucketSize;
  int m_cBS;

  float m_bytesToAdd;
  int m_cIR ;
  int m_packetSize;


};

}; // namespace ns3

#endif /* TokenBucket_H */
