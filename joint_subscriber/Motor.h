class Motor {
 private:
    int dirPin;
    int stepPin;
    double ratio;
    double ratio_decimal;
    double debt_steps;
    int stps=800;
  
    unsigned long  totalsteps_goal;
    unsigned long  totalsteps_actual;
    float motorPosition_ = 0;
    float input_ = 0;

    int delayTime=140;
    double angle = 0.0;
    
    bool goal_reached_ = true;
    bool executed = true;
    bool revert_ = false;
    bool dir;

 public:
  Motor (int dirPin, int stepPin, double ratio) {
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->ratio = ratio;

    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);

    ratio_decimal = ratio-round(ratio);
       
  }

 

void moveONE(float input){

   input_ = input;
   //set direction of rotation    
   if (input>=0){dir=false;}
   else if (input<0){dir=true;}

   //reverse the motor
   if (revert_== true){dir = !dir;}
   
   ///calculated the steps a motor has to move to reach goal
   totalsteps_goal = round(stps*ratio*abs(input)/(2*3.1416)) ;

   totalsteps_actual = 0;
   if(totalsteps_goal>0){goal_reached_ = false;}
   
}

 
void stepONE(boolean dir, byte dirPin, byte stepperPin){

  
  if (input_>0){motorPosition_ = motorPosition_ + (2*3.1416/(800*ratio));}
  else if (input_<0){motorPosition_ = motorPosition_ - (2*3.1416/(800*ratio));}
  
  digitalWrite(dirPin, dir);
  digitalWrite(stepperPin, HIGH);
  delayMicroseconds(delayTime); 
  digitalWrite(stepperPin, LOW);
  //delayMicroseconds(delayTime);

  totalsteps_actual = totalsteps_actual + 1; 
   
  if(totalsteps_actual >= totalsteps_goal){goal_reached_ = true;totalsteps_actual=0;}
       
}

void step(boolean dir, byte dirPin, byte stepperPin){

  //for (int i = 0; i < round(ratio); i++) {
  for (int i = 0; i < 20; i++) {
     if (input_>0){motorPosition_ = motorPosition_ + (2*3.1416/(800*ratio));}
     else if (input_<0){motorPosition_ = motorPosition_ - (2*3.1416/(800*ratio));}
  
     digitalWrite(dirPin, dir);
     digitalWrite(stepperPin, HIGH);
     delayMicroseconds(delayTime); 
     digitalWrite(stepperPin, LOW);
     delayMicroseconds(delayTime);
     totalsteps_actual = totalsteps_actual + 1; 
     if(totalsteps_actual >= totalsteps_goal){goal_reached_ = true;totalsteps_actual=0;return;}//??
  }

  debt_steps = debt_steps + ratio_decimal;
  
  /*if(debt_steps >= 1){

    if (input_>0){motorPosition_ = motorPosition_ + (2*3.1416/(800*ratio));}
    else if (input_<0){motorPosition_ = motorPosition_ - (2*3.1416/(800*ratio));}
  
    digitalWrite(dirPin, dir);
    digitalWrite(stepperPin, HIGH);
    delayMicroseconds(delayTime); 
    digitalWrite(stepperPin, LOW);
    delayMicroseconds(delayTime);
    totalsteps_actual = totalsteps_actual + 1; 
    debt_steps = debt_steps-1;
  }*/

  
  if(totalsteps_actual >= totalsteps_goal){goal_reached_ = true;totalsteps_actual=0;}
       
}

  void step_ONE(){
   stepONE(dir, dirPin, stepPin);
  }
  
  void step_RATIO(){
   step(dir, dirPin, stepPin);
  }
  
  float motorPosition(){
    return motorPosition_;
    }
    
  double get_debt_steps(){return debt_steps;}
    
  void set_executed(bool value){
    executed = value;
    }
    
  void revert(bool value){
    revert_ = value;
    }
    
  bool goal_reached(){return goal_reached_;}  

  long step_diff(){return (totalsteps_goal-totalsteps_actual);}
  long step_goal(){return totalsteps_goal;}
  long step_actual(){return totalsteps_actual;}
  
  //class end
};
