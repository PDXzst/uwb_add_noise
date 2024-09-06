## Make By Tsinghua_PDXzst
#### communication by zst1677476115@qq.com
### uwb_add_noise
#### bag
两个功能包都可以用  
#### launch
启动rviz环境  
#### rviz
rviz环境  
#### src
对uwb数据添加高斯噪声  
通过调整`src/uwb_add_noise.cpp`改变高斯噪声的均值`mean`和方差`stddev`  
也可以根据`los`情况改变某一个信道  
```cpp
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
```
#### urdf
存放模型  

#### how to use
编译  
```
cd 'workspace'
catkin_make
```
运行  
```
source devel/setup.bash
roscore
```
先跑`bag`  
```
rosbag play bag/bag5.bag
```
运行可视化文件  
```
roslaunch uwb_add_noise world_visual.launch
```

#### 更新日志
- [X] 添加bag5.bag实现uwb信道路径可视化  
- [X] uwb_add_noise.cpp实现根据los情况改变信道高斯噪声方差  

