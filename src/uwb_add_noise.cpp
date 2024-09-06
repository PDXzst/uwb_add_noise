#include "uwb_add_noise.h"
namespace uwb_add_noise{
void Add_Noise::callback(const nlink_parser::LinktrackNodeframe2::ConstPtr& uwb_in_ptr){
    nlink_parser::LinktrackNodeframe2 uwb_out(*uwb_in_ptr);

    uwb_out.nodes[0].dis += GuassianKernel(mean1,stddev1);
    uwb_out.nodes[1].dis += GuassianKernel(mean2,stddev2);
    uwb_out.nodes[2].dis += GuassianKernel(mean3,stddev3);
    uwb_out.nodes[3].dis += GuassianKernel(mean4,stddev4);

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
//根据los情况调节高斯噪声
void Add_Noise::callback_los1(const std_msgs::Bool::ConstPtr& los1_in_ptr){
  std_msgs::Bool los1_in(*los1_in_ptr);
  if(los1_in.data == true){
    stddev1 = 0.01;//los时，噪声标准差为0.01
    mean1 = 0;
  }
  else{
    stddev1 = 0.1;//nlos时，噪声标准差为0.1
    mean1 = 0;
  }
}

void Add_Noise::callback_los2(const std_msgs::Bool::ConstPtr& los2_in_ptr){
  std_msgs::Bool los2_in(*los2_in_ptr);
  if(los2_in.data == true){
    stddev2 = 0.01;
    mean2 = 0;
  }
  else{
    stddev2 = 0.1;
    mean2 = 0;
  }
}

void Add_Noise::callback_los3(const std_msgs::Bool::ConstPtr& los3_in_ptr){
  std_msgs::Bool los3_in(*los3_in_ptr);
  if(los3_in.data == true){
    stddev3 = 0.01;
    mean3 = 0;
  }
  else{
    stddev3 = 0.1;
    mean3 = 0;
  }
}

void Add_Noise::callback_los4(const std_msgs::Bool::ConstPtr& los4_in_ptr){
  std_msgs::Bool los4_in(*los4_in_ptr);
  if(los4_in.data == true){
    stddev4 = 0.01;
    mean4 = 0;
  }
  else{
    stddev4 = 0.1;
    mean4 = 0;
  }
}

Add_Noise::Add_Noise(ros::NodeHandle &_nh)
{
    //initialize the mean and stddev
    stddev1= 0.01;//标准差
    mean1 = 0;//均值
    stddev2= 0.01;//标准差
    mean2 = 0;//均值
    stddev3= 0.01;//标准差
    mean3 = 0;//均值
    stddev4= 0.01;//标准差
    mean4 = 0;//均值

    nh = _nh;
    los1_get = nh.subscribe<std_msgs::Bool>("los1",100,&Add_Noise::callback_los1,this);
    los2_get = nh.subscribe<std_msgs::Bool>("los2",100,&Add_Noise::callback_los2,this);
    los3_get = nh.subscribe<std_msgs::Bool>("los3",100,&Add_Noise::callback_los3,this);
    los4_get = nh.subscribe<std_msgs::Bool>("los4",100,&Add_Noise::callback_los4,this);
    uwb_origin_sub=nh.subscribe<nlink_parser::LinktrackNodeframe2>("nlink_parser_LinktrackNodeframe2",100,&Add_Noise::callback,this);
    uwb_noise_pub = nh.advertise<nlink_parser::LinktrackNodeframe2>("nlink_parser_LinktrackNodeframe2_noise", 100, true);
    //groundtrue_vel_pub = nh.advertise<nav_msgs::Odometry>("true_vel", 100, true);
}
}