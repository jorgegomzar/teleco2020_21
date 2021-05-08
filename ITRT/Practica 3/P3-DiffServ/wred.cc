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
#include "ns3/wred.h"

NS_LOG_COMPONENT_DEFINE ("WRED");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (WRED);

TypeId WRED::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WRED")
    .SetParent<DiffServAQM> ()
    .AddConstructor<WRED> ()

    ;

  return tid;
}

WRED::WRED ()
{
  NS_LOG_FUNCTION_NOARGS ();


m_aqmId = "WRED";

//Configuring the random number
srand(time(NULL));

//AF1
m_AF1_exponentialWeight = 7;

 m_AF1_minThresholdRed = 10;
 m_AF1_minThresholdYellow =30 ;
 m_AF1_minThresholdGreen = 50;

 m_AF1_maxThresholdRed = 40 ;
 m_AF1_maxThresholdYellow = 60;
 m_AF1_maxThresholdGreen = 100 ;

 m_AF1_maxProbabilityRed = 90;
 m_AF1_maxProbabilityYellow = 60;
 m_AF1_maxProbabilityGreen = 30 ;

//AF2

m_AF2_exponentialWeight = 7;

 m_AF2_minThresholdRed = 10;
 m_AF2_minThresholdYellow =30 ;
 m_AF2_minThresholdGreen = 50;

 m_AF2_maxThresholdRed = 40 ;
 m_AF2_maxThresholdYellow = 60;
 m_AF2_maxThresholdGreen = 100 ;

 m_AF2_maxProbabilityRed = 90;
 m_AF2_maxProbabilityYellow = 60;
 m_AF2_maxProbabilityGreen = 30 ;


//AF3

m_AF3_exponentialWeight = 7;

 m_AF3_minThresholdRed = 10;
 m_AF3_minThresholdYellow =30 ;
 m_AF3_minThresholdGreen = 50;

 m_AF3_maxThresholdRed = 40 ;
 m_AF3_maxThresholdYellow = 60;
 m_AF3_maxThresholdGreen = 100 ;

 m_AF3_maxProbabilityRed = 90;
 m_AF3_maxProbabilityYellow = 60;
 m_AF3_maxProbabilityGreen = 30 ;

//AF4

m_AF4_exponentialWeight = 7;

 m_AF4_minThresholdRed = 10;
 m_AF4_minThresholdYellow =30 ;
 m_AF4_minThresholdGreen = 50;

 m_AF4_maxThresholdRed = 40 ;
 m_AF4_maxThresholdYellow = 60;
 m_AF4_maxThresholdGreen = 100 ;

 m_AF4_maxProbabilityRed = 90;
 m_AF4_maxProbabilityYellow = 60;
 m_AF4_maxProbabilityGreen = 30 ;


}



WRED::~WRED ()
{
  NS_LOG_FUNCTION_NOARGS ();
}


