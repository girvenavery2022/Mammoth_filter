# Mammoth_filter
This repo is a simple pcl filter to filter through PointCloud2 data, right now it is implemented using a passthrough filter
but can be changed to another filtering algorithm provided by PCL.

# Build 
1. Change directory into your colcon workspace folder. Example: `cd ~/ros_ws/`
2. Clone the repository into your colcon workspace: `vcs import src --input https://raw.githubusercontent.com/girvenavery2022/Mammoth_filter/master/pointcloud_filter.repos`
3. Build the colcon workspace: `colcon build`
4. Source the local workspace: `. install/setup.bash`

# External Packages
This package uses the PCL libray to do filtering work but unfortunately, PCL is only supported in ROS1. To get around that, 
I included the perception_pcl package that ports over PCL from ROS1 to ROS2 foxy. 

# Problems
Luckily, the package builds succesfully. but when launching the node from either the command line or from a launch file it crashes. The PCL class doesn't like the pointers defined in the hpp file. fixing that should fix the problem and we can go on to the testing phase.
