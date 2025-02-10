FROM openrtm/devel-rtm:ubuntu18.04

COPY OpenRTM-aist /root/OpenRTM-aist
RUN cmake\
 -DSSL_ENABLE=ON\
 -DOBSERVER_ENABLE=ON\
 -DFLUENTBIT_ENABLE=ON\
 -DFLUENTBIT_ROOT=/usr/local\
 -DROS_ENABLE=ON\
 -DFASTRTPS_ENABLE=ON\
 -DROS2_ENABLE=ON\
 -DCMAKE_BUILD_TYPE=Release\
 -S /root/OpenRTM-aist\
 -B/tmp/rtm/build\
 && cmake --build /tmp/rtm/build -- -j$(nproc)
