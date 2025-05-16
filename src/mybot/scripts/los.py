#!/usr/bin/env python
import rospy
from gazebo_msgs.msg import ModelStates
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import tf.transformations as tft
import matplotlib.pyplot as plt
import numpy as np
import math
import time

class AdaptiveLOSTrajectoryController:
    def __init__(self):
        rospy.init_node('adaptive_los_trajectory_controller')

        self.ROBOT_NAME = "st"
        self.cmd_vel_pub = rospy.Publisher('/Diff_Drive/diff_drive_controller/cmd_vel', Twist, queue_size=10)
        rospy.Subscriber('/gazebo/model_states', ModelStates, self.model_states_callback)

        self.current_x = 0.0
        self.current_y = 0.0
        self.current_theta = 0.0
        self.last_heading_error = 0.0
        self.last_time = None

        self.KP = 2.5
        self.LINEAR_SPEED = 0.52
        self.ANGULAR_SPEED = 1.5
        self.GOAL_RADIUS = 0.5
        self.LOOKAHEAD_DISTANCE = 0.41
        self.MAX_LINEAR_SPEED = 1.0
        self.MAX_ANGULAR_SPEED = 2

        self.waypoints = [(0,0),(7.765,-4.42),(19.68,-12.1),(28.912,3.44),(35.22, 12.78),(39.6, 10.324),(50.53,2.95)]
        self.x_data = []
        self.y_data = []
        self.cte_data = []
        self.angular_data = []
        self.time_data = []
        self.start_time = time.time()
        self.target_heading_data = []


        self.current_waypoint_index = 0

        self.waypoints = self.interpolate_waypoints(self.waypoints, resolution= 0.5, remove_old_waypoints=True)

    def model_states_callback(self, msg):
        try:
            index = msg.name.index(self.ROBOT_NAME)
            position = msg.pose[index].position
            orientation = msg.pose[index].orientation
            _, _, self.current_theta = self.euler_from_quaternion(orientation.x, orientation.y, orientation.z, orientation.w)
            self.current_x = position.x
            self.current_y = position.y
            self.x_data.append(position.x)
            self.y_data.append(position.y)
        except ValueError:
            pass

    def euler_from_quaternion(self, x, y, z, w):
        return tft.euler_from_quaternion([x, y, z, w])

    def distance(self, x1, y1, x2, y2):
        return math.sqrt((x2 - x1)**2 + (y2 - y1)**2)

    def get_heading(self, x1, y1, x2, y2):
        return math.atan2(y2 - y1, x2 - x1)

    def get_lookahead_point(self, x, y, theta, distance):
        return x + distance * math.cos(theta), y + distance * math.sin(theta)

    def normalize_angle(self, angle):
        return (angle + math.pi) % (2 * math.pi) - math.pi

    def interpolate_waypoints(self, waypoints, resolution=1, remove_old_waypoints=False):
        new_waypoints = []
        for i in range(len(waypoints) - 1):
            start_x, start_y = waypoints[i]
            end_x, end_y = waypoints[i + 1]
            dist = self.distance(start_x, start_y, end_x, end_y)
            num_points = int(dist / resolution)
            for j in range(num_points):
                ratio = j / float(num_points)
                interp_x = start_x + ratio * (end_x - start_x)
                interp_y = start_y + ratio * (end_y - start_y)
                new_waypoints.append((interp_x, interp_y))
        new_waypoints.append(waypoints[-1])
        return [waypoints[0]] + new_waypoints[1:-1] + [waypoints[-1]] if remove_old_waypoints else new_waypoints

    def get_cross_track_error(self, px, py, ax, ay, bx, by):
        dx = bx - ax
        dy = by - ay
        apx = px - ax
        apy = py - ay
        cross = dx * apy - dy * apx
        return cross

    def control_adaptive_los(self, goal_x, goal_y):
        x_fake, y_fake = self.get_lookahead_point(self.current_x, self.current_y, self.current_theta, self.LOOKAHEAD_DISTANCE)

        twist = Twist()
        target_heading = self.get_heading(x_fake, y_fake, goal_x, goal_y)
        self.target_heading_data.append(target_heading)
        heading_error = self.normalize_angle(target_heading - self.current_theta)

        current_time = time.time()
        dt = current_time - self.last_time if self.last_time else 0.01
        derivative = (heading_error - self.last_heading_error) / dt if dt > 0 else 0.0

        angular_z = (self.ANGULAR_SPEED * heading_error + self.KP * derivative)
        angular_z = max(min(angular_z, self.MAX_ANGULAR_SPEED), -self.MAX_ANGULAR_SPEED)
        twist.angular.z = angular_z

        dist_to_goal = self.distance(self.current_x, self.current_y, goal_x, goal_y)
        if abs(heading_error) > math.pi / 4:
            twist.linear.x = max(min(self.MAX_LINEAR_SPEED / 2, self.LINEAR_SPEED * dist_to_goal), 0.05)
        else:
            twist.linear.x = max(min(self.MAX_LINEAR_SPEED, self.LINEAR_SPEED * dist_to_goal), 0.05)

        self.last_heading_error = heading_error
        self.last_time = current_time
        self.angular_data.append(self.current_theta)

        if self.current_waypoint_index < len(self.waypoints) - 1:
            ax, ay = self.waypoints[self.current_waypoint_index]
            bx, by = self.waypoints[self.current_waypoint_index + 1]
            cte = self.get_cross_track_error(self.current_x, self.current_y, ax, ay, bx, by)
            self.cte_data.append(cte)
            self.time_data.append(current_time - self.start_time)

        return twist

    def smooth_data(self, data, window_size=5):
        if len(data) < window_size:
            return np.array(data)
        return np.convolve(data, np.ones(window_size)/window_size, mode='valid')

    def plot_combined(self):
        fig = plt.figure(figsize=(10, 10))
        gs = plt.GridSpec(2, 2)

        ax1 = fig.add_subplot(gs[0, 1])
        if len(self.x_data) > 5 and len(self.y_data) > 5:
            x_position = self.smooth_data(self.x_data)
            y_position = self.smooth_data(self.y_data)
            min_len_xy = min(len(x_position), len(y_position))
            x_position = x_position[:min_len_xy]
            y_position = y_position[:min_len_xy]
        else:
            x_position = self.x_data
            y_position = self.y_data

        ax1.plot(x_position, y_position, 'r-', label="Position")
        ax1.set_xlabel("X (m)")
        ax1.set_ylabel("Y (m)")
        ax1.set_title("Position")
        ax1.grid(True)
        ax1.legend()

        ax2 = fig.add_subplot(gs[0, 0])
        min_len_cte = min(len(self.time_data), len(self.cte_data))
        ax2.plot(self.time_data[:min_len_cte], self.cte_data[:min_len_cte], label="CTE (Cross Track Error)")
        ax2.set_xlabel("Time (s)")
        ax2.set_ylabel("CTE (m)")
        ax2.set_title("CTE (Cross Track Error)")
        ax2.grid(True)
        ax2.legend()

        ax3 = fig.add_subplot(gs[1, 0])
        min_len_yaw = min(len(self.time_data), len(self.angular_data), len(self.target_heading_data))
        yaw_unwrapped = np.unwrap(self.angular_data[:min_len_yaw])
        yaw_deg_unwrapped = np.degrees(yaw_unwrapped)
        normalized_target = [self.normalize_angle(a) for a in self.target_heading_data[:min_len_yaw]]
        target_unwrapped = np.unwrap(normalized_target)
        target_deg_unwrapped = np.degrees(target_unwrapped)

        ax3.plot(self.time_data[:min_len_yaw], yaw_deg_unwrapped, label="YAW", color='g')
        ax3.plot(self.time_data[:min_len_yaw], target_deg_unwrapped, label="Target Heading", color='orange', linestyle='--')
        ax3.set_xlabel("Time (s)")
        ax3.set_ylabel("YAW / Heading (degree)")
        ax3.set_title("YAW vs Target Heading")
        ax3.grid(True)
        ax3.legend()

        plt.tight_layout()
        plt.show()

    def run(self):
        rate = rospy.Rate(10)
        arrived = False

        while not rospy.is_shutdown():
            if self.current_waypoint_index >= len(self.waypoints):
                rospy.loginfo("Arrived at final destination. Stopping robot.")
                self.cmd_vel_pub.publish(Twist())
                arrived = True
                break

            goal_x, goal_y = self.waypoints[self.current_waypoint_index]
            dist = self.distance(self.current_x, self.current_y, goal_x, goal_y)
            twist = self.control_adaptive_los(goal_x, goal_y)

            if dist <= self.GOAL_RADIUS:
                rospy.loginfo("Reached waypoint ({}, {})".format(goal_x, goal_y))
                self.current_waypoint_index += 1

            self.cmd_vel_pub.publish(twist)
            rate.sleep()

        if arrived:
            self.plot_combined()

if __name__ == '__main__':
    controller = AdaptiveLOSTrajectoryController()
    controller.run()
