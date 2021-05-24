arg ROSDISTRO=foxy
from rostooling/setup-ros-docker:ubuntu-focal-ros-${ROSDISTRO}-desktop-latest

arg ROSDISTRO=foxy
arg ENTRYPKG=robot_stack

run rosdep update

run apt-get update && apt-get install -y --no-install-recommends \
  ccache \
  gdb \
  htop \
  less \
  screen \
  tree \
  vim \
  zsh
run python3 -m pip install -U ipython

run mkdir /ws
copy src /ws/src
workdir /ws
run apt-get update && . /opt/ros/${ROSDISTRO}/setup.sh && rosdep install --from-paths $(colcon list --packages-up-to ${ENTRYPKG} -p) --ignore-src -y

# RUN curl -fsSL https://deb.nodesource.com/setup_12.x | sudo -E bash - && \
#     apt-get install -y nodejs

env COLCON_DEFAULTS_FILE=/ws/defaults.yaml
env COLCON_HOME=/etc/colcon
run colcon mixin add default https://raw.githubusercontent.com/colcon/colcon-mixin-repository/master/index.yaml
run colcon mixin update
