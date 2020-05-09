/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_PoseKeeping.h                                      */
/*    DATE:                                                 */
/************************************************************/

#ifndef PoseKeeping_HEADER
#define PoseKeeping_HEADER

#include <string>
#include "IvPBehavior.h"

class BHV_PoseKeeping : public IvPBehavior {
public:
  BHV_PoseKeeping(IvPDomain);
  ~BHV_PoseKeeping() {};
  
  bool         setParam(std::string, std::string);
  void         onSetParamComplete();
  void         onCompleteState();
  void         onIdleState();
  void         onHelmStart();
  void         postConfigStatus();
  void         onRunToIdleState();
  void         onIdleToRunState();
  IvPFunction* onRunState();

protected: // Local Utility functions
  IvPFunction* buildFunctionWithZAIC();

protected: // Configuration parameters
  double m_static_heading;
  double m_static_station_x;
  double m_static_station_y;
  double m_r_range;
  double m_a_range;

protected: // State variables
  double m_osx;
  double m_osy;
  double m_osheading;
};
 

#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_PoseKeeping(domain);}
}
#endif
