from rostooling/setup-ros-docker:ubuntu-focal-ros-foxy-desktop-latest
run rosdep update

run mkdir /ros_ws
workdir /ros_ws
copy src .
# run colcon list --packages-up-to robot_stack
run rosdep install --from-paths $(colcon list --packages-up-to robot_stack -p) --ignore-src -y --rosdistro foxy

