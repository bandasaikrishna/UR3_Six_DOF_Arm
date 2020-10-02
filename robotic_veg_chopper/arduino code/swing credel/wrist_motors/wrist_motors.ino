//slave2
#include <Wire.h>
#include <AccelStepper.h>
int motor,pos[3];
String inString="";
int a,b, auto_mode=0;
AccelStepper stepper4(1, 3,2); // driver, step, dir
AccelStepper stepper5(1, 5,4); //
AccelStepper stepper6(1, 7,6); //

void setup() {
  Wire.begin(10);  
  Wire.onReceive(receiveEvent);
  stepper4.setMaxSpeed(1000.0);
  stepper4.setAcceleration(200.0);
  stepper4.setCurrentPosition(180*5.12);
  
  stepper5.setMaxSpeed(1000.0);
  stepper5.setAcceleration(200.0);
  stepper5.setCurrentPosition(180*5.12);
  
  stepper6.setMaxSpeed(1000.0);
  stepper6.setAcceleration(200.0); 
  stepper6.setCurrentPosition(180*5.12); 
}

void loop() {
  stepper4.run();
  stepper5.run();
  stepper6.run();
}

void receiveEvent() {
 
  // Read while data received
  for(int i=0;i<3;i++)
  {
    a = Wire.read();
    b = Wire.read();
    pos[i]= (b<<8)|a;
  }
  
  if(pos[0]==400)
  {
    auto_mode=1;
    //stepper4.moveTo(0);//yet to decide
    stepper5.moveTo(189);
    //stepper6.moveTo(0);
  }
  else
  {
    auto_mode=0;
  }
   
  if(auto_mode==0)
  {
    stepper4.moveTo(pos[0]*5.12);
    stepper5.moveTo(pos[1]*5.12);
    stepper6.moveTo(pos[2]*5.12);
  } 
}
