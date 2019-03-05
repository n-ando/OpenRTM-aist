FROM debian:8

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
WORKDIR /root/OpenRTM-aist
RUN ln -s . src/lib/coil/common/coil\
 && ln -s ../../build/yat.py utils/rtm-skelwrapper/yat.py
RUN cmake -DCORBA=omniORB -DSSL_ENABLE=ON -DOBSEVER_ENABLE=ON -S . -Bbuild_openrtm\
 && cmake --build build_openrtm -- -j$(nproc)
