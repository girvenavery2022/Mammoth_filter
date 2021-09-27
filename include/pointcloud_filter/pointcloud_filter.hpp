#ifndef POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_
#define POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include "pcl_conversions/pcl_conversions.h"


namespace PointcloudFilter
{
class PointcloudFilter : public rclcpp::Node
{
public:
  explicit PointcloudFilter(rclcpp::NodeOptions options);

private:

  void filter_callback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);
  
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr filtered_pc_publisher;
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr unfiltered_pc_subscription;
  

  pcl::PCLPointCloud2::Ptr cloud;
  pcl::PCLPointCloud2::Ptr filtered_cloud;
};
}  // namespace PointcloudFilter

#endif  // POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_
