//slave
#include <Wire.h>
#include <AccelStepper.h>
int motor,pos[3];
String inString="";
int a,b;
AccelStepper stepper1(1, 3,2); // driver, step, dir
AccelStepper stepper2(1, 5,4); //
AccelStepper stepper3(1, 7,6); //

void setup() {
  Wire.begin(9); 
  //Wire.onRequest(requestEvent); 
  Wire.onReceive(receiveEvent);
  //Serial.begin(9600);
  stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(50.0);
  stepper1.setCurrentPosition(180*21.33);
  
  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(50.0);
  stepper2.setCurrentPosition(180*21.33);
  
  stepper3.setMaxSpeed(500.0);
  stepper3.setAcceleration(50.0); 
  stepper3.setCurrentPosition(180*21.33); 
}

void loop() {
  stepper1.run();
  stepper2.run();
  stepper3.run();
  //Serial.println("working");
}

/*void requestEvent() {
  
  // Setup byte variable in the correct size
  byte response[ANSWERSIZE];
  
  // Format answer as array
  for (byte i=0;i<ANSWERSIZE;i++) {
    response[i] = (byte)answer.charAt(i);
  }
  
  // Send response back to Master
  Wire.write(response,sizeof(response));
  
  // Print to Serial Monitor
  Serial.println("Request event");
}*/

void receiveEvent() {
 
  // Read while data received
  for(int i=0;i<3;i++)
  {
    a = Wire.read();
    b = Wire.read();
    pos[i]= (b<<8)|a;
  }
  stepper1.moveTo(pos[0]*21.33);
  stepper2.moveTo(pos[1]*21.33);
  stepper3.moveTo(pos[2]*21.33);
  
  /*Serial.println(pos[0]*21.33);
  Serial.println(pos[1]*21.33);
  Serial.println(pos[2]*21.33);*/
  
}
