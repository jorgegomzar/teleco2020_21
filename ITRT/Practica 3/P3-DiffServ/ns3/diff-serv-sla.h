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


#ifndef DiffServSla_H
#define DiffServSla_H


#include "ns3/object.h"

using namespace std;

struct ConformanceSpec{
int initialCodePoint;
int nonConformantActionI;
int nonConformantActionII;
 };
   

struct MeterSpec{
string meterID;
int   cIR;
int   cBS;
int   eBS;
int   pIR;
int   pBS;
float lastPacketArrivalTime;
float committedBucketSize;
float extraBucketSize;
float peakBucketSize;  
};

namespace ns3 {


class DiffServSla : public Object {
public:
  static TypeId GetTypeId (void);
  

DiffServSla ();

DiffServSla(int slaId, ConformanceSpec cSpec, MeterSpec mSpec );

  virtual ~DiffServSla();

 void SetSlaId (int slaId);
 void SetConformanceSpecification( ConformanceSpec cSpec);
 void SetMeterSpecification( MeterSpec mSpec);

int GetSlaId (void);
ConformanceSpec GetConformanceSpecification(void);
MeterSpec GetMeterSpecification(void);
 
void SetSlaMeter (bool meter);
bool GetSlaMeter (void); 

public:
ConformanceSpec m_cSpec;
MeterSpec m_mSpec;
 
private:
int m_slaId;
bool m_meterSla;




};

}; // namespace ns3

#endif /* DiffServSla_H */
