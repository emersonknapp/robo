FROM arm64v8/ros:eloquent
COPY bin/qemu-aarch64-static /usr/bin

COPY compressed_install.sh .
RUN chmod +x compressed_install.sh
RUN apt-get update && ./compressed_install.sh
CMD /bin/bash
