#!/usr/bin/env python

import rospy


from sensor_msgs.msg import JointState
from rospy_tutorials.msg import Floats
import math

def cb(msg):
    x=Floats()
    x.data.append(180+(math.degrees(msg.position[0])))
    x.data.append(180+(math.degrees(msg.position[1])))
    x.data.append(180+(math.degrees(msg.position[2])))
    
    x.data.append(180+(math.degrees(msg.position[3])))
    x.data.append(180+(math.degrees(msg.position[4])))
    x.data.append(180+(math.degrees(msg.position[5])))
    #rospy.sleep(1/2)
    pub.publish(x)
    


rospy.init_node('Joints_to_aurdino')

pub = rospy.Publisher('/joints_to_aurdino', Floats, queue_size=1)

sub = rospy.Subscriber('/joint_states', JointState, cb, queue_size=1)

rospy.spin()

