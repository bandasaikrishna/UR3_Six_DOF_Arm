#include <ros.h>
#include <rospy_tutorials/Floats.h>
//#include <three_dof_planar_manipulator/Floats_array.h>
#include <Servo.h> 
#include <Wire.h>

#define slave1 9
#define slave2 10
ros::NodeHandle  nh;

void servo_cb( const rospy_tutorials::Floats& cmd_msg){
  //nh.loginfo("Command Received ");
  
  int new_pos[6]={cmd_msg.data[0],cmd_msg.data[1],cmd_msg.data[2],cmd_msg.data[3],cmd_msg.data[4],cmd_msg.data[5]};
  //int new_pos[3]={cmd_msg.data[0],cmd_msg.data[1],cmd_msg.data[2]};
  
  int i=0,j=0;
  uint8_t buffer[6]={0,0,0,0,0,0};
  
  for(i=0,j=0;i<3;i++)
  {  
    buffer[j++]=new_pos[i];
    buffer[j++]=new_pos[i] >> 8;
  }
  
  Wire.beginTransmission(slave1);
  Wire.write(buffer,6);
  Wire.endTransmission();
  
  for(i=3,j=0;i<6;i++)
  { 
    buffer[j++]=new_pos[i];
    buffer[j++]=new_pos[i] >> 8;
  }
  Wire.beginTransmission(slave2);
  Wire.write(buffer,6);
  Wire.endTransmission();
  
}

/*void callback(const three_dof_planar_manipulator::Floats_array::Request & req, three_dof_planar_manipulator::Floats_array::Response & res)
{
  // Simulate function running for a non-deterministic amount of time
  

  res.res_length=6;
  Wire.requestFrom(slave1, 9); //3 bytes for each joint    
  while (Wire.available()) { // slave may send less than requested
    char c[9] = Wire.read();
  res.res[0]=0;//read from slave1;
  res.res[1]=0;//read from slave1;
  res.res[2]=0;//read from slave1;

  Wire.requestFrom(slave2, 9); //3 bytes for each joint    
  while (Wire.available()) { // slave may send less than requested
    char c[9] = Wire.read();
  res.res[3]=0;//read from slave2;
  res.res[4]=0;//read from slave2;
  res.res[5]=0;//read from slave2;
  
  return;
  
}*/



ros::Subscriber<rospy_tutorials::Floats> sub("/joints_to_aurdino",servo_cb);
//ros::ServiceServer<three_dof_planar_manipulator::Floats_array::Request, three_dof_planar_manipulator::Floats_array::Response> server("/read_joint_state",&callback);


void setup(){

  nh.initNode();
  nh.subscribe(sub);
  //nh.advertiseService(server);
  Wire.begin(); 
}

void loop(){

  nh.spinOnce();
}

