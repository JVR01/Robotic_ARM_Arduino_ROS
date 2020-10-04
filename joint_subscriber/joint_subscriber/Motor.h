class Motor {
 private:
    int dirPin;
    int stepPin;
    double ratio;
    int stps=800;
  
    long totalsteps = stps*ratio;
    float motorPosition_;
    float input = 0;

    int delayTime=140;
    double angle = 0.0;

  //double ratioY = 38.4;
  
    bool executed = true;
    bool revert_ = false;


 public:
  Motor (int dirPin, int stepPin, double ratio) {
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->ratio = ratio;

    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
       
  }

 void move(float input){
   bool dir;    
   if (input>=0){dir=false;}
   else if (input<0){dir=true;}
   
   if (revert_== true){dir = !dir;}
   
   totalsteps = round(stps*ratio*abs(input)/(2*3.1416)) ;
 
   if ( executed == true ){  
    
      step(dir, dirPin, stepPin, totalsteps );
    
      motorPosition_ = motorPosition_ + input; 
      executed = false;
      //char number[20] = "dog";
      //String(motorPosition_).toCharArray(number, 10);
  }

 }
 
 void step(boolean dir, byte dirPin, byte stepperPin, int steps){
  digitalWrite(dirPin, dir);
  
  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime); 

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime); 
    

  }
  
  }

  float motorPosition(){
    return motorPosition_;
    
    }
  void set_executed(bool value){
    executed = value;
    
    }
    
 void revert(bool value){
    revert_ = value;
    //return revert_;
    }
  //class end
};
