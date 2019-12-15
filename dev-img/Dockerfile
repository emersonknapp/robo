ARG ROSDISTRO=eloquent
FROM osrf/ros:$ROSDISTRO-desktop
ARG ROSDISTRO

# Useful dev tools
RUN apt-get update && apt-get install -y \
      htop \
      screen \
      tree \
      vim \
      less \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install -U \
  ipython

# dependency ros packages
RUN apt-get update && apt-get install -y \
      ros-$ROSDISTRO-ros2bag \
      ros-$ROSDISTRO-rosbag2-storage-default-plugins \
      ros-$ROSDISTRO-launch-testing-ament-cmake \
      ros-$ROSDISTRO-python-qt-binding \
      ros-$ROSDISTRO-xacro \
      ros-$ROSDISTRO-gazebo-plugins \
    && rm -rf /var/lib/apt/lists/*

# specifically cartographer-ros dependencies
RUN apt-get update && apt-get install -y \
      ros-$ROSDISTRO-cartographer-ros \
      libsdl1.2-dev \
      libsdl-image1.2-dev \
      ros-$ROSDISTRO-test-msgs \
      libgraphicsmagick++1-dev \
      ros-$ROSDISTRO-behaviortree-cpp-v3 \
    && rm -rf /var/lib/apt/lists/*

# kobuki_driver dependencies
RUN apt-get update && apt-get install -y \
      ftdi-eeprom \
      libusb-dev \
      libftdi-dev \
      ros-${ROSDISTRO}-ecl-build \
      ros-${ROSDISTRO}-ecl-threads \
      ros-${ROSDISTRO}-ecl-geometry \
      ros-${ROSDISTRO}-ecl-linear-algebra \
      ros-${ROSDISTRO}-ecl-command-line \
      ros-${ROSDISTRO}-ecl-mobile-robot \
      ros-${ROSDISTRO}-ecl-config \
      ros-${ROSDISTRO}-ecl-converters \
      ros-${ROSDISTRO}-ecl-devices \
      ros-${ROSDISTRO}-ecl-sigslots \
      ros-${ROSDISTRO}-ecl-time \
    && rm -rf /var/lib/apt/lists/*

# for joint_state_publisher and neato_botvac
RUN python3 -m pip install -U \
  pyserial \
  PySide2

# development workflow dependencies
RUN apt-get update && apt-get install -y \
      ros-$ROSDISTRO-rqt \
      ros-$ROSDISTRO-rqt-graph \
    && rm -rf /var/lib/apt/lists/*

# RUN groupadd -r developer -g 1001 && useradd -r -g developer -u 1000 developer -m -G dialout
# USER developer

ENV TERM xterm-256color
CMD ["bash", "-l"]
COPY setup.bash /home/developer/homey_setup.bash
RUN echo "source ~/homey_setup.bash" >> /home/developer/.bashrc
