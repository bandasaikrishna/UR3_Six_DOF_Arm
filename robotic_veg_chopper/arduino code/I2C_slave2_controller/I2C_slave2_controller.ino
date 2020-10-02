//slave
#include <Wire.h>
#include <AccelStepper.h>
int motor,pos[3];
String inString="";
int a,b;
AccelStepper stepper4(1, 3,2); // driver, step, dir
AccelStepper stepper5(1, 5,4); //
AccelStepper stepper6(1, 7,6); //

void setup() {
  Wire.begin(10); 
  //Wire.onRequest(requestEvent); 
  Wire.onReceive(receiveEvent);
  //Serial.begin(9600);
  stepper4.setMaxSpeed(200.0);
  stepper4.setAcceleration(50.0);
  stepper4.setCurrentPosition(180*5.12);
  
  stepper5.setMaxSpeed(200.0);
  stepper5.setAcceleration(50.0);
  stepper5.setCurrentPosition(180*5.12);
  
  stepper6.setMaxSpeed(200.0);
  stepper6.setAcceleration(50.0);  
  stepper6.setCurrentPosition(180*5.12);
}

void loop() {
  stepper4.run();
  stepper5.run();
  stepper6.run();
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
  stepper4.moveTo(pos[0]*5.12);
  stepper5.moveTo(pos[1]*5.12);
  stepper6.moveTo(pos[2]*5.12);
  /*Serial.println(pos[0]*5.12);
  Serial.println(pos[1]*5.12);
  Serial.println(pos[2]*5.12);*/
  
}
