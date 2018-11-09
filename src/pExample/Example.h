/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: Example.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef Example_HEADER
#define Example_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class Example : public CMOOSApp
{
 public:
   Example();
   ~Example();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
 int k;
};

#endif 
