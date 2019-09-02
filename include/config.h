/*
 * \file
 * \brief Configuration file
 *
 * Comment not using params:
 * DEBUG - for debug
 * ERROR - enable output errors to terminal
 * KAFKA - enable suuport of kafka
 * SYSLOG - output to syslog
 */
//#define IP_TYPE IPv4Address
#define IP_TYPE std::string
//#define ERROR
#define SYSLOG
#define DEBUG
//#define CPPHTTPLIB_OPENSSL_SUPPORT
