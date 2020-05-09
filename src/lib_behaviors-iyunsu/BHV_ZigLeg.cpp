/************************************************************/
/*    NAME: iyunsu                                          */
/*    ORGN: MIT                                             */
/*    FILE: BHV_ZigLeg.cpp                                   */
/*    DATE: 20190320                                        */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_ZigLeg.h"
#include <iostream>
#include "XYRangePulse.h"
#include "ZAIC_PEAK.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_ZigLeg::BHV_ZigLeg(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "zigleg");

  // Default values
  m_index_last=0; 
  m_index_deq.clear();
  m_index_deq.push_back(0);
  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course");

  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y, DESIRED_HEADING");
  addInfoVars("WPT_INDEX","no_warning");

 // double IvPBehavior:: getBufferCurrTime();

}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_ZigLeg::setParam(string param, string val)
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
  else if (param == "zig_angle") {
    m_zig_angle = double_val;
    return(true);
  }
  else if (param == "zig_duration"){
    m_zig_duration = double_val;
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

void BHV_ZigLeg::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_ZigLeg::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_ZigLeg::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_ZigLeg::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_ZigLeg::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_ZigLeg::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_ZigLeg::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_ZigLeg::onRunState()
{
  // Part 1: Build the IvP function
  IvPFunction *ipf = 0;

  bool ok_x,ok_y,ok_i,ok_h;
  m_osx = getBufferDoubleVal("NAV_X",ok_x);
  m_osy = getBufferDoubleVal("NAV_Y",ok_y);
  m_index = getBufferDoubleVal("WPT_INDEX",ok_i);
  if(!ok_x || !ok_y){
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0);
  }
  m_heading = getBufferDoubleVal("DESIRED_HEADING",ok_h);
//  if(!ok_i){
//    postWMessage("No ownship WPT_INDEX in info_buffer.");
//    return(0);
//  
//  }
  


  m_curr_time = getBufferCurrTime();
  postMessage("TIME_CURR", m_curr_time);
  postMessage("NAV_INDEXX",m_index);

  
  int last_index = m_index_deq.front();
  m_index_deq.push_back(m_index);
  


  if (m_index != last_index ){
    m_zigleg_time = m_curr_time +5;
    postMessage("T_PULSE_FIVE",m_zigleg_time);
    postMessage("T_ORIGINAL",m_curr_time);
  }

  double five_s_later = m_curr_time - m_zigleg_time;
  postMessage("FIVE", five_s_later);
  if (five_s_later < 0.1 && five_s_later > 0){
    m_new_heading = m_heading + m_zig_angle;
  
  
  
  
  
  }  


  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf){
    ipf->setPWT(m_priority_wt);
    postRepeatableMessage("PWT",m_priority_wt);
  }
  return(ipf);
}
//----------------------------------------------------------------------
// Procedure: buildFunctionWithZAIC

IvPFunction *BHV_ZigLeg::buildFunctionWithZAIC()
{
  ZAIC_PEAK spd_zaic(m_domain,"course");
  crs_zaic.setSummit(m_new_heading);
  crs_zaic.setPeakWidth(0);
  crs_zaic.setBaseWidth(180.0);
  crs_zaic.setSummitDelta(0);
  if(spd_zaic.stateOK() == false) {
    string warning = "Heading ZAIC problems. " + spd_zaic.getWarnings();
    postWMessage(warning);
    return(0);
  }


  //double m_desired_heading


}
