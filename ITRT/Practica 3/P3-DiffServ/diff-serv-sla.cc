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

#include "ns3/diff-serv-sla.h"
#include "ns3/log.h"

using namespace std;

NS_LOG_COMPONENT_DEFINE ("DiffServSla");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (DiffServSla);

TypeId DiffServSla::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DiffServSla")
  .SetParent<Object> ()

    ;

  return tid;
}


DiffServSla::DiffServSla()
{
 NS_LOG_FUNCTION_NOARGS ();

m_meterSla = true;

}


DiffServSla::~DiffServSla()
{
  NS_LOG_FUNCTION_NOARGS ();
}



DiffServSla::DiffServSla(int slaId, ConformanceSpec cSpec, MeterSpec mSpec)
{

m_meterSla = true;

m_slaId = slaId;

m_cSpec = cSpec;

 int codepoint = m_cSpec.initialCodePoint;
 int nonConformantActionI = m_cSpec.nonConformantActionI;
 int nonConformantActionII = m_cSpec.nonConformantActionII;

 NS_ASSERT( (codepoint >= 0) && (codepoint <= 252) );


NS_ASSERT( (nonConformantActionI >= 0) && ( (nonConformantActionI <= 252) || (nonConformantActionI == 256) ) );


NS_ASSERT( (nonConformantActionII >= 0) && ( (nonConformantActionII <= 252) || (nonConformantActionII == 256) ) );




m_mSpec = mSpec;

NS_ASSERT ( (mSpec.cIR >= 0) && (mSpec.cBS >= 0) && (mSpec.pIR >= 0) && (mSpec.pBS >= 0) && (mSpec.eBS >= 0) );


m_mSpec.committedBucketSize = m_mSpec.cBS;
m_mSpec.extraBucketSize = m_mSpec.eBS;
m_mSpec.peakBucketSize = m_mSpec.pBS;
m_mSpec.lastPacketArrivalTime = 0;



}

 void DiffServSla:: SetSlaId (int slaId)
{
  m_slaId = slaId;
}

void DiffServSla :: SetConformanceSpecification( ConformanceSpec cSpec)
{
 m_cSpec = cSpec;

 int codepoint = m_cSpec.initialCodePoint;
 int nonConformantActionI = m_cSpec.nonConformantActionI;
 int nonConformantActionII = m_cSpec.nonConformantActionII;

 NS_ASSERT( (codepoint >= 0) && (codepoint <= 252) );


NS_ASSERT( (nonConformantActionI >= 0) && ( (nonConformantActionI <= 252) || (nonConformantActionI == 256) ) );


NS_ASSERT( (nonConformantActionII >= 0) && ( (nonConformantActionII <= 252) || (nonConformantActionII == 256) ) );


}


void DiffServSla :: SetMeterSpecification( MeterSpec mSpec)
{
 m_mSpec = mSpec;

NS_ASSERT ( (mSpec.cIR >= 0) && (mSpec.cBS >= 0) && (mSpec.pIR >= 0) && (mSpec.pBS >= 0) && (mSpec.eBS >= 0) );

 m_mSpec.committedBucketSize = m_mSpec.cBS;
 m_mSpec.extraBucketSize = m_mSpec.eBS;
 m_mSpec.peakBucketSize = m_mSpec.pBS;
 m_mSpec.lastPacketArrivalTime = 0;
}




//Get methods


int DiffServSla:: GetSlaId (void)
{
  return m_slaId;
}

ConformanceSpec DiffServSla :: GetConformanceSpecification(void)
{
  return m_cSpec;
}


MeterSpec DiffServSla :: GetMeterSpecification(void)
{
  return m_mSpec;
}

//Metering enable and disable

void DiffServSla::SetSlaMeter(bool meter)
{
 m_meterSla = meter;
}


bool DiffServSla::GetSlaMeter (void)
{
 return m_meterSla;
}


//DiffServSla end

}//ns3


