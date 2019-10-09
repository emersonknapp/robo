FROM ubuntu:bionic

RUN echo 'Etc/UTC' > /etc/timezone && \
    ln -s /usr/share/zoneinfo/Etc/UTC /etc/localtime

RUN apt-get update && apt-get install -q -y \
       tzdata \
       locales \
       curl \
       gnupg2 \
       lsb-release \
    && rm -rf /var/lib/apt/lists/*

ENV LANG=en_US.UTF-8
RUN locale-gen en_US $LANG && update-locale LC_ALL=$LANG LANG=$LANG

RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -
RUN sh -c 'echo "deb [arch=amd64,arm64] http://packages.ros.org/ros2/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'

RUN apt-get update && apt-get install -y \
      ros-dashing-desktop \
    && rm -rf /var/lib/apt/lists/*

# Install build tools for building our workspace
RUN apt-get update --fix-missing && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3-colcon-common-extensions \
    python3-lark-parser \
    python3-pip \
    python-rosdep \
    python3-vcstool \
    wget \
  && rm -rf /var/lib/apt/lists/*

# install some pip packages needed for testing
RUN python3 -m pip install -U \
  argcomplete \
  colcon-mixin \
  flake8 \
  flake8-blind-except \
  flake8-builtins \
  flake8-class-newline \
  flake8-comprehensions \
  flake8-deprecated \
  flake8-docstrings \
  flake8-import-order \
  flake8-quotes \
  pytest-repeat \
  pytest-rerunfailures \
  pytest \
  pytest-cov \
  pytest-runner \
  setuptools

# base packages
RUN python3 -m pip install -U \
  pyserial

# perception packages
RUN apt-get update && apt-get install -y \
      ros-dashing-cartographer-ros \
    && rm -rf /var/lib/apt/lists/*

# Other ros packages
RUN apt-get update && apt-get install -y \
      ros-dashing-rosbag2 \
      ros-dashing-rosbag2-storage-default-plugins \
      ros-dashing-ros2bag \
    && rm -rf /var/lib/apt/lists/*

# Useful dev tools
RUN apt-get update && apt-get install -y \
      htop \
      screen \
    && rm -rf /var/lib/apt/lists/*

RUN groupadd -r developer -g 1001 && useradd -r -g developer -u 1000 developer -m -G dialout
USER developer

ENV TERM xterm-256color
CMD ["bash", "-l"]
COPY setup.bash /home/developer/homey_setup.bash
RUN echo "source ~/homey_setup.bash" >> /home/developer/.bashrc
