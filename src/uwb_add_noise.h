#ifndef UWB_ADD_NOISE_H
#define UWB_ADD_NOISE_H
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "nav_msgs/Odometry.h"
#include "tf/tf.h"
#include <nlink_parser/LinktrackNodeframe2.h>
#include <nlink_parser/LinktrackNode2.h>
namespace uwb_add_noise{
class Add_Noise{
public:
    Add_Noise(ros::NodeHandle &_nh);
private:
    ros::Publisher uwb_noise_pub;
    ros::NodeHandle nh; 
    ros::Subscriber uwb_origin_sub;
    void callback(const nlink_parser::LinktrackNodeframe2::ConstPtr& uwb_in_ptr);
    unsigned int seed = 0;
    double GuassianKernel(double mu, double sigma);

    double mean;
    double stddev;
}; 

}


#endif