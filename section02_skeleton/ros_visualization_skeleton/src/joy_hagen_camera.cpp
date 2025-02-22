
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/highgui/highgui.hpp>

int main( int argc, char **argv )
{
  ros::init( argc, argv, "joy_hagen_camera");
  ros::NodeHandle n;
  const int CAMERA_INDEX = 0;
  cv::VideoCapture capture(CAMERA_INDEX);
  if(not capture.isOpened())
  {
    ROS_ERROR_STREAM("Failed to open camera with index " << CAMERA_INDEX << "!");
    ros::shutdown();
  }
  image_transport::ImageTransport it(n);
  image_transport::Publisher pub_image = it.advertise("/joy_hagen_camera/camera", 1);
  cv_bridge::CvImagePtr frame = boost::make_shared<cv_bridge::CvImage>();
  frame->encoding = sensor_msgs::image_encodings::BGR8;
  while( ros::ok() ) {
    capture >> frame->image;
    if( frame->image.empty() )
    {
      ROS_ERROR_STREAM( "Failed to capture frame!" );
      ros::shutdown();
    }
  
    frame->header.stamp = ros::Time::now();
    pub_image.publish( frame->toImageMsg() );
    cv::waitKey( 3 );
    ros::spinOnce();
  }
  capture.release();
  return EXIT_SUCCESS;
}

