/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_PoseKeeping.cpp                                    */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_PoseKeeping.h"
#include "ZAIC_PEAK.h"
#include "OF_Coupler.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_PoseKeeping::BHV_PoseKeeping(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "defaultname");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");


  // Defult values for all parameters
  m_osx = 0;
  m_osy = 0;
  m_osheading = 0;

  m_static_heading = 0;
  m_static_station_x = 0;
  m_static_station_y = 0;
  m_a_range = 15;
  m_r_range = 1;



  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y");
  addInfoVars("HEADING", "no_warning");
  


}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_PoseKeeping::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());
  
  if((param == "foo") && isNumber(val)) {
    // Set local member variables here
    return(true);
  }
  else if (param == "bar") {
    // return(setBooleanOnString(m_my_bool, val));
  }
  else if ((param == "posekeeping_heading") || (param == "heading")) {
    m_static_heading = double_val;
    return(true);
  } 
  else if ((param == "posekeeping_pt") || (param == "point")) {
    string left  = stripBlankEnds(biteString(val, ','));
    string right = stripBlankEnds(val);
    if(!isNumber(left) || !isNumber(right))
        return(false);
    m_static_station_x = atof(left.c_str());
    m_static_station_y = atof(right.c_str());
    return(true);
  }
  else if (param == "radius_range") {
    m_r_range = double_val;
    return(true);
  }
  else if (param == "angle_range") {
    m_a_range = double_val;
    return(true);
  }

  // If not handled above, then just return false;
  return(false);
}

//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_PoseKeeping::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_PoseKeeping::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_PoseKeeping::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_PoseKeeping::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_PoseKeeping::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_PoseKeeping::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_PoseKeeping::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_PoseKeeping::onRunState()
{
  bool ok1, ok2, ok3;
  m_osx = getBufferDoubleVal("NAV_X", ok1);
  m_osy = getBufferDoubleVal("NAV_Y", ok2);
  m_osheading = getBufferDoubleVal("HEADING", ok3);
  if (!ok1 || !ok2){
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0); 
   }
  if (!ok3){
    postWMessage("No ownship heading info in info_buffer.");
    return(0);
  }
  // Part 1: Build the IvP function
  IvPFunction *ipf = 0;



  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}

//----------------------------------------------------------------
//Procedure: buildFunctionWithZAIC()
//

IvPFunction* BHV_PoseKeeping::buildFunctionWithZAIC()
{
  ZAIC_PEAK spd_zaic(m_domain, "speed");



}
