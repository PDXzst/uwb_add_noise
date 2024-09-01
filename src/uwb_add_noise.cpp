#include "uwb_add_noise.h"
namespace uwb_add_noise{
void Add_Noise::callback(const nlink_parser::LinktrackNodeframe2::ConstPtr& uwb_in_ptr){
    nlink_parser::LinktrackNodeframe2 uwb_out(*uwb_in_ptr);
    uwb_out.nodes[0].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[1].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[2].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[3].dis += GuassianKernel(mean,stddev);

    uwb_noise_pub.publish(uwb_out);
}

//高斯噪声
double Add_Noise::GuassianKernel(double mu, double sigma)
{
  // generation of two normalized uniform random variables
  double U1 = static_cast<double>(rand_r(&seed)) / static_cast<double>(RAND_MAX);
  double U2 = static_cast<double>(rand_r(&seed)) / static_cast<double>(RAND_MAX);

  // using Box-Muller transform to obtain a varaible with a standard normal distribution
  double Z0 = sqrt(-2.0 * ::log(U1)) * cos(2.0*M_PI * U2);

  // scaling
  Z0 = sigma * Z0 + mu;
  return Z0;
}


Add_Noise::Add_Noise(ros::NodeHandle &_nh)
{
    stddev = 0.01;//标准差
    mean = 0;//均值
    nh = _nh;
    uwb_origin_sub=nh.subscribe<nlink_parser::LinktrackNodeframe2>("nlink_parser_LinktrackNodeframe2",100,&Add_Noise::callback,this);
    uwb_noise_pub = nh.advertise<nlink_parser::LinktrackNodeframe2>("nlink_parser_LinktrackNodeframe2_noise", 100, true);
    //groundtrue_vel_pub = nh.advertise<nav_msgs::Odometry>("true_vel", 100, true);
}
}