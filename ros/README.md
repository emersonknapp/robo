# Home Robo ROS2 software stack

## Setup

```
mkdir src
vcs import src < homey.repos
```


## Build

```
colcon build --packages-up-to neato_gazebo cartographer_ros nav2_map_server
```

## Run

Simulation workflow is launched via

```
ros2 launch neato_gazebo neato_willow.launch.py
```

It runs cartographer SLAM. Once you have a map

```
ros2 run nav2_map_server map_saver
```
