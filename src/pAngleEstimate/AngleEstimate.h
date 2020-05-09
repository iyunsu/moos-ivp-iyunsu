/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: AngleEstimate.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef AngleEstimate_HEADER
#define AngleEstimate_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include <string>
#include <deque>

class AngleEstimate : public CMOOSApp
{
 public:
   AngleEstimate();
   ~AngleEstimate();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();
   std::string m_collect_data;
   std::string m_exchange;
   std::string m_msmnt_report;
   std::deque<std::string> m_data_deq;
   int i;
   void estimateAngle(std::string);
   std::string m_collect;
   std::vector<double> m_theta_vec;
   void exchange();




 private: // Configuration variables
    std::string m_node;
 private: // State variables
  
};

#endif 
