#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
import sys, select, termios, tty

rospy.init_node('cmd_vel_publisher')

cmd_vel_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)

MAX_LINEAR_SPEED = 2  # m/s
MAX_ANGULAR_SPEED = 4  # rad/s

settings = termios.tcgetattr(sys.stdin)

def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

last_time = rospy.Time.now()
last_key = ''
timeout = 20 

try:

    while not rospy.is_shutdown():
        key = getKey()
        if key != '':
            last_time = rospy.Time.now()
            last_key = key
        else:

            if (rospy.Time.now() - last_time).to_sec() < timeout:
                key = last_key
            else:
                key = ''

        twist = Twist()
        if key == 'w':
            twist.linear.x =  twist.linear.x + 10
        elif key == 's':
            twist.linear.x =  twist.linear.x - 10
        elif key == 'a':
            twist.linear.x =  twist.linear.x + 10
            twist.angular.z = twist.angular.z + 10
        elif key == 'd':
            twist.linear.x =  twist.linear.x - 10
            twist.angular.z = twist.angular.z - 10
        else:
            twist.linear.x = 0.0
            twist.angular.z = 0.0

        cmd_vel_pub.publish(twist)
 
        if key == 'q':
            break

except Exception as e:
    print(e)

finally:
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)














# try:

#     print("w/a/s/d")
#     print("q=exit")
    
#     while True:
#         key = getKey()
#         if key == 'w':
#             linear_speed = MAX_LINEAR_SPEED
#             angular_speed = 0.0
#         elif key == 's':
#             linear_speed = -MAX_LINEAR_SPEED
#             angular_speed = 0.0
#         elif key == 'a':
#             linear_speed = 0.0
#             angular_speed = MAX_ANGULAR_SPEED
#         elif key == 'd':
#             linear_speed = 0.0
#             angular_speed = -MAX_ANGULAR_SPEED
#         else:
#             linear_speed = 0.0
#             angular_speed = 0.0


#         twist = Twist()
#         twist.linear.x = linear_speed
#         twist.angular.z = angular_speed

#         cmd_vel_pub.publish(twist)

#         if key == 'q':
#             break
# except Exception as e:
#     print(e)

# finally:
#     # Reset terminal settings
#     termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
