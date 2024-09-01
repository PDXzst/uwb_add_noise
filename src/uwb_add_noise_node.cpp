#include "uwb_add_noise.h"
#include <ros/ros.h>


using namespace uwb_add_noise;

int main(int argc,char** argv){
    ros::init(argc,argv,"uwb_add_noise_node");
    ros::NodeHandle nh;
    Add_Noise filer(nh);
    ros::spin();
}