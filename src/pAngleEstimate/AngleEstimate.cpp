/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: AngleEstimate.cpp                                        */
/*    DATE:                                                 */
/************************************************************/









#include <iterator>
#include "MBUtils.h"
#include "AngleEstimate.h"
using namespace std;

//---------------------------------------------------------
// Constructor

AngleEstimate::AngleEstimate()
{
    i=0;
    m_data_deq.clear();
}

//---------------------------------------------------------
// Destructor

AngleEstimate::~AngleEstimate()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool AngleEstimate::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();



//    if(key == "ESTIMATE") {
//        estimateAngle(msg.GetString());
//    }
    if(key == "UCTD_MSMNT_REPORT"){
        m_msmnt_report = msg.GetString();
        m_data_deq.push_back( m_msmnt_report );
        std::string data_test = m_data_deq.back();
        Notify("DATA",data_test);
    }
    else if(key == "COLLECT"){
        m_collect = msg.GetString();
    }
    else if(key == "RETURN2EXCHANGE"){
        m_exchange = msg.GetString();
    
    }
    if (m_exchange=="true"){
        exchange();
    }
    else if (m_collect=="estimating"){
        estimateAngle(m_collect);
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

bool AngleEstimate::OnConnectToServer()
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

bool AngleEstimate::Iterate()
{
    
    if(m_collect!="start"){
        m_data_deq.clear();
    } 
    else 
       m_data_deq.push_back(m_collect_data); 

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool AngleEstimate::OnStartUp()
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
      else if (param == "node"){
        m_node = value;
        return true;
      }
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void AngleEstimate::RegisterVariables()
{
  // Register("FOOBAR", 0);
  Register("COLLECT", 0);
//  Register("ESTIMATE", 0);

  Register("UCTD_MSMNT_REPORT", 0);
}

//-------------------------------------------------------
// process Data
// ------------------------------------------------------
void AngleEstimate::estimateAngle(string m_collect)
{
    if(m_collect=="estimating" || !m_data_deq.empty()){
      
      struct data{
        string vname;
        double x;
        double y;
        double temp;
      };
      
      std::deque<data> processed_data_deq;
      for(int j=0;j<m_data_deq.size();j++){
          string orig = m_data_deq.front();         
          string vname_s = tokStringParse(orig, "vname", ',', '=');
          string x_s = tokStringParse(orig, "x", ',', '=');
          string y_s = tokStringParse(orig, "y", ',', '=');
          string temp_s = tokStringParse(orig, "temp", ',', '=');
          
          data D;
          stringstream ss;
          ss<<vname_s;ss>>D.vname;ss.clear();
          ss<<x_s;ss>>D.x;ss.clear();
          ss<<y_s;ss>>D.y;ss.clear();
          ss<<temp_s;ss>>D.temp;ss.clear();
    
          Notify("TEMP", D.temp) ;
          processed_data_deq.push_back(D);
          m_data_deq.pop_front();
      }
      double temp_min=1000;
      double temp_max=0;
      deque<data>::iterator j;
      for(j=processed_data_deq.begin();j!=processed_data_deq.end();j++){
        if(j->temp > temp_max){
         temp_max = j->temp;
        }
        if(j->temp < temp_min){
         temp_min = j->temp;
        }
      }

      double thres = 0.5;
      double temp_mid = (temp_max+temp_min)/2;
      double sum_x;
      double sum_y;
      int count=0;
      vector<double> x_vec;
      vector<double> y_vec;
E:
      x_vec.clear();
      y_vec.clear();
      for(j=processed_data_deq.begin();j!=processed_data_deq.end();j++){
          if(abs(j->temp-temp_mid) < thres){
              sum_x += j->x;
              sum_y += j->y;
              count++;     
          }
          else if (abs(j->temp-temp_mid)>=thres && count > 0){
            x_vec.push_back(sum_x/count);
            y_vec.push_back(sum_y/count);
            count = 0;
            sum_y = 0;
            sum_x = 0;
          }
      }

      if(x_vec.size()==2){
        m_theta_vec.push_back(tan(abs(y_vec.at(1)-y_vec.at(2))/abs(x_vec.at(1)-x_vec.at(2))));
      }
      else{
        thres+=0.1;
        goto E;
      }  
    }
}

void AngleEstimate::exchange(){
    double theta=0;
    for(int i=0;i<m_theta_vec.size();i++){
        theta += m_theta_vec.at(i);
    }
    theta /= m_theta_vec.size();
    stringstream ss;
    string s;
    ss<<"src_node="<<m_node<<",dest_node=all,var_name=THETA_REPORT,string_val="<<theta;
    ss>>s;ss.clear();
    Notify("EXCHANGE_IN","true");
    Notify("NODE_MESSAGE_LOCAL", s);

}
