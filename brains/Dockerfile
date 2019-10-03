FROM balenalib/raspberrypi3-ubuntu-python:3.6.9-bionic
# COPY bin/qemu-arm-static /usr/bin
ENV UDEV=1

# set up timezone
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
RUN echo "deb [arch=armhf] http://packages.ros.org/ros2/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list
RUN apt-get update && apt-get install -q -y \
      ros-dashing-ros-core \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -q -y \
      ros-dashing-joy \
      ros-dashing-teleop-twist-joy \
  && rm -rf /var/lib/apt/lists/*

CMD /bin/bash
