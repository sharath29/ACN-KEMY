FROM ubuntu:latest
LABEL Description="Docker image for NS-3 Network Simulator"

RUN apt-get update

# General dependencies
RUN apt-get install -y \
  git \
  mercurial \
  wget \
  vim \
  autoconf \
  bzr \
  cvs \
  unrar \
  build-essential \
  clang \
  valgrind \
  gsl-bin \
  libgsl2 \
  libgsl-dev \
  flex \
  bison \
  libfl-dev \
  tcpdump \
  sqlite \
  sqlite3 \
  libsqlite3-dev \
  libxml2 \
  libxml2-dev \
  vtun \
  lxc

# QT4 components
RUN apt-get install -y \
  qtbase5-dev

# Python components
RUN apt-get install -y \
  python \
  python-dev \
  python-setuptools \
  cmake \
  libc6-dev \
  libc6-dev-i386 \
  g++-multilib

# NS-3

# Create working directory
RUN mkdir -p /usr/ns3
WORKDIR /usr

# Fetch NS-3 source
RUN wget http://www.nsnam.org/release/ns-allinone-3.27.tar.bz2
RUN tar -xf ns-allinone-3.27.tar.bz2

# Configure and compile NS-3
RUN cd ns-allinone-3.27 && ./build.py --enable-examples --enable-tests

RUN ln -s /usr/ns-allinone-3.27/ns-3.27/ /usr/ns3/

# Cleanup
RUN apt-get clean && \
  rm -rf /var/lib/apt && \
  rm /usr/ns-allinone-3.27.tar.bz2

#docker cp traffic-control ns3:/usr/


RUN apt-get install -y git \
boost \
boost-devel \
libX11-devel \
xorg-x11-proto-devel \
libXt-devel \
libXmu-devel \
autoconf \
automake \
make \
gcc \
gcc-c++ \
protobuf \
protobuf-devel \
pkg-conf \
jemalloc*


//protobuf
RUN apt-get install \
autoconf \
automake \
libtool \
curl \
make \
g++ \
unzip

RUN cd /usr && git clone https://github.com/google/protobuf.git && cd protobuf && git submodule update --init --recursive && ./autogen.sh && ./configure && make && make check && make install && ldconfig

RUN cd ns3/ns-3.27/src/traffic-control/model/kemy/ && /usr/local/bin/protoc --cpp_out=. dna.proto

RUN ./waf configure CXXFLAGS='$(pkg-config --cflags protobuf)' LINKFLAGS='$(pkg-config --libs protobuf)' && ./waf












