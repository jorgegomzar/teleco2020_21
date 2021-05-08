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


#include "ns3/diff-serv-flow.h"
#include "ns3/log.h"

using namespace std;

NS_LOG_COMPONENT_DEFINE ("DiffServFlow");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (DiffServFlow);

TypeId DiffServFlow::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DiffServFlow")
  .SetParent<Object> ()

    ;

  return tid;
}


DiffServFlow::DiffServFlow ()
{

  NS_LOG_FUNCTION_NOARGS ();
}


DiffServFlow::~DiffServFlow()
{
  NS_LOG_FUNCTION_NOARGS ();
}


DiffServFlow::DiffServFlow(int flowId,char const * scrAddress,char const * destAddress,int scrPortNumber,int destPortNumber)
{

m_flowId = flowId;
 m_scrAddress.Set(scrAddress);
m_destAddress.Set(destAddress);
  m_scrPortNumber = scrPortNumber;
 m_destPortNumber = destPortNumber;

}



 void DiffServFlow:: SetFlowId (int flowId)
{
  m_flowId = flowId;
}

void DiffServFlow:: SetSourceAddress ( char const * scrAddress)
{
 m_scrAddress.Set(scrAddress);
}

void DiffServFlow:: SetDestinationAddress ( char const * destAddress)
{
 m_destAddress.Set(destAddress);
}

void DiffServFlow:: SetSourcePort (int scrPortNumber)
{
  m_scrPortNumber = scrPortNumber;
}

void DiffServFlow:: SetDestinationPort (int destPortNumber)
{
 m_destPortNumber = destPortNumber;
}

void DiffServFlow:: SetSla (Ptr<DiffServSla> sla)
{
  m_sla = sla;
}

//Get methods


int DiffServFlow:: GetFlowId (void)
{
  return m_flowId;
}

Ipv4Address DiffServFlow:: GetSourceAddress (void)
{
 return m_scrAddress;
}

Ipv4Address DiffServFlow:: GetDestinationAddress (void)
{
 return m_destAddress;
}

int DiffServFlow:: GetSourcePort (void)
{
 return m_scrPortNumber;
}

int DiffServFlow:: GetDestinationPort (void)
{
 return m_destPortNumber;
}

Ptr<DiffServSla> DiffServFlow:: GetSla (void)
{
  return m_sla;
}


//DiffServFlow end

}//ns3


