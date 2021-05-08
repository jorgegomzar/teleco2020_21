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

#ifndef WRED_H
#define WRED_H

#include <cmath>
#include "diff-serv-aqm.h"


namespace ns3 {



class WRED : public DiffServAQM {
public:
  static TypeId GetTypeId (void);

  WRED ();

  virtual ~WRED();




 int RandomNumberGenerator(int min, int max);

void SetAF1WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop);

void SetAF2WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop);

void SetAF3WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop);

void SetAF4WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop);


private:
  virtual bool DoAQM ( int currentQueueSize, int DS);



//AQM variables

float m_gradient;
float m_packetDropProbability;

//AF1

int m_AF1_exponentialWeight;
float m_AF1_averageQueueSize;

float m_AF1_minThresholdRed;
float m_AF1_minThresholdYellow;
float m_AF1_minThresholdGreen;

float m_AF1_maxThresholdRed;
float m_AF1_maxThresholdYellow;
float m_AF1_maxThresholdGreen;

float m_AF1_maxProbabilityRed;
float m_AF1_maxProbabilityYellow;
float m_AF1_maxProbabilityGreen;
//


//AF2

int m_AF2_exponentialWeight;
float m_AF2_averageQueueSize;

float m_AF2_minThresholdRed;
float m_AF2_minThresholdYellow;
float m_AF2_minThresholdGreen;

float m_AF2_maxThresholdRed;
float m_AF2_maxThresholdYellow;
float m_AF2_maxThresholdGreen;

float m_AF2_maxProbabilityRed;
float m_AF2_maxProbabilityYellow;
float m_AF2_maxProbabilityGreen;
//

//AF3

int m_AF3_exponentialWeight;
float m_AF3_averageQueueSize;

float m_AF3_minThresholdRed;
float m_AF3_minThresholdYellow;
float m_AF3_minThresholdGreen;

float m_AF3_maxThresholdRed;
float m_AF3_maxThresholdYellow;
float m_AF3_maxThresholdGreen;

float m_AF3_maxProbabilityRed;
float m_AF3_maxProbabilityYellow;
float m_AF3_maxProbabilityGreen;
//

//AF4

int m_AF4_exponentialWeight;
float m_AF4_averageQueueSize;

int m_AF4_minThresholdRed;
float m_AF4_minThresholdYellow;
float m_AF4_minThresholdGreen;

float m_AF4_maxThresholdRed;
float m_AF4_maxThresholdYellow;
float m_AF4_maxThresholdGreen;

float m_AF4_maxProbabilityRed;
float m_AF4_maxProbabilityYellow;
float m_AF4_maxProbabilityGreen;
//


};

}; // namespace ns3

#endif /* WRED_H */
