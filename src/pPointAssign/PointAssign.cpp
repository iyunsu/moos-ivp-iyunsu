/************************************************************/
/*    NAME: iyunsu                                              */
/*    ORGN: MIT                                             */
/*    FILE: PointAssign.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "PointAssign.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

//---------------------------------------------------------
// Constructor

PointAssign::PointAssign()

{
	k=0;
    m_input_dequ_point.clear();
    m_stop;
    m_size;
    m_last;
}

//---------------------------------------------------------
// Destructor

PointAssign::~PointAssign()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PointAssign::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
  string key = msg.GetKey();
  if (key== "TESTING")
	  cout << "hello"<<endl;
  if (key== "VISIT_POINT")
  {

      stringstream point_in_ss;
      string point_in_string;
      point_in_ss << msg.GetString();
      point_in_ss >> point_in_string;
    
      
      m_input_dequ_point.push_back(point_in_string);
      m_size = m_input_dequ_point.size();
      Notify ("POINT_NUM", m_size);
  }
    
      
#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PointAssign::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PointAssign::Iterate()
{
	k=k+1;
	Notify("PUB_TEST",k);
    
    
    int i;
    int r;
    Notify("STOP", m_stop++); 
    string tmp_num;


   // cout << m_input_dequ_point.back();
   // Notify("DEQU_SIZE_2",m_input_dequ_point.back());
    
    if(!m_input_dequ_point.empty())
    {   
        m_last = m_input_dequ_point.back(); 
        Notify("LAST", m_last);
        if (m_last == "lastpoint")
        {
           

            m_input_dequ_point.pop_front();
            m_input_dequ_point.pop_back();
        
            Notify("SIZE",m_input_dequ_point.size());
      
            for (i=1;i<=m_size-2;i++){
                Notify("I", i);         
                tmp_num = m_input_dequ_point.front();
                r=i%2;

                if (r == 1)
                {   
                    // m_odd.push_back(tmp_num);
                    Notify("VISIT_POINT_ONE",tmp_num);
                    m_input_dequ_point.pop_front();
                }
                else
                {
                    // m_even.push_back(tmp_num);
                    Notify("VISIT_POINT_TWO",tmp_num);
                    m_input_dequ_point.pop_front();
                }
            }    
    
        }
       
    }

//    cout << "even number= " << m_even.size() << endl;
//    string a;
//    a=m_input_dequ_point.front();
//    string rand="true";
//    
        //for (int i=1; i<=m_odd.size(); i++)
        //{
        //    Notify("VISIT_POINT_HENRY", m_odd.front());
        //    m_odd.pop_front();
        //}

        //for (int i=1; i<=m_even.size(); i++)
        //{
        //    Notify("VISIT_POINT_GILDA", m_even.front());
        //    m_even.pop_front();
        //}
    

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PointAssign::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      
      if(param == "foo") {
        //handled
      }
      else if(param == "bar") {
        //handled
      }

      //choose method
//      else if(param == "method"){
//        if (value == "odd_and_even")
//            m_method = 1;
        
//      }
    }
  }

  //set condition to trigger uTimerscript
  string rand="true";
  Notify("RAND_START",rand);  

  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void PointAssign::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("TESTING",0);
  Register("VISIT_POINT",0);
}

//---------------------------------------------------------
// Procedure: postViewPoint

//void PointAssign::postViewPoint(double x, double y, string label, string color)
//{
//  XYPoint point(x, y);
//  point.set_label(label);
//  point.set_color("vertex", color);
//  point.set_param("vertex_size", "2");
//
//  string spec = point.get_spec();
//  Notify("VIEW_POINT", spec);
//}

