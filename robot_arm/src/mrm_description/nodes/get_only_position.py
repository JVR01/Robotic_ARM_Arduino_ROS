#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from std_msgs.msg import Float64
from std_msgs.msg import Empty
from sensor_msgs.msg import JointState

from std_msgs.msg import Float64MultiArray


pub_range = rospy.Publisher('toggle_led', Empty, queue_size=10)
pub = rospy.Publisher('position_joints', Float64MultiArray, queue_size=10)


def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.position)
    rate = rospy.Rate(1)
    rospy.loginfo("I heard %s", data.position)

    #Float64[] vector = data.position
    pub_range.publish(Empty())
    #for x in fruits:
    array = []
    array = data.position
    vector = Float64MultiArray(data=array)   
    #rate = rospy.Rate(10)
    #while not rospy.is_shutdown():
        
    pub.publish(vector)
    rospy.loginfo("nixxx")
        #rate.sleep() 
    #rate = rospy.Rate(1)
        
    
    rospy.sleep(0.1)

def listener():

    rospy.init_node('get_only_position', anonymous=True)

    rospy.Subscriber("/joint_states",JointState, callback)

    #rostopic pub toggle_led std_msgs/Empty --once
    rospy.spin()

if __name__ == '__main__':
    listener()



####erase_from_Here

#!/usr/bin/env python
"""
import rospy
import tf
import math
import numpy
from geometry_msgs.msg import Vector3
from sensor_msgs.msg import LaserScan, Range

rospy.init_node('sonar_to_laser_node')

# buffer
b1 = 0.0
b2 = 0.0
b3 = 0.0

pub = rospy.Publisher('car/scan', LaserScan, queue_size=10)
pub_range = rospy.Publisher('car/range', Range, queue_size=10)
#pub_range = rospy.Publisher('sensor/sonar_front', Range, queue_size=10)



def callback(msg):

	# buffer for rejecting false range data
	global b1, b2, b3
	b1 = b2
	b2 = b3
	b3 = msg.z / 100

	# wait to have more non null ranges before publishing
	if b1 > 0.0 and b2 > 0.0 and b3 > 0.0:

		Scan_msg.ranges = [msg.z / 100]
		Range_msg.range = msg.z / 100
		Scan_msg.header.stamp = rospy.Time.now()
		Range_msg.header.stamp = rospy.Time.now()
		pub.publish(Scan_msg)
		pub_range.publish(Range_msg)

	# publish 0.0 (could be false measuremet)
	else:

		Scan_msg.ranges = [0.0]
		Range_msg.range = 0.0
		Scan_msg.header.stamp = rospy.Time.now()
		Range_msg.header.stamp = rospy.Time.now()
		pub.publish(Scan_msg)
		pub_range.publish(Range_msg)


#sub = rospy.Subscriber('car/power', Vector3, callback)
sub = rospy.Subscriber('sensor/sonar_front', Range, callback)
rospy.spin()

"""
