# Code check by the latest clang.
FROM ubuntu:20.04
ARG CLANG_VAR=9

RUN apt-get update\
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends\
 clang-${CLANG_VAR}\
 ninja-build\
 cmake\
 uuid-dev\
 libboost-filesystem-dev\
 omniorb-nameserver\
 libomniorb4-dev\
 omniidl\
 && apt-get clean\
 && rm -rf /var/lib/apt/lists/*

RUN update-alternatives\
 --install /usr/bin/clang clang /usr/bin/clang-${CLANG_VAR} 10\
 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VAR}\
 && update-alternatives --install /usr/bin/cc  cc  /usr/bin/clang   10\
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 10

COPY OpenRTM-aist /root/OpenRTM-aist

RUN cmake\
 -DSSL_ENABLE=ON\
 -DOBSERVER_ENABLE=ON\
 -DCMAKE_BUILD_TYPE=Release\
 -S /root/OpenRTM-aist\
 -B /tmp/rtm/build\
 -G Ninja\
 && cmake --build /tmp/rtm/build
