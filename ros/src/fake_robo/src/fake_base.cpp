// Copyright 2019 Emerson Knapp
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"

#include "geometry_msgs/msg/twist_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"


namespace fake_robo
{

class FakeBase : public rclcpp::Node
{
public:
  explicit FakeBase(const rclcpp::NodeOptions & options)
  : Node("fake_base", options)
  {
    std::cout << "Hello Node" << std::endl;
    cmd_vel_sub_ = create_subscription<geometry_msgs::msg::TwistStamped>(
      "cmd_vel", 10, [this](const geometry_msgs::msg::TwistStamped::SharedPtr msg) -> void {
        RCLCPP_INFO(this->get_logger(), "I heard a cmd x %f", msg->twist.linear.x);
      });
    odom_pub_ = create_publisher<nav_msgs::msg::Odometry>("odom", 10);
  }

private:
  rclcpp::Subscription<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_vel_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
};

}  // namespace demo_nodes_cpp

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor exec;
  rclcpp::NodeOptions options;
  auto fake_base = std::make_shared<fake_robo::FakeBase>(options);
  exec.add_node(fake_base);
  exec.spin();
  rclcpp::shutdown();
  return 0;
}

RCLCPP_COMPONENTS_REGISTER_NODE(fake_robo::FakeBase)
