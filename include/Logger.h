/**
 * @file Logger.h
 *
 * @brief ANSI C logger.
 *
 ******************************************************************************/

#ifndef LOGGER_H
#define LOGGER_H

/* Includes
 ******************************************************************************/

#include <stdlib.h>

/* Typedefs
 ******************************************************************************/

typedef enum
{
  LOGGER_LEVEL_ERROR,
  LOGGER_LEVEL_WARNING,
  LOGGER_LEVEL_INFO,
  LOGGER_LEVEL_DEBUG,
  LOGGER_LEVEL_VERBOSE
} Logger_Level_t;

/* Function Prototypes
 ******************************************************************************/

void Logger_SetLogLevel(const Logger_Level_t level);
void Logger_RegisterCustomLogger(void (*log)(const char *const buffer, const size_t size), char *const buffer, const size_t size);
void Logger_Log(const char *const tag, const Logger_Level_t level, char *const format, ...);

#ifdef LOGGER
#define LOGGER_LOG_ERROR(tag, format, ...)   Logger_Log(tag, LOGGER_LEVEL_ERROR, format, __VA_ARGS__)
#define LOGGER_LOG_WARNING(tag, format, ...) Logger_Log(tag, LOGGER_LEVEL_WARNING, format, __VA_ARGS__)
#define LOGGER_LOG_INFO(tag, format, ...)    Logger_Log(tag, LOGGER_LEVEL_INFO, format, __VA_ARGS__)
#define LOGGER_LOG_DEBUG(tag, format, ...)   Logger_Log(tag, LOGGER_LEVEL_DEBUG, format, __VA_ARGS__)
#define LOGGER_LOG_VERBOSE(tag, format, ...) Logger_Log(tag, LOGGER_LEVEL_VERBOSE, format, __VA_ARGS__)
#else
#define LOGGER_LOG_ERROR(tag, format, ...)   ;
#define LOGGER_LOG_WARNING(tag, format, ...) ;
#define LOGGER_LOG_INFO(tag, format, ...)    ;
#define LOGGER_LOG_DEBUG(tag, format, ...)   ;
#define LOGGER_LOG_VERBOSE(tag, format, ...) ;
#endif

#endif