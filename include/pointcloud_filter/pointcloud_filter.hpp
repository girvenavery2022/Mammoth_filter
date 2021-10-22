#ifndef POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_
#define POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_

#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/header.hpp"
#include "sensor_msgs/msg/point_cloud2.h"
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include "pcl_conversions/pcl_conversions.h"
#include <pcl/io/pcd_io.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

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
  
};
}  // namespace PointcloudFilter

#endif  // POINTCLOUD_FILTER__POINTCLOUD_FILTER_HPP_
