/*
 * \file
 * \brief Configuration file
 *
 * Comment not using params:
 * DEBUG - for debug
 * ERROR - enable output errors to terminal
 */
#include <vector>
#include <tins/tins.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <ctime>
/////////////////////
using namespace std;
using json = nlohmann::json;
using namespace Tins;
/////////////////////
//#define IP_TYPE IPv4Address
#define IP_TYPE std::string
//#define ERROR
#define DEBUG
#define CPPHTTPLIB_OPENSSL_SUPPORT
#define CPPHTTPLIB_ZLIB_SUPPORT