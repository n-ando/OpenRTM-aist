FROM openrtm/devel-rtm:ubuntu18.04

ENV DEBIAN_FRONTEND=noninteractive
ENV ROS_DISTRO=melodic
RUN apt-get update
RUN apt-get -y install gnupg2
RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu bionic main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt-key adv --keyserver keyserver.ubuntu.com --recv-keys F42ED6FBAB17C654
RUN apt-get -y update
RUN apt-get -y install ros-${ROS_DISTRO}-ros-base
RUN rosdep init
RUN rosdep update
ENV CMAKE_PREFIX_PATH=/opt/ros/${ROS_DISTRO}:${CMAKE_PREFIX_PATH}
ENV ROS_ETC_DIR=/opt/ros/${ROS_DISTRO}/etc/ros
ENV ROS_ROOT=/opt/ros/${ROS_DISTRO}/share/ros
ENV ROS_VERSION=1
ENV ROS_PYTHON_VERSION=2
ENV ROS_PACKAGE_PATH=/opt/ros/${ROS_DISTRO}/share
ENV PYTHONPATH=/opt/ros/${ROS_DISTRO}/lib/python2.7/dist-packages:${PYTHONPATH}
ENV PATH=/opt/ros/${ROS_DISTRO}/bin:${PATH}

COPY OpenRTM-aist /root/OpenRTM-aist
RUN cmake\
 -DSSL_ENABLE=ON\
 -DOBSERVER_ENABLE=ON\
 -DFLUENTBIT_ENABLE=ON\
 -DFLUENTBIT_ROOT=/usr/local/include\
 -DROS_ENABLE=ON\
 -DCMAKE_BUILD_TYPE=Release\
 -S /root/OpenRTM-aist\
 -B/tmp/rtm/build\
 && cmake --build /tmp/rtm/build -- -j$(nproc)
