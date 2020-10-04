/* 
 * rosserial Subscriber Example
 * Blinks an LED on callback
 */

#include <ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>
#include "Motor.h"
ros::NodeHandle  nh;
#define EN        8 

//creating the message
//sensor_msgs::JointState jstate;
float jstate[5];
bool T = false;
//Motor motor1 = Motor(5, 2, 38.4);
//---Motor motor1 = Motor(5, 2, 1);
//creating the arrays of motors 
Motor motor[] = {Motor(5, 2, 1), Motor(6, 3, 1), Motor(7, 4, 1)};






void getdata( const sensor_msgs::JointState& info){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
  jstate[0]=info.position[0];
  jstate[1]=info.position[1];
  jstate[2]=info.position[2];
  jstate[3]=info.position[3];
  nh.logwarn("Warnings.");
  T = true;
}

std_msgs::Float64 mydata;
ros::Subscriber<sensor_msgs::JointState> sub("joint_states", &getdata );
ros::Publisher chatter("chatter", &mydata);

void setup()
{ 
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  motor[1].revert(true);
  
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
  
  mydata.data = jstate[0];
  
  nh.spinOnce();
  
 float diff = jstate[0]-motor[0].motorPosition();
  mydata.data = motor[0].motorPosition();
  //mydata.data = diff;
  if (T == true){ T = false; 
    chatter.publish( &mydata );
    
    //--motor1.set_executed(true);
    //--motor1.move(diff);
    for (int i=0; i<=1; i++){
        float diff = jstate[i]-motor[i].motorPosition();
        motor[i].set_executed(true);
        motor[i].move(diff);
      }
    }
    
    
  delay(5);
  
}
