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

#ifndef DiffServAQM_H
#define DiffServAQM_H

#include "ns3/object.h"

using namespace std;

namespace ns3 {


class DiffServAQM : public Object {
public:
  static TypeId GetTypeId (void);
  
  DiffServAQM ();

  virtual ~DiffServAQM();

  
 virtual bool DoAQM ( int currentQueueSize, int DS) = 0;
  
  string m_aqmId;

};

}; // namespace ns3

#endif /* DiffServAQM_H */
