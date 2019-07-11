# passive dns
[![Build Status](https://travis-ci.com/sidorenko69/pdns.svg?token=wwQZr2XUtpzPdKqcF1eA&branch=dev)](https://travis-ci.com/sidorenko69/pdns)

## Requirements
1. C++11 and higher
1. Make
1. pcap `libpcap-dev`
1. G++
1. Python headers `python-dev`
1. ZLIB`zlib1g-dev`
1. [CMake](https://cmake.org/download/ )*(greater or equal 3.14)*
1. openssl `openssl-dev`

## Run
`./passivedns -i [eth0]`

## Installation
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. `make`
1. `make install`
