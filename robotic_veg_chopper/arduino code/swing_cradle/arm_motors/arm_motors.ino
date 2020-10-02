//slave
#include <Wire.h>
#include <AccelStepper.h>
int motor,pos[3];
String inString="";
int a,b, auto_mode=0;
AccelStepper stepper1(1, 3,2); // driver, step, dir
AccelStepper stepper2(1, 5,4); //
AccelStepper stepper3(1, 7,6); //

void setup() {
   Wire.begin(9); 
  Wire.onReceive(receiveEvent);
  //Serial.begin(9600);
  stepper1.setMaxSpeed(1500.0);
  stepper1.setAcceleration(500.0);
  stepper1.setCurrentPosition(180*21.33);
  
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(200.0);
  stepper2.setCurrentPosition(180*21.33);
  
  stepper3.setMaxSpeed(1000.0);
  stepper3.setAcceleration(200.0); 
  stepper3.setCurrentPosition(180*21.33); 

}

void loop() {
  stepper1.run();
  stepper2.run();
  stepper3.run();
  

  if (auto_mode==1 && stepper1.currentPosition()== (5930) && stepper2.currentPosition()== (5930)) //  5610=263*21.33   5930=278*21.33   
  {
    stepper1.setMaxSpeed(1500.0);
    stepper1.setAcceleration(1000.0); 
    stepper1.moveTo(4735);//222
    stepper1.run();
    while(auto_mode==1)
    {
      if (stepper1.currentPosition()== (4735))
        stepper1.moveTo(4202);//197
      if (stepper1.currentPosition()== (4202))
        stepper1.moveTo(4735);

      stepper1.run();
    }   
  }
}


void receiveEvent() {
 
  for(int i=0;i<3;i++)
  {
    a = Wire.read();
    b = Wire.read();
    pos[i]= (b<<8)|a;
  }

  if(pos[0]==400)
  {
    auto_mode=1;
    stepper1.moveTo(5930);//278
    stepper2.moveTo(5930);//278
    stepper3.moveTo(1740);//81.6
  }
  else
  {
    auto_mode=0;
  }

  if(auto_mode==0)
  {
    stepper1.moveTo(pos[0]*21.33);
    stepper2.moveTo(pos[1]*21.33);
    stepper3.moveTo(pos[2]*21.33);
  }
}