bool WRED:: DoAQM (int currentQueueSize, int DS)
{

NS_LOG_INFO("WRED:");

//Updating Average Queue size

//AF1

if( (DS == 40) || (DS == 48) || (DS == 56) )
{

m_AF1_averageQueueSize = m_AF1_averageQueueSize * ( 1-(pow(0.5,m_AF1_exponentialWeight) ) )+

(currentQueueSize *  pow(0.5,m_AF1_exponentialWeight) );

  NS_LOG_INFO("AF1 AverageQueueSize: "<<m_AF1_averageQueueSize);
  NS_LOG_INFO("AF1 CurrentQueueSize: "<<currentQueueSize);
}

//AF2

if( (DS == 72) || (DS == 80) || (DS == 88) )
{

m_AF2_averageQueueSize = m_AF2_averageQueueSize * ( 1-(pow(0.5,m_AF2_exponentialWeight) ) )+

(currentQueueSize *  pow(0.5,m_AF2_exponentialWeight) );

  NS_LOG_INFO("AF2 AverageQueueSize: "<<m_AF2_averageQueueSize);
  NS_LOG_INFO("AF2 CurrentQueueSize: "<<currentQueueSize);

}


//AF3


if( (DS == 104) || (DS == 112) || (DS == 120) )
{

m_AF3_averageQueueSize = m_AF3_averageQueueSize * ( 1-(pow(0.5,m_AF3_exponentialWeight) ) )+

(currentQueueSize *  pow(0.5,m_AF3_exponentialWeight) );


  NS_LOG_INFO("AF3 AverageQueueSize: "<<m_AF3_averageQueueSize);
  NS_LOG_INFO("AF3 CurrentQueueSize: "<<currentQueueSize);

}

//AF4

if( (DS == 136) || (DS == 144) || (DS == 152) )
{

m_AF4_averageQueueSize = m_AF4_averageQueueSize * ( 1-(pow(0.5,m_AF4_exponentialWeight) ) )+

(currentQueueSize *  pow(0.5,m_AF4_exponentialWeight) );

  NS_LOG_INFO("AF4 AverageQueueSize: "<<m_AF4_averageQueueSize);
  NS_LOG_INFO("AF4 CurrentQueueSize: "<<currentQueueSize);

}




switch(DS)
{

//AF1 Green

case 40:

NS_LOG_INFO("AF1 GREEN packet");

if (m_AF1_averageQueueSize <= m_AF1_minThresholdGreen)
  {
    m_packetDropProbability = 0;
  }

if (m_AF1_averageQueueSize >= m_AF1_maxThresholdGreen)
  {
    m_packetDropProbability = 100;
  }

if((m_AF1_minThresholdGreen< m_AF1_averageQueueSize)&& (m_AF1_averageQueueSize < m_AF1_maxThresholdGreen))
  {
   m_gradient = (m_AF1_maxThresholdGreen - m_AF1_minThresholdGreen)/ m_AF1_maxProbabilityGreen;

   m_packetDropProbability = (m_AF1_averageQueueSize - m_AF1_minThresholdGreen)/m_gradient;

   NS_LOG_INFO("AF1 Green gradient :" <<m_gradient);
  }
break;

//AF1 Yellow

case 48:

NS_LOG_INFO("AF1 YELLOW packet");

if (m_AF1_averageQueueSize <= m_AF1_minThresholdYellow)
  {
    m_packetDropProbability = 0;
  }

if (m_AF1_averageQueueSize >= m_AF1_maxThresholdYellow)
  {
    m_packetDropProbability = 100;
  }

if((m_AF1_minThresholdYellow< m_AF1_averageQueueSize)&& (m_AF1_averageQueueSize < m_AF1_maxThresholdYellow))
  {
  m_gradient = (m_AF1_maxThresholdYellow - m_AF1_minThresholdYellow)/ m_AF1_maxProbabilityYellow;

   m_packetDropProbability = (m_AF1_averageQueueSize - m_AF1_minThresholdYellow)/m_gradient;

     NS_LOG_INFO("AF1 Yellow gradient :" <<m_gradient);
  }

break;

//AF1 Red

case 56:

NS_LOG_INFO("AF1 RED packet");

if (m_AF1_averageQueueSize <= m_AF1_minThresholdRed)
  {
    m_packetDropProbability = 0;
  }

if (m_AF1_averageQueueSize >= m_AF1_maxThresholdRed)
  {
    m_packetDropProbability = 100;
  }

if((m_AF1_minThresholdRed< m_AF1_averageQueueSize)&& (m_AF1_averageQueueSize < m_AF1_maxThresholdRed))
  {
   m_gradient = (m_AF1_maxThresholdRed - m_AF1_minThresholdRed)/ m_AF1_maxProbabilityRed;

   m_packetDropProbability = (m_AF1_averageQueueSize - m_AF1_minThresholdRed)/m_gradient;

   NS_LOG_INFO("AF1 Red gradient :" <<m_gradient);
  }
break;











//AF2 Green

case 72:

NS_LOG_INFO("AF2 GREEN packet");

if (m_AF2_averageQueueSize <= m_AF2_minThresholdGreen)
  {
    m_packetDropProbability = 0;
  }

if (m_AF2_averageQueueSize >= m_AF2_maxThresholdGreen)
  {
    m_packetDropProbability = 100;
  }

if((m_AF2_minThresholdGreen< m_AF2_averageQueueSize)&& (m_AF2_averageQueueSize < m_AF2_maxThresholdGreen))
  {
   m_gradient = (m_AF2_maxThresholdGreen - m_AF2_minThresholdGreen)/ m_AF2_maxProbabilityGreen;

   m_packetDropProbability = (m_AF2_averageQueueSize - m_AF2_minThresholdGreen)/m_gradient;

   NS_LOG_INFO("AF2 Green gradient :" <<m_gradient);
  }
break;

//AF2 Yellow

case 80:

NS_LOG_INFO("AF2 YELLOW packet");

if (m_AF2_averageQueueSize <= m_AF2_minThresholdYellow)
  {
    m_packetDropProbability = 0;
  }

if (m_AF2_averageQueueSize >= m_AF2_maxThresholdYellow)
  {
    m_packetDropProbability = 100;
  }

if((m_AF2_minThresholdYellow< m_AF2_averageQueueSize)&& (m_AF2_averageQueueSize < m_AF2_maxThresholdYellow))
  {
  m_gradient = (m_AF2_maxThresholdYellow - m_AF2_minThresholdYellow)/ m_AF2_maxProbabilityYellow;

   m_packetDropProbability = (m_AF2_averageQueueSize - m_AF2_minThresholdYellow)/m_gradient;

     NS_LOG_INFO("AF2 Yellow gradient :" <<m_gradient);
  }

break;

//AF2 Red

case 88:

NS_LOG_INFO("AF2 RED packet");

if (m_AF2_averageQueueSize <= m_AF2_minThresholdRed)
  {
    m_packetDropProbability = 0;
  }

if (m_AF2_averageQueueSize >= m_AF2_maxThresholdRed)
  {
    m_packetDropProbability = 100;
  }

if((m_AF2_minThresholdRed< m_AF2_averageQueueSize)&& (m_AF2_averageQueueSize < m_AF2_maxThresholdRed))
  {
   m_gradient = (m_AF2_maxThresholdRed - m_AF2_minThresholdRed)/ m_AF2_maxProbabilityRed;

   m_packetDropProbability = (m_AF2_averageQueueSize - m_AF2_minThresholdRed)/m_gradient;

   NS_LOG_INFO("AF2 Red gradient :" <<m_gradient);
  }
break;












//AF3 Green

case 104:

NS_LOG_INFO("AF3 GREEN packet");

if (m_AF3_averageQueueSize <= m_AF3_minThresholdGreen)
  {
    m_packetDropProbability = 0;
  }

if (m_AF3_averageQueueSize >= m_AF3_maxThresholdGreen)
  {
    m_packetDropProbability = 100;
  }

if((m_AF3_minThresholdGreen< m_AF3_averageQueueSize)&& (m_AF3_averageQueueSize < m_AF3_maxThresholdGreen))
  {
   m_gradient = (m_AF3_maxThresholdGreen - m_AF3_minThresholdGreen)/ m_AF3_maxProbabilityGreen;

   m_packetDropProbability = (m_AF3_averageQueueSize - m_AF3_minThresholdGreen)/m_gradient;

   NS_LOG_INFO("AF3 Green gradient :" <<m_gradient);
  }
break;

//AF3 Yellow

case 112:

NS_LOG_INFO("AF3 YELLOW packet");

if (m_AF3_averageQueueSize <= m_AF3_minThresholdYellow)
  {
    m_packetDropProbability = 0;
  }

if (m_AF3_averageQueueSize >= m_AF3_maxThresholdYellow)
  {
    m_packetDropProbability = 100;
  }

if((m_AF3_minThresholdYellow< m_AF3_averageQueueSize)&& (m_AF3_averageQueueSize < m_AF3_maxThresholdYellow))
  {
  m_gradient = (m_AF3_maxThresholdYellow - m_AF3_minThresholdYellow)/ m_AF3_maxProbabilityYellow;

   m_packetDropProbability = (m_AF3_averageQueueSize - m_AF3_minThresholdYellow)/m_gradient;

     NS_LOG_INFO("AF3 Yellow gradient :" <<m_gradient);
  }

break;

//AF3 Red

case 120:

NS_LOG_INFO("AF3 RED packet");

if (m_AF3_averageQueueSize <= m_AF3_minThresholdRed)
  {
    m_packetDropProbability = 0;
  }

if (m_AF3_averageQueueSize >= m_AF3_maxThresholdRed)
  {
    m_packetDropProbability = 100;
  }

if((m_AF3_minThresholdRed< m_AF3_averageQueueSize)&& (m_AF3_averageQueueSize < m_AF3_maxThresholdRed))
  {
   m_gradient = (m_AF3_maxThresholdRed - m_AF3_minThresholdRed)/ m_AF3_maxProbabilityRed;

   m_packetDropProbability = (m_AF3_averageQueueSize - m_AF3_minThresholdRed)/m_gradient;

   NS_LOG_INFO("AF3 Red gradient :" <<m_gradient);
  }
break;












//AF4 Green

case 136:

NS_LOG_INFO("AF4 GREEN packet");

if (m_AF4_averageQueueSize <= m_AF4_minThresholdGreen)
  {
    m_packetDropProbability = 0;
  }

if (m_AF4_averageQueueSize >= m_AF4_maxThresholdGreen)
  {
    m_packetDropProbability = 100;
  }

if((m_AF4_minThresholdGreen< m_AF4_averageQueueSize)&& (m_AF4_averageQueueSize < m_AF4_maxThresholdGreen))
  {
   m_gradient = (m_AF4_maxThresholdGreen - m_AF4_minThresholdGreen)/ m_AF4_maxProbabilityGreen;

   m_packetDropProbability = (m_AF4_averageQueueSize - m_AF4_minThresholdGreen)/m_gradient;

   NS_LOG_INFO("AF4 Green gradient :" <<m_gradient);
  }
break;



case 144:

NS_LOG_INFO("AF4 YELLOW packet");

if (m_AF4_averageQueueSize <= m_AF4_minThresholdYellow)
  {
    m_packetDropProbability = 0;
  }

if (m_AF4_averageQueueSize >= m_AF4_maxThresholdYellow)
  {
    m_packetDropProbability = 100;
  }

if((m_AF4_minThresholdYellow< m_AF4_averageQueueSize)&& (m_AF4_averageQueueSize < m_AF4_maxThresholdYellow))
  {
  m_gradient = (m_AF4_maxThresholdYellow - m_AF4_minThresholdYellow)/ m_AF4_maxProbabilityYellow;

   m_packetDropProbability = (m_AF4_averageQueueSize - m_AF4_minThresholdYellow)/m_gradient;

     NS_LOG_INFO("AF4 Yellow gradient :" <<m_gradient);
  }

break;

//AF4 Red

case 152:

NS_LOG_INFO("AF4 RED packet");

if (m_AF4_averageQueueSize <= m_AF4_minThresholdRed)
  {
    m_packetDropProbability = 0;
  }

if (m_AF4_averageQueueSize >= m_AF4_maxThresholdRed)
  {
    m_packetDropProbability = 100;
  }

if((m_AF4_minThresholdRed< m_AF4_averageQueueSize)&& (m_AF4_averageQueueSize < m_AF4_maxThresholdRed))
  {
   m_gradient = (m_AF4_maxThresholdRed - m_AF4_minThresholdRed)/ m_AF4_maxProbabilityRed;

   m_packetDropProbability = (m_AF4_averageQueueSize - m_AF4_minThresholdRed)/m_gradient;

   NS_LOG_INFO("AF4 Red gradient :" <<m_gradient);
  }
break;



default:

return true;

}

//Deciding if packet should be dropped

NS_LOG_INFO("Packet drop probability: "<< m_packetDropProbability);

int randomInt = RandomNumberGenerator(1,100);

NS_LOG_INFO("Random number: "<< randomInt);


if(randomInt <=  m_packetDropProbability)
  {
  NS_LOG_INFO("Packet to be dropped--returning false");
  return false;
  }

else
 {
 NS_LOG_INFO("Packet to be enqueued--returning true");
 return true;
 }




}



