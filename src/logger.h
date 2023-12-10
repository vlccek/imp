#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "setting.hpp"

#ifndef LOGGER_IMP
#define LOGGER_IMP

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


//macro for coloring text
#define Coloring(COLOR, TEXT) COLOR TEXT RESET

#define ERR_TEXT "------------------------"


/**
 * @brief Init logger
 *
 */
inline void logger_init() {
#if logging_on
    while (!Serial) { ; // wait for serial port to connect. Needed for native USB
    }
#endif
}


// 1. InternalError - problem cant be solved, restart
#define FATAL_ERROR(message, ...) \
    do { \
    Serial.printf(Coloring(RED, "ERR IN: | %15s:%-3d | in %s() | " message "\n" ), \
                __FILE__, \
                __LINE__, \
                __FUNCTION__, ##__VA_ARGS__); \
        ESP.restart(); \
    } while (0)


/**
 * @brief Error - problem can be solved, continue
 */
#define ERROR(message, ...) \
    do { \
    Serial.printf(Coloring(RED, "ERR IN: | %15s:%-3d | in %s() | " message "\n"), \
                __FILE__, \
                __LINE__, \
                __FUNCTION__, ##__VA_ARGS__); \
    } while (0)



// loging
/**
 * @brief Loging
 *
 */
#define loging(message, args...) \
    do { \
        if (logging_on) { \
            Serial.printf("LOG IN: | %15s:%-3d | in %s() | " message "\n" , \
                     __FILE__, \
                     __LINE__, \
                     __FUNCTION__, ##args); \
        } \
    } while (0)

#endif