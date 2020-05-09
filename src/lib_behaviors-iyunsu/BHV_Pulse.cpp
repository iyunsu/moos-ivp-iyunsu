/************************************************************/
/*    NAME: iyunsu                                          */
/*    ORGN: MIT                                             */
/*    FILE: BHV_Pulse.cpp                                   */
/*    DATE: 20190320                                        */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_Pulse.h"
#include <iostream>
#include "XYRangePulse.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_Pulse::BHV_Pulse(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "pulse");

  // Default values
  m_index_last=0;
  t=0;
  m_osx = 0;
  m_osy = 0; 
  m_index_deq.clear();
  m_index_deq.push_back(0);
  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");

  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y");
  addInfoVars("WPT_INDEX","no_warning");

 // double IvPBehavior:: getBufferCurrTime();

}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_Pulse::setParam(string param, string val)
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
  else if (param == "pulse_range") {
    m_range = double_val;
    return(true);
  }
  else if (param == "pulse_duration"){
    m_pulse_duration = double_val;
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

void BHV_Pulse::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_Pulse::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_Pulse::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_Pulse::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_Pulse::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_Pulse::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_Pulse::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_Pulse::onRunState()
{
  // Part 1: Build the IvP function
  IvPFunction *ipf = 0;

  bool ok_x,ok_y,ok_i;
  m_osx = getBufferDoubleVal("NAV_X",ok_x);
  m_osy = getBufferDoubleVal("NAV_Y",ok_y);
  m_index = getBufferDoubleVal("WPT_INDEX",ok_i);
  if(!ok_x || !ok_y){
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0);
  }
//  if(!ok_i){
//    postWMessage("No ownship WPT_INDEX in info_buffer.");
//    return(0);
//  
//  }
  


  m_curr_time = getBufferCurrTime();
  postMessage("TIME_CURR", m_curr_time);
  postMessage("NAV_INDEXX",m_index);

  
//  int point = m_index - m_index_deq.back();
  m_index_deq.push_back(m_index);
  int last_index = m_index_deq.front();
  


  if (m_index != last_index ){
    m_pulse_time = m_curr_time +5;
    postMessage("T_PULSE",m_pulse_time);
    postMessage("T_CURR",m_curr_time);
  }

  double five_s_later = m_curr_time - m_pulse_time;  
  postMessage("FIVE",five_s_later);
  if (five_s_later < 0.1 && five_s_later >0){
    XYRangePulse pulse;
    pulse.set_x(m_osx);
    pulse.set_y(m_osy);
    pulse.set_label("bhv_pulse");
    pulse.set_rad(m_range);
    pulse.set_duration(m_pulse_duration);
    pulse.set_time(m_curr_time+5);
    pulse.set_color("edge", "yellow");
    pulse.set_color("fill", "yellow");

    string spec = pulse.get_spec();
    postMessage("VIEW_RANGE_PULSE", spec);

    int t;
    postMessage("PULSE_NUM",t++);
  }

  
  m_index_deq.pop_front();

  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}