// RandomNumberGenerator

int WRED::RandomNumberGenerator(int min, int max)
{

int randomInt;
randomInt = rand()%max + min;
return randomInt;

}




//SetAF1WRED

void WRED::SetAF1WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop)
{

 m_AF1_exponentialWeight = exp;

 m_AF1_minThresholdRed = redMinTh;
 m_AF1_minThresholdYellow = yellowMinTh;
 m_AF1_minThresholdGreen = greenMinTh;

 m_AF1_maxThresholdRed = redMaxTh;
 m_AF1_maxThresholdYellow = yellowMaxTh;
 m_AF1_maxThresholdGreen = greenMaxTh;

 m_AF1_maxProbabilityRed = redMaxDrop;
 m_AF1_maxProbabilityYellow = yellowMaxDrop;
 m_AF1_maxProbabilityGreen = greenMaxDrop;

}

//SetAF2WRED

void WRED::SetAF2WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop)
{

 m_AF2_exponentialWeight = exp;

 m_AF2_minThresholdRed = redMinTh;
 m_AF2_minThresholdYellow = yellowMinTh;
 m_AF2_minThresholdGreen = greenMinTh;

 m_AF2_maxThresholdRed = redMaxTh;
 m_AF2_maxThresholdYellow = yellowMaxTh;
 m_AF2_maxThresholdGreen = greenMaxTh;

 m_AF2_maxProbabilityRed = redMaxDrop;
 m_AF2_maxProbabilityYellow = yellowMaxDrop;
 m_AF2_maxProbabilityGreen = greenMaxDrop;

}

