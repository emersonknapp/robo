FROM emerson/native-ubuntu-eloquent

RUN apt-get update && apt-get install -y ros-eloquent-rviz2

ENTRYPOINT /bin/bash
