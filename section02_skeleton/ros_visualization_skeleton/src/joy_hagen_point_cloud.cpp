
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <math.h>
// http://wiki.ros.org/pcl/Overview

int main( int argc, char **argv )
{
  ros::init( argc, argv, "joy_hagen_point_cloud" );
  ros::NodeHandle n;
  ros::Publisher pub_pc = n.advertise< sensor_msgs::PointCloud2 >("/joy_hagen_point_cloud/point_cloud", 1000);

  sensor_msgs::PointCloud2 msg_pc;
  pcl::PointCloud<pcl::PointXYZ > pc;
  pc.width  = 200;
  pc.height = 100;
  pc.is_dense = false;
  pc.resize(pc.width*pc.height);
  for( size_t i = 0; i < pc.height; ++i ) {
    for( size_t j = 0; j < pc.width; ++j ) {
      const size_t k = pc.width * i + j;
      pcl::PointXYZ tmp(10,10,10);
      pc.points[k] = tmp;
      // TODO assign the x, y, and z values of each point  
    }
  }
  ROS_INFO_STREAM( "Initial Point Cloud created." );
  ros::Rate rate( 1 );
  while( ros::ok() ) {
    for( size_t i = 0; i < pc.height; ++i ) {
      for( size_t j = 0; j < pc.width; ++j ) {
        const size_t k = pc.width * i + j;
          pcl::PointXYZ tmp(10+sin(i),12+sin(i+j),14+sin(j));
          pc.points[k] = tmp;
        // TODO assign the x, y, and z values of each point  
      }
    }
    pcl::toROSMsg(pc,msg_pc);
    msg_pc.header.frame_id = "smb";
    msg_pc.header.stamp = ros::Time::now();
    
    // TODO use pcl::toROSMsg to convert pcl message to ROS message 
    // TODO set header frame id of msg_pc as the "pc_frame" 
    pub_pc.publish(msg_pc);
    ros::spinOnce();
    rate.sleep();
  }

  return EXIT_SUCCESS;
}

