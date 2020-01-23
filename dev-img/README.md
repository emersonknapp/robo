## build

```
docker build . -t homeydev
```

## run
From `$REPO/ros`

```
docker run -it \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    -v $(pwd):/ws \
    homeydev
```


## rosdep workflow

```
docker build -f Dockerfile_rosdep -t rosdepper 
docker run -v $ROS_WS:/root/ros -w /root/ros -e ROSDISTRO=eloquent -e PACKAGE=robot_runtime rosdepper
```

Outputs `$ROS_WS/compressed_install.sh` which contains a single-line apt-get install script. Can use this to create `runtime` image

