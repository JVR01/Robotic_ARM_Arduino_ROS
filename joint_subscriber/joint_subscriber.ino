/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
//#include <std_msgs/Empty.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include "Motor.h"
ros::NodeHandle  nh;

//creating the message
//--sensor_msgs::JointState jstate;
float jstate;
bool T = false;
Motor motor1 = Motor(5, 2, 38.4);

//creating the arrays for the message
//char name[] = {"motor_1", "motor_2"};
//char NAME ="wellcome";
//float vel[]={0,0};
//float pos[]={0,0};
//float eff[]={0,0};

void getdata( const sensor_msgs::JointState& info){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
  
  //--jstate.position=info.position;
  jstate=info.position[0];
  nh.logwarn("Warnings.");
  T = true;
}

std_msgs::Float64 mydata;
ros::Subscriber<sensor_msgs::JointState> sub("joint_states", &getdata );
ros::Publisher chatter("chatter", &mydata);

void setup()
{ 
  pinMode(LED_BUILTIN, OUTPUT);
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}

void loop()
{  
  /*while (!nh.connected())
  {
    nh.spinOnce();
  }*/
  //--mydata.data = jstate.position[1];
  mydata.data = jstate;
  //chatter.publish( &mydata );
  nh.spinOnce();
  if (T == true){ T = false; chatter.publish( &mydata );}
  delay(5);
  
}
