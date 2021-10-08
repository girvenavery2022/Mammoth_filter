# Mammoth_filter
This repo is a simple pcl filter to filter through PointCloud2 data, right now it is implemented using a passthrough filter
but can be changed to another filtering algorithm provided by PCL.

# Build 
1. Change directory into your colcon workspace folder. Example: 'cd ~/ros_ws/'
2. Clone the repository into your colcon workspace: vcs import src --input https://raw.githubusercontent.com/girvenavery2022/Mammoth_filter/master/pointcloud_filter.repos
3. Build the colcon workspace: colcon build
4. Source the local workspace: . install/setup.bash
