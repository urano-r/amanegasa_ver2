// -*- C++ -*-
/*!
 * @file  makePattern_v2.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "makePattern_v2.h"

// Module specification
// <rtc-template block="module_spec">
static const char* makepattern_v2_spec[] =
  {
    "implementation_id", "makePattern_v2",
    "type_name",         "makePattern_v2",
    "description",       "ModuleDescription",
    "version",           "1.1.0",
    "vendor",            "Roma.u",
    "category",          "amanegasa",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.num", "8",
    "conf.default.threshold", "0",
    // Widget
    "conf.__widget__.num", "text",
    "conf.__widget__.threshold", "text",
    // Constraints
    ""
  };
// </rtc-template>

int pattern = 0;
unsigned int step = 0;

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
makePattern_v2::makePattern_v2(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_valIn("val", m_val),
    m_patternOut("pattern", m_pattern)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
makePattern_v2::~makePattern_v2()
{
}



RTC::ReturnCode_t makePattern_v2::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("val", m_valIn);
  
  // Set OutPort buffer
  addOutPort("pattern", m_patternOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("num", m_num, "8");
  bindParameter("threshold", m_threshold, "0");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t makePattern_v2::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t makePattern_v2::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t makePattern_v2::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t makePattern_v2::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t makePattern_v2::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t makePattern_v2::onExecute(RTC::UniqueId ec_id)
{
	
	if(m_valIn.isNew()){
		step++;
		m_valIn.read();
		
		int val = abs(m_val.data - 512);
		if(m_val.data > m_threshold){
			pattern = val % m_num;
			m_pattern.data = pattern;
			std::cout << "val is over threshold" << std::endl;
		}else{
			pattern = 9;
		}
		m_patternOut.write();
		std::cout << "step = " << step << std::endl;
		std::cout << "input = " << m_val.data << std::endl;
		std::cout << "val = " << val << std::endl;		
		std::cout << "pattern = " << pattern << std::endl;
		std::cout << "-----------------------------------" << std::endl << std::endl;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t makePattern_v2::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t makePattern_v2::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t makePattern_v2::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t makePattern_v2::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t makePattern_v2::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void makePattern_v2Init(RTC::Manager* manager)
  {
    coil::Properties profile(makepattern_v2_spec);
    manager->registerFactory(profile,
                             RTC::Create<makePattern_v2>,
                             RTC::Delete<makePattern_v2>);
  }
  
};


