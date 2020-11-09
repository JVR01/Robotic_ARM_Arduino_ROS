/* 
 * Joint_Subscriber 2
 * Excecuting the step function from an external function
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
//creating the arrays of motors 
Motor motor[] = {Motor(5, 2, 38.4), Motor(6, 3, 38.4), Motor(7, 4, 1)};




void getdata( const sensor_msgs::JointState& info){
  digitalWrite(LED_BUILTIN, HIGH-digitalRead(LED_BUILTIN));   // blink the led
  jstate[0]=info.position[0];
  jstate[1]=info.position[1];
  jstate[2]=info.position[2];
  jstate[3]=info.position[3];
  nh.logwarn("callBack_executed");
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
  //motor[0].revert(true);
  //motor[1].revert(true);
  
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(chatter);
}

void moveToGoal()
{

  //if(motor[0].goal_reached()*motor[1].goal_reached()==false){}
  //else {nh.logwarn("nothing to move");}
  
  bool missionCompleted = motor[0].goal_reached()*motor[1].goal_reached();
  
  while(missionCompleted == false){
    
    for (int i=0; i<=1; i++){


         if(motor[i].goal_reached()==false /*&& missionCompleted == false*/){  
           
           //----motor[i].step_ONE();
           motor[i].step_RATIO();
           //char msg[10];
           //String message =  String(abs(diff));
           //String message =  String(motor[i].motorPosition());
           //String message =  String(motor[i].step_diff()); message.toCharArray(msg, 10);
           //nh.logwarn(msg);
            //message =  String(motor[i].step_goal());message.toCharArray(msg, 10);nh.logwarn(msg);
            //message =  String(motor[i].step_actual());message.toCharArray(msg, 10);nh.logwarn(msg); 
            //message =  String(motor[i].motorPosition());message.toCharArray(msg, 10);nh.logwarn(msg);
            //message =  String(jstate[i]);message.toCharArray(msg, 10);nh.logwarn(msg);
            //message =  String(jstate[i]-motor[i].motorPosition());message.toCharArray(msg, 10);nh.logwarn(msg);
           
           if(i==0){nh.logwarn("MotorPosition_1");}
           else if(i ==1){nh.logwarn("MotorPosition_2");}
           log_float(motor[i].motorPosition());
           //nh.logwarn(msg);

          }
          
         else {
           nh.logwarn("completedddd-----------------------ddddddddddd");
           } 
         missionCompleted = motor[0].goal_reached()*motor[1].goal_reached();
         if(missionCompleted){nh.logwarn("somehow mission completed  ###################");
           log_float(motor[0].get_debt_steps());
            }
           //delay(5000);}
      }
    
    //missionCompleted = motor[0].goal_reached()*motor[1].goal_reached();
    
    }
    nh.logwarn("nothing to move"); 
    log_float(motor[0].motorPosition());
    log_float(motor[1].motorPosition());
    //char msg[10]; String message =  String(motor[0].motorPosition());message.toCharArray(msg, 10);nh.logwarn(msg);
}

void loop()
{  
  
 /*mydata.data = jstate[0];*/
 nh.spinOnce(); 
 
  
 if (T == true){ 
    T = false; 
    //chatter.publish( &mydata );
      
    for(int i=0; i<=1; i++){
        float diff = jstate[i]-motor[i].motorPosition();
        //motor[i].set_executed(true);
        motor[i].moveONE(diff);

        mydata.data = motor[i].motorPosition();
        chatter.publish( &mydata );
    } 
    nh.logwarn("goal_set"); 
   
    moveToGoal();      
  }
    
  
}

void log_float(float input)
{
  char result[8];
  nh.logwarn(dtostrf(input, 6, 3, result));
}