//SetAF3WRED

void WRED::SetAF3WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop)
{

 m_AF3_exponentialWeight = exp;

 m_AF3_minThresholdRed = redMinTh;
 m_AF3_minThresholdYellow = yellowMinTh;
 m_AF3_minThresholdGreen = greenMinTh;

 m_AF3_maxThresholdRed = redMaxTh;
 m_AF3_maxThresholdYellow = yellowMaxTh;
 m_AF3_maxThresholdGreen = greenMaxTh;

 m_AF3_maxProbabilityRed = redMaxDrop;
 m_AF3_maxProbabilityYellow = yellowMaxDrop;
 m_AF3_maxProbabilityGreen = greenMaxDrop;

}


//SetAF4WRED

void WRED::SetAF4WRED(int exp, int redMinTh,int redMaxTh, int redMaxDrop, int yellowMinTh, int yellowMaxTh, int yellowMaxDrop, int greenMinTh, int greenMaxTh, int greenMaxDrop)
{

 m_AF4_exponentialWeight = exp;

 m_AF4_minThresholdRed = redMinTh;
 m_AF4_minThresholdYellow = yellowMinTh;
 m_AF4_minThresholdGreen = greenMinTh;

 m_AF4_maxThresholdRed = redMaxTh;
 m_AF4_maxThresholdYellow = yellowMaxTh;
 m_AF4_maxThresholdGreen = greenMaxTh;

 m_AF4_maxProbabilityRed = redMaxDrop;
 m_AF4_maxProbabilityYellow = yellowMaxDrop;
 m_AF4_maxProbabilityGreen = greenMaxDrop;

}


} // namespace ns3


