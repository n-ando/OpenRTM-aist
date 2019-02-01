FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

RUN set -x && \
    apt-get update -qq

COPY build/pkg_install_ubuntu.sh /
RUN chmod a+x ./pkg_install_ubuntu.sh&& \
    ./pkg_install_ubuntu.sh -l c++ -l python -c --yes

ENTRYPOINT ["/bin/bash", "-c"]
