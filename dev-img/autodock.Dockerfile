from rostooling/setup-ros-docker:ubuntu-focal-ros-foxy-desktop-latest

run rosdep update

run mkdir /ws
copy src /ws/src
workdir /ws
run . /opt/ros/foxy/setup.sh && rosdep install --from-paths $(colcon list --packages-up-to robot_stack -p) --ignore-src -y --rosdistro foxy
env COLCON_DEFAULTS_FILE=/ws/defaults.yaml

