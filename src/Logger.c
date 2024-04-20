/**
 * @file Logger.c
 *
 * @brief Minimal ANSI C logger.
 *
 ******************************************************************************/

/* Includes
 ******************************************************************************/

#include "Logger.h"

#ifdef LOGGER
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#endif

/* Defines
 ******************************************************************************/

#define LOGGER_UNUSED(x) (void)(x)

#define LOGGER_ANSI_RESET  "\e[0m"
#define LOGGER_ANSI_RED    "\e[0;31m"
#define LOGGER_ANSI_YELLOW "\e[0;33m"
#define LOGGER_ANSI_GREEN  "\e[0;32m"
#define LOGGER_ANSI_BLUE   "\e[0;34m"
#define LOGGER_ANSI_PURPLE "\e[0;35m"

/* Typedefs
 ******************************************************************************/

typedef enum
{
  LOGGER_MODE_PRINT,
  LOGGER_MODE_CUSTOM
} Logger_Mode_t;

/* Globals
 ******************************************************************************/

#ifdef LOGGER
static const char *Logger_AnsiColorLut[] = {LOGGER_ANSI_RED, LOGGER_ANSI_YELLOW, LOGGER_ANSI_GREEN, LOGGER_ANSI_BLUE, LOGGER_ANSI_PURPLE};

static const char *Logger_PrefixFormat = "%s[%.6lf] %s: ";
static const char *Logger_PostfixFormat = "%s\n";

static Logger_Mode_t Logger_Mode = LOGGER_MODE_PRINT;
static Logger_Level_t Logger_Level = LOGGER_LEVEL_VERBOSE;

static void (*Logger_CustomLog)(const char *const buffer, const size_t size) = NULL; /* Client-specified logging function, not be called directly */
static char *Logger_CustomLogBuffer = NULL;
static size_t Logger_CustomLogBufferSize = 0UL;
#endif

/* Function Prototypes
 ******************************************************************************/

#ifdef LOGGER
static inline double Logger_GetTime(void);
static inline void Logger_Print(const char *const tag, const Logger_Level_t level, const char *const format, va_list args);
static inline void Logger_Custom(const char *const tag, const Logger_Level_t level, const char *const format, va_list args);
#endif

/* Function Definitions
 ******************************************************************************/

void Logger_SetLogLevel(const Logger_Level_t level)
{
#ifdef LOGGER
  Logger_Level = level;
#else
  LOGGER_UNUSED(level);
#endif
}

void Logger_RegisterCustomLogger(void (*log)(const char *const buffer, const size_t size), char *const buffer, const size_t size)
{
#ifdef LOGGER
  if (log != NULL && buffer != NULL)
  {
    Logger_CustomLog = log;
    Logger_CustomLogBuffer = buffer;
    Logger_CustomLogBufferSize = size;
    Logger_Mode = LOGGER_MODE_CUSTOM;
  }
#else
  LOGGER_UNUSED(log);
  LOGGER_UNUSED(buffer);
  LOGGER_UNUSED(size);
#endif
}

void Logger_Log(const char *const tag, const Logger_Level_t level, char *const format, ...)
{
#ifdef LOGGER
  if (tag != NULL && format != NULL && level <= Logger_Level)
  {
    va_list args;

    va_start(args, format);

    switch (Logger_Mode)
    {
    case LOGGER_MODE_PRINT:
      Logger_Print(tag, level, format, args);
      break;
    case LOGGER_MODE_CUSTOM:
      Logger_Custom(tag, level, format, args);
      break;
    default:
      break;
    }

    va_end(args);
  }
#else
  LOGGER_UNUSED(tag);
  LOGGER_UNUSED(level);
  LOGGER_UNUSED(format);
#endif
}

#ifdef LOGGER
static inline double Logger_GetTime(void)
{
  return (double)(clock()) / (double)CLOCKS_PER_SEC;
}

static inline void Logger_Print(const char *const tag, const Logger_Level_t level, const char *const format, va_list args)
{
  printf(Logger_PrefixFormat, Logger_AnsiColorLut[level], Logger_GetTime(), tag);
  vprintf(format, args);
  printf(Logger_PostfixFormat, LOGGER_ANSI_RESET);
}

static inline void Logger_Custom(const char *const tag, const Logger_Level_t level, const char *const format, va_list args)
{
  int64_t size;

  size = snprintf(Logger_CustomLogBuffer, Logger_CustomLogBufferSize, Logger_PrefixFormat, Logger_AnsiColorLut[level], Logger_GetTime(), tag);
  if (size > 0L)
  {
    Logger_CustomLog(Logger_CustomLogBuffer, (size_t)size);
  }

  size = vsnprintf(Logger_CustomLogBuffer, Logger_CustomLogBufferSize, format, args);
  if (size > 0L)
  {
    Logger_CustomLog(Logger_CustomLogBuffer, (size_t)size);
  }

  size = snprintf(Logger_CustomLogBuffer, Logger_CustomLogBufferSize, Logger_PostfixFormat, LOGGER_ANSI_RESET);
  if (size > 0L)
  {
    Logger_CustomLog(Logger_CustomLogBuffer, (size_t)size);
  }
}
#endif