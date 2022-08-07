FROM ubuntu:20.04
ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    clang-12 \
    lldb-12 \
    gdb \
    ninja-build \
    libeigen3-dev \
    freeglut3-dev \
    mesa-common-dev \
    mesa-utils \
    libopencv-dev

CMD ["/bin/bash"]
