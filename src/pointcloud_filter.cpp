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
    "/mammoth/unfiltered_points", 10,
    std::bind(&PointcloudFilter::filter_callback, this, std::placeholders::_1));
}

void PointcloudFilter::filter_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // convert PointCloud2 to PCL::PointCloud
	pcl_conversions::copyPointCloud2MetaData(*msg, *cloud); 
	
  // Create the filtering object
  pcl::PassThrough<pcl::PCLPointCloud2> pass;
  pass.setInputCloud (cloud);
  pass.setFilterFieldName ("z");
  pass.setFilterLimits (0.0, 1.0);
  pass.FilterIndices::setNegative(true);
  pass.filter (*filtered_cloud);
  
  // convert PCL::PointCloud to PointCloud2
  pcl_conversions::copyPCLPointCloud2MetaData(*filtered_cloud, *msg);
  
  filtered_pc_publisher->publish(*msg);
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
