#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <string>

 

using namespace sensor_msgs;
using namespace message_filters;

void callback(const ImageConstPtr& image1, const ImageConstPtr& image2)
{
  // Solve all of perception here...

  cv::Mat left=cv_bridge::toCvShare(image1, "bgr8")->image;
  cv::Mat right=cv_bridge::toCvShare(image2, "bgr8")->image;
  cv::namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );
  cv::imshow( "Gray image", right );
  cv::waitKey(3);

  int name = ros::Time::now().toNSec();
  std::ostringstream out ;
  out<<name;

  cv::imwrite("/home/jake/Desktop/clahs/left/"+out.str()+".jpg",left);
  cv::imwrite("/home/jake/Desktop/clahs/right/"+out.str()+".jpg",right);

}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "vision_node");

  ros::NodeHandle nh;
  message_filters::Subscriber<Image> image1_sub(nh, "stereo/clahs/left/image_rect_color", 1);
  message_filters::Subscriber<Image> image2_sub(nh, "stereo/clahs/right/image_rect_color", 1);

  typedef sync_policies::ApproximateTime<Image, Image> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), image1_sub, image2_sub);
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();

  return 0;
}