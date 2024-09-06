#ifndef UWB_ADD_NOISE_H
#define UWB_ADD_NOISE_H
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "nav_msgs/Odometry.h"
#include "tf/tf.h"
#include <nlink_parser/LinktrackNodeframe2.h>
#include <nlink_parser/LinktrackNode2.h>
#include <std_msgs/Bool.h>
namespace uwb_add_noise{
class Add_Noise{
public:
    Add_Noise(ros::NodeHandle &_nh);
private:
    ros::Publisher uwb_noise_pub;
    ros::NodeHandle nh; 
    ros::Subscriber uwb_origin_sub,los1_get,los2_get,los3_get,los4_get;
    void callback(const nlink_parser::LinktrackNodeframe2::ConstPtr& uwb_in_ptr);
    unsigned int seed = 0;
    double GuassianKernel(double mu, double sigma);
    void callback_los1(const std_msgs::Bool::ConstPtr& los1_in_ptr);
    void callback_los2(const std_msgs::Bool::ConstPtr& los2_in_ptr);
    void callback_los3(const std_msgs::Bool::ConstPtr& los3_in_ptr);
    void callback_los4(const std_msgs::Bool::ConstPtr& los4_in_ptr);
    double mean1, mean2, mean3, mean4;
    double stddev1, stddev2, stddev3, stddev4;
}; 

}


#endif