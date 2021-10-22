#include <memory>
#include <functional>


#include "pointcloud_filter/pointcloud_filter.hpp"


namespace PointcloudFilter
{
PointcloudFilter::PointcloudFilter(rclcpp::NodeOptions options)
: Node("pointcloud_filter", options)
{
  filtered_pc_publisher =this->create_publisher<sensor_msgs::msg::PointCloud2>( 
    "/mammoth/filtered_points", rclcpp::SensorDataQoS());

  unfiltered_pc_subscription = this->create_subscription<sensor_msgs::msg::PointCloud2>(
    "/mammoth/unfiltered_points", rclcpp::SensorDataQoS(),
    std::bind(&PointcloudFilter::filter_callback, this, std::placeholders::_1));
}

void PointcloudFilter::filter_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
   // Container for original & filtered data
  pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
  pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
  pcl::PCLPointCloud2 cloud_filtered;
  
  // Convert to PCL data type
  pcl_conversions::toPCL(*msg, *cloud);

  // Perform the actual filtering
  pcl::PassThrough<pcl::PCLPointCloud2> pass;
  pass.setInputCloud (cloudPtr);
  pass.setFilterFieldName ("z");
  pass.setFilterLimits (0.0, 1.0);
  //pass.setFilterLimitsNegative (true);
  pass.filter (cloud_filtered);
  
  // Convert to ROS data type
  sensor_msgs::msg::PointCloud2 output;
  pcl_conversions::fromPCL(cloud_filtered, output);
  
  // publish filtered pointcloud2 message 
  filtered_pc_publisher->publish(output);
}
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;
  rclcpp::NodeOptions options;
  auto lp_node = std::make_shared<PointcloudFilter::PointcloudFilter>(options);
  exec.add_node(lp_node);
  exec.spin();
  rclcpp::shutdown();
  return 0;
}
