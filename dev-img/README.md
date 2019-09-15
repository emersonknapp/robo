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
