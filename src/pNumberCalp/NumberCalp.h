/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: NumberCalp.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef NumberCalp_HEADER
#define NumberCalp_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class NumberCalp : public AppCastingMOOSApp
{
 public:
   NumberCalp();
   ~NumberCalp();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables

 private: // State variables
};

#endif 
