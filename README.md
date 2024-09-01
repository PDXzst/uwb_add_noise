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
也可以单独改变某一个信道  
```cpp
    void Add_Noise::callback(const nlink_parser::LinktrackNodeframe2::ConstPtr& uwb_in_ptr){
    nlink_parser::LinktrackNodeframe2 uwb_out(*uwb_in_ptr);
    uwb_out.nodes[0].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[1].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[2].dis += GuassianKernel(mean,stddev);
    uwb_out.nodes[3].dis += GuassianKernel(mean,stddev);

    uwb_noise_pub.publish(uwb_out);
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
rosbag play bag/bag1.bag
```
运行可视化文件  
```
roslaunch uwb_add_noise world_visual.launch
```

