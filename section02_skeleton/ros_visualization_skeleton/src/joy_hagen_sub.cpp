
#include <ros/ros.h>
#include <ros/console.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Vector3.h>
#include <ros_visualization_skeleton/SetSpeed.h>

float previous_speed = 0.;
float new_speed      = 0.;

void callback_temp(const std_msgs::Int32::ConstPtr& msg){
  ROS_INFO_STREAM( "Temp = " << msg->data );
}

void callback_accel(const geometry_msgs::Vector3::ConstPtr& msg){
  ROS_INFO_STREAM("Accel = (" << msg->x << ", " << msg->y << ", " << msg->z << ")");
}

bool callback_speed(ros_visualization_skeleton::SetSpeed::Request  &req, ros_visualization_skeleton::SetSpeed::Response &res){
  ROS_INFO_STREAM("Speed service request: desired speed = " << req.desired_speed);
  previous_speed = new_speed;
  new_speed = 0.6*req.desired_speed;
  
  res.new_speed = new_speed;
  res.previous_speed = previous_speed;
  res.stalled  = new_speed < 0.1;
  return true;
}

int main( int argc, char **argv )
{
  ros::init(argc, argv, "joy_hagen_sub");
  ros::NodeHandle n;
  ros::Subscriber sub_temp = n.subscribe( "/joy_hagen/temperature", 1000, callback_temp );
  ros::Subscriber sub_accel = n.subscribe( "/joy_hagen/imu", 1000, callback_accel );
  ros::ServiceServer srv_speed = n.advertiseService( "speed", callback_speed );
  while(ros::ok()) {
    ros::spin();
  }
  return EXIT_SUCCESS;
}

