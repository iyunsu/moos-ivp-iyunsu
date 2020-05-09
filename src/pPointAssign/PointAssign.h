/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: PointAssign.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef PointAssign_HEADER
#define PointAssign_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
using namespace std;
#include <deque>
#include <string>

class PointAssign : public CMOOSApp
{
 public:
   PointAssign();
   ~PointAssign();
   std::deque<string> m_input_dequ_point;
   string point_in_string;

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();
//   void postViewPoint();

    
 private: // Configuration variables
 int m_method;

 int m_stop;
 int m_size;
 string m_last;

 private: // State variables
 std::deque<string> m_odd;
 std::deque<string> m_even;
 int k;
 
};

#endif 
