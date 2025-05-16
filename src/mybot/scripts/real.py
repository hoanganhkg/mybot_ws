#!/usr/bin/env python
import rospy
from gazebo_msgs.msg import ModelStates
from geometry_msgs.msg import Twist, Pose2D
import tf.transformations as tft
import math

class DynamicGoalController:
    def __init__(self):
        rospy.init_node('dynamic_goal_controller')
        self.ROBOT_NAME = "st"
        self.cmd_vel_pub = rospy.Publisher('/Diff_Drive/diff_drive_controller/cmd_vel', Twist, queue_size=10)
        rospy.Subscriber('/gazebo/model_states', ModelStates, self.model_states_callback)
        # rospy.Subscriber('/goal_pose', Pose2D, self.goal_callback)

        self.sub_odom = rospy.Subscriber("odom_2", Odometry, self.on_odom_callback) #IMU
        self.sub_gps = rospy.Subscriber("odom_1", Odometry, self.on_pos_callback) #GPS

        self.current_x = 0.0
        self.current_y = 0.0
        self.current_theta = 0.0

        self.goal_x = None
        self.goal_y = None
        self.goal_theta = None

        self.LINEAR_SPEED = 0.5
        self.ANGULAR_SPEED = 1.0
        self.POS_TOLERANCE = 0.3 
        self.YAW_TOLERANCE = math.radians(5) 
        self.MIN_ANGULAR_SPEED = 0.2  

    def model_states_callback(self, msg):
        try:
            index = msg.name.index(self.ROBOT_NAME)
            pose = msg.pose[index]
            self.current_x = pose.position.x
            self.current_y = pose.position.y
            _, _, self.current_theta = self.euler_from_quaternion(
                pose.orientation.x, pose.orientation.y,
                pose.orientation.z, pose.orientation.w
            )
        except ValueError:
            pass
    def on_pos_callback(self, msg):
        self.goal_x = msg.position.x
        self.goal_y = msg.position.y

    def on_odom_callback(self, msg):
        self.goal_theta = msg.heading

    # def goal_callback(self, msg):
    #     self.goal_x = msg.x
    #     self.goal_y = msg.y
    #     self.goal_theta = msg.theta

    def euler_from_quaternion(self, x, y, z, w):
        return tft.euler_from_quaternion([x, y, z, w])

    def normalize_angle(self, angle):
        return (angle + math.pi) % (2 * math.pi) - math.pi

    def distance(self, x1, y1, x2, y2):
        return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

    def run(self):
        rate = rospy.Rate(10)
        while not rospy.is_shutdown():
            if self.goal_x is None:
                rospy.loginfo_throttle(2, "Waiting for goal pose...")
                rate.sleep()
                continue

            rospy.loginfo("Current: ({:.2f}, {:.2f}), Goal: ({:.2f}, {:.2f}), Heading: {:.2f}".format(
             self.current_x, self.current_y, self.goal_x, self.goal_y, self.current_theta))

            twist = Twist()

            dist = self.distance(self.current_x, self.current_y, self.goal_x, self.goal_y)
            heading = math.atan2(self.goal_y - self.current_y, self.goal_x - self.current_x)
            heading_error = self.normalize_angle(heading - self.current_theta)

            if dist > self.POS_TOLERANCE:
                twist.linear.x = min(self.LINEAR_SPEED, dist)
                twist.angular.z = self.ANGULAR_SPEED * heading_error
            else:
                yaw_error = self.normalize_angle(self.goal_theta - self.current_theta)

                if abs(yaw_error) > self.YAW_TOLERANCE:
                    twist.angular.z = self.ANGULAR_SPEED * yaw_error
                else:
                    twist.angular.z = 0.0
                    rospy.loginfo("Goal reached with correct orientation!")

            self.cmd_vel_pub.publish(twist)
            rate.sleep()

if __name__ == '__main__':
    controller = DynamicGoalController()
    controller.run()
