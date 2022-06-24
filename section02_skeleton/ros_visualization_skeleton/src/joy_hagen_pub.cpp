
#include <ros/ros.h>
#include <ros/console.h>

#include <std_msgs/Int32.h>
#include <geometry_msgs/Vector3.h>
#include <math.h>
#include <ros_visualization_skeleton/SetSpeed.h>

int main( int argc, char **argv )
{

  ros::init( argc, argv, "joy_hagen");
  ros::NodeHandle n;
  ros::Publisher pub_temp = n.advertise<std_msgs::Int32>( "/joy_hagen/temperature", 1000);
  ros::Publisher pub_imu = n.advertise<geometry_msgs::Vector3>( "/joy_hagen/imu", 1000);
  ros::ServiceClient srv_speed = n.serviceClient<ros_visualization_skeleton::SetSpeed>( "speed" );

  std_msgs::Int32 msg_temperature;
  geometry_msgs::Vector3 msg_imu_acceleration;
  ros_visualization_skeleton::SetSpeed msg_speed;

  int i = 0;
  ros::Rate rate( 5 );
  while( ros::ok() ) {

    msg_imu_acceleration.x = cos(i*0.1);
    msg_imu_acceleration.y = sin(i*0.1);
    msg_imu_acceleration.z = sin(i*0.2);
    msg_temperature.data = sin(i*0.05);

    pub_imu.publish(msg_imu_acceleration);
    pub_temp.publish(msg_temperature);

    msg_speed.request.desired_speed =0.3*i;
    bool kavo = srv_speed.call(msg_speed);
    if (kavo)
    {
      ROS_INFO("Aboba %f %f",msg_speed.response.new_speed, msg_speed.response.previous_speed);
    }

    // if (srv_speed.call(msg_sp))
    // TODO call the service srv_speed and if it get executed, print previous_speed and new_speed
    ++i;
    ros::spinOnce();
    rate.sleep();
  }
  return EXIT_SUCCESS;
}

