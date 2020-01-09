FROM debian:10

RUN apt-get update\
 && apt-get install -y --no-install-recommends\
 g++\
 make\
 cmake\
 uuid-dev\
 libboost-filesystem-dev\
 omniorb-nameserver\
 libomniorb4-dev\
 omniidl\
 && apt-get clean\
 && rm -rf /var/lib/apt/lists/*

COPY OpenRTM-aist /root/OpenRTM-aist
RUN cmake\
 -DSSL_ENABLE=ON\
 -DOBSERVER_ENABLE=ON\
 -DCMAKE_BUILD_TYPE=Release\
 -S /root/OpenRTM-aist\
 -B /tmp/rtm/build\
 && cmake --build /tmp/rtm/build -j $(nproc)
