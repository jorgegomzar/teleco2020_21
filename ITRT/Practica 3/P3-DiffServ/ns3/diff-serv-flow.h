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

#ifndef DiffServFlow_H
#define DiffServFlow_H


#include "ipv4-header.h"
#include "ns3/object.h"
#include "diff-serv-sla.h"



namespace ns3 {


class DiffServFlow : public Object {
public:
  static TypeId GetTypeId (void);
  

DiffServFlow ();

DiffServFlow(int flowId,char const *scrAddress,char const * destAddress,int scrPortNumber,int destPortNumber);

  virtual ~DiffServFlow();

 void SetFlowId (int flowId);
 void SetSourceAddress ( char const * scrAddress);
 void SetDestinationAddress ( char const * destAddress);
 void SetSourcePort (int scrPortNumber);
 void SetDestinationPort (int destPortNumber);
 void SetSla (Ptr<DiffServSla> sla);

int GetFlowId (void);
Ipv4Address GetSourceAddress (void);
Ipv4Address GetDestinationAddress (void);
int GetSourcePort (void);
int GetDestinationPort (void);
Ptr<DiffServSla> GetSla (void);

  

 

private:
 
 int m_flowId;

 Ipv4Address m_scrAddress; 
 Ipv4Address m_destAddress;

 int m_scrPortNumber;
 int m_destPortNumber;
 
 Ptr<DiffServSla> m_sla;
  

};

}; // namespace ns3

#endif /* DiffServFlow_H */
