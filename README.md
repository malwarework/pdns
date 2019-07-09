# passive dns
[![Build Status](https://travis-ci.com/sidorenko69/pdns.svg?token=wwQZr2XUtpzPdKqcF1eA&branch=dev)](https://travis-ci.com/sidorenko69/pdns)

## Requirements
1. C++11 and higher
1. Make
1. G++
1. Python headers `python-dev`
1. ZLIB
1. [CMake](https://cmake.org/download/ )*(greater or equal 3.14)*
1. [nlohmann/json](https://github.com/nlohmann/json.git)
1. [libtins](https://github.com/mfontanini/libtins.git)
1. [Boost](https://dl.bintray.com/boostorg/release/)
1. [librdkafka](https://github.com/edenhill/librdkafka.git)
1. [cppkafka](https://github.com/mfontanini/cppkafka.git) with param `CPPKAFKA_RDKAFKA_STATIC_LIB=ON`


## Run
`./passivedns -i [eth0]`
