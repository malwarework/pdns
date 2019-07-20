# Passive DNS
[![Build Status](https://travis-ci.com/sidorenko69/pdns.svg?branch=master)](https://travis-ci.com/sidorenko69/pdns)

## Requirements
1. C++11 and higher
1. Make
1. pcap `libpcap-dev`
1. G++
1. Python headers `python-dev`
1. ZLIB`zlib1g-dev`
1. [CMake](https://cmake.org/download/ )*(greater or equal 3.14)*
1. openssl `libssl-dev`

## Running
1. Configure `/etc/passivedns/passivedns.conf`
2. Execute as daemon`passivedns -d`

## Compiling
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. `make`
1. `make install`
1. `ldconfig`

## Installation
* In case if **Ubuntu**<p>
Run as root <b>`dpkg -i passivedns-*.deb`</b>
* In case if **Centos**<p>
Run <b>`rpm -ivh passivedns-*.rpm`</b>
