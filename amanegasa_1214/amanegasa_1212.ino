
#include <UART.h>
#include <RTno.h>
#include <iostream>


/**
 * This function is called at first.
 * conf._default.baudrate: baudrate of serial communication
 * exec_cxt.periodic.type: reserved but not used.
 */
void rtcconf(config_str& conf, exec_cxt_str& exec_cxt) {
  conf._default.connection_type = ConnectionTypeSerial1;
  // conf._default.connection_type = ConnectionTypeSerial2; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeSerial3; // This configuration is avaiable in Arduino-Mega
  // conf._default.connection_type = ConnectionTypeEtherTcp; // This configuration is avaiable with Ethernet Shield.
  conf._default.baudrate = 57600;
  exec_cxt.periodic.type = ProxySynchronousExecutionContext;
  
  // Configurations Below are configuration parameter for EtherTcp connection.
  // conf._default.port = 23;
  // conf._default.mac_address = MacAddr(0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED);
  // conf._default.ip_address = IPAddr(192,168,42,100);
  // conf._default.subnet_mask = IPAddr(255,255,255,0);
  // conf._default.default_gateway = IPAddr(192,168,42,254);

  // exec_cxt.periodic.type = Timer1ExecutionContext; // onExecute is called by Timer1. Period must be specified by 'rate' option.
  // *caution: TimerOne can not be used with PWM 9, 10.
  // exec_cxt.periodic.rate = 1000; // [Hz] This option is indispensable when type is Timer*ExecutionContext.
}


/** 
 * Declaration Division:
 *
 * DataPort and Data Buffer should be placed here.
 *
 * available data types are as follows:
 * TimedLong
 * TimedDouble
 * TimedFloat
 * TimedLongSeq
 * TimedDoubleSeq
 * TimedFloatSeq
 *
 * Please refer following comments. If you need to use some ports,
 * uncomment the line you want to declare.
 **/

//データポートの宣言
TimedDouble in0;
InPort<TimedDouble> in0In("delayTime", in0);
TimedLong out0;
OutPort<TimedLong> out0Out("val", out0);


//////////////////////////////////////////
// on_initialize
//
// This function is called in the initialization
// sequence when th processor is turned on.
// In on_initialize, usually DataPorts are added.
//
//////////////////////////////////////////
int RTno::onInitialize() {

  //データポートの作成  
  addInPort(in0In);
  addOutPort(out0Out);
  
  // Some initialization (like port direction setting)
  // int LED = 13;
  // pinMode(LED, OUTPUT);
  return RTC_OK; 
}

////////////////////////////////////////////
// on_activated
// This function is called when the RTnoRTC
// is activated. When the activation, the RTnoRTC
// sends message to call this function remotely.
// If this function is failed (return value 
// is RTC_ERROR), RTno will enter ERROR condition.
////////////////////////////////////////////
int RTno::onActivated() {
  // Write here initialization code.
  
  return RTC_OK; 
}

/////////////////////////////////////////////
// on_deactivated
// This function is called when the RTnoRTC
// is deactivated.
/////////////////////////////////////////////
int RTno::onDeactivated()
{
  // Write here finalization code.

  return RTC_OK;
}

//////////////////////////////////////////////
// This function is repeatedly called when the 
// RTno is in the ACTIVE condition.
// If this function is failed (return value is
// RTC_ERROR), RTno immediately enter into the 
// ERROR condition.r
//////////////////////////////////////////////
int RTno::onExecute() {
  
  TCCR1B = 0x01;
  pinMode(5, INPUT);
  
  double delayTime;
  int soundTime;
  
  if(in0In.isNew()) {
    in0In.read();
    delayTime = in0.data;
      
      soundTime = (500000) / (delayTime*2);
     if(delayTime != 0){      
           // アタック
            for(int j=0; j<64; j++){
          
              analogWrite(9, (64/64)*j+(255-64));
              delayMicroseconds(delayTime);
          
              analogWrite(9, 0);
              delayMicroseconds(delayTime);
          
            }  
          
            // ディケイ
            for(int j=0; j<64; j++){
          
              analogWrite(9, 255-(64/64)*j);
              delayMicroseconds(delayTime);
          
              analogWrite(9, 0);
              delayMicroseconds(delayTime);
          
            }  
          
            // リリース
            for(int j=0; j<64; j++){
               for(int i=0; i<10; i++){
          
                analogWrite(9, (255-64)-j);
                delayMicroseconds(delayTime);
          
                analogWrite(9, 0);
                delayMicroseconds(delayTime);
          
            }
          }
       }
    } 
  
  //出力ポートに書き込み
  int buf = analogRead(5);
  out0.data = buf;
  out0Out.write();

  delay(5);  
  return RTC_OK; 
}


//////////////////////////////////////
// on_error
// This function is repeatedly called when
// the RTno is in the ERROR condition.
// The ERROR condition can be recovered,
// when the RTno is reset.
///////////////////////////////////////
int RTno::onError()
{
  return RTC_OK;
}

////////////////////////////////////////
// This function is called when 
// the RTno is reset. If on_reset is
// succeeded, the RTno will enter into
// the INACTIVE condition. If failed 
// (return value is RTC_ERROR), RTno
// will stay in ERROR condition.ec
///////////////////////////////////////
int RTno::onReset()
{
  return RTC_OK;
}

