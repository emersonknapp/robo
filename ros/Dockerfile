from rostooling/setup-ros-docker:ubuntu-focal-latest
env DEBIAN_FRONTEND=noninteractive
run apt-get update && apt-get install -y --no-install-recommends \
  ccache \
  curl \
  gdb \
  htop \
  less \
  screen \
  tree \
  vim \
  zsh
run python3 -m pip install -U ipython colcon-mixin

workdir /ws
copy src/ src/

arg ROSDISTRO=galactic
arg ENTRYPKG=robot_stack
env ROS_DISTRO=$ROSDISTRO
env ROS_PYTHON_VERSION=3

run apt-get update && rosdep update && rosdep install --from-paths $(colcon list -p --packages-up-to $ENTRYPKG) --ignore-src -y --rosdistro $ROS_DISTRO

env COLCON_DEFAULTS_FILE=/ws/defaults.yaml
env COLCON_HOME=/etc/colcon
run colcon mixin add default https://raw.githubusercontent.com/colcon/colcon-mixin-repository/master/index.yaml && colcon mixin update
