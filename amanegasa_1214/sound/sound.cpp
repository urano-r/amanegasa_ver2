// -*- C++ -*-
/*!
 * @file  sound.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "sound.h"

// Module specification
// <rtc-template block="module_spec">
static const char* sound_spec[] =
  {
    "implementation_id", "sound",
    "type_name",         "sound",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Roma.u",
    "category",          "amanegasa",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.sound1", "523",
    "conf.default.sound2", "587",
    "conf.default.sound3", "659",
    "conf.default.sound4", "698",
    "conf.default.sound5", "783",
    "conf.default.sound6", "880",
    "conf.default.sound7", "987",
    "conf.default.sound8", "1046",
    // Widget
    "conf.__widget__.sound1", "text",
    "conf.__widget__.sound2", "text",
    "conf.__widget__.sound3", "text",
    "conf.__widget__.sound4", "text",
    "conf.__widget__.sound5", "text",
    "conf.__widget__.sound6", "text",
    "conf.__widget__.sound7", "text",
    "conf.__widget__.sound8", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */

unsigned int step = 0;
double frequency = 0;
double delayTime = 0;
	
sound::sound(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_patternIn("pattern", m_pattern),
    m_delayTimeOut("delayTime", m_delayTime)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
sound::~sound()
{
}



RTC::ReturnCode_t sound::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("pattern", m_patternIn);
  
  // Set OutPort buffer
  addOutPort("delayTime", m_delayTimeOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("sound1", m_sound1, "523");
  bindParameter("sound2", m_sound2, "587");
  bindParameter("sound3", m_sound3, "659");
  bindParameter("sound4", m_sound4, "698");
  bindParameter("sound5", m_sound5, "783");
  bindParameter("sound6", m_sound6, "880");
  bindParameter("sound7", m_sound7, "987");
  bindParameter("sound8", m_sound8, "1046");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t sound::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sound::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sound::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t sound::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sound::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sound::onExecute(RTC::UniqueId ec_id)
{

	if(m_patternIn.isNew()){
		m_patternIn.read();
		step++;
		if(m_pattern.data == 1){
			frequency = m_sound1;
		}else if(m_pattern.data == 2){
			frequency = m_sound2;
		}else if(m_pattern.data == 3){
			frequency = m_sound3;
		}else if(m_pattern.data == 4){
			frequency = m_sound4;
		}else if(m_pattern.data == 5){
			frequency = m_sound5;
		}else if(m_pattern.data == 6){
			frequency = m_sound6;
		}else if(m_pattern.data == 7){
			frequency = m_sound7;
		}else if(m_pattern.data == 8){
			frequency = m_sound8;
		}else{
			frequency = 9;
		}

		if(frequency != 9){
			delayTime = (1000000 / frequency) / 2;
		}else{
			delayTime = 0;
		}
		m_delayTime.data = delayTime;
		m_delayTimeOut.write();
		std::cout << "step = " << step << std::endl;
		std::cout << "pattern = " << m_pattern.data << std::endl;
		std::cout << "frequency = " << frequency << std::endl;
		std::cout << "-----------------------------------" << std::endl << std::endl;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sound::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sound::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t sound::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t sound::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t sound::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void soundInit(RTC::Manager* manager)
  {
    coil::Properties profile(sound_spec);
    manager->registerFactory(profile,
                             RTC::Create<sound>,
                             RTC::Delete<sound>);
  }
  
};


