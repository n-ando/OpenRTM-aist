FROM openrtm/devel-rtm:ubuntu18.04

COPY OpenRTM-aist /root/OpenRTM-aist
WORKDIR /root/OpenRTM-aist
RUN ln -s . src/lib/coil/common/coil\
 && ln -s ../../build/yat.py utils/rtm-skelwrapper/yat.py
RUN cmake -DCORBA=omniORB -DFLUENTBIT_ENABLE=ON  -DFLUENTBIT_ROOT=/usr/local/include\
 -DSSL_ENABLE=ON -DOBSERVER_ENABLE=ON -S . -Bbuild_openrtm\
 && cmake --build build_openrtm -- -j$(nproc)

