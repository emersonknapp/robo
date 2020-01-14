FROM arm64v8/ros:eloquent

COPY qemu-aarch64-static /usr/bin/

RUN apt-get update && apt-get install -y \
      ros-eloquent-joy \
      ros-eloquent-teleop-twist-joy \
      ros-eloquent-ecl-build \
      libboost-system-dev \
      ros-eloquent-ecl-build \
      ros-eloquent-ecl-mobile-robot \
      ros-eloquent-ecl-config \
      ros-eloquent-ecl-converters \
      ros-eloquent-ecl-devices \
      ros-eloquent-ecl-geometry \
      ros-eloquent-ecl-sigslots \
      ros-eloquent-ecl-threads \
      ros-eloquent-ecl-time \
      ros-eloquent-ecl-command-line

RUN mkdir -p /root/ws/src
WORKDIR /root/ws

COPY kobuki_base src/kobuki_base/
COPY robot_stack src/robot_stack/

RUN . /opt/ros/eloquent/setup.sh && \
    colcon build --packages-up-to robot_stack --packages-skip parking_rviz_plugins
