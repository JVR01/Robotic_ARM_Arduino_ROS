class Motor {
 private:
    int dirPin;
    int stepPin;
    double ratio;
    int stps=800;
  
    long totalsteps = stps*ratio;
    float motorPosition;
    float input = 0;

    int delayTime=140;
    double angle = 0.0;

  //double ratioY = 38.4;
  
    bool executed = true;
 


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
   if (input>=0){dir=true;}
   else if (input<0){dir=false;}
  
   totalsteps = round(stps*ratio*abs(input)/(2*3.1416)) ;
 
   if ( executed == true ){  
    
      step(dir, dirPin, stepPin, totalsteps );
    
      motorPosition = motorPosition + input; 
      executed = false;
      char number[20] = "dog";
      String(motorPosition).toCharArray(number, 10);
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
    //nh.spinOnce();

  }
  //nh.logwarn("I did move the motors");
  Serial.print("I did move the motor: " );
  Serial.println(steps);
  }

  //class end
};
