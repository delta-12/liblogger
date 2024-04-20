#include "Logger.h"

const char *test_Logger_Tag = "test_Logger_Tag";

int main()
{
    int i = 0U;
    LOGGER_LOG_ERROR(test_Logger_Tag, "ERROR: %d", i);
    i++;
    LOGGER_LOG_WARNING(test_Logger_Tag, "WARNING: %d", i);
    i++;
    LOGGER_LOG_INFO(test_Logger_Tag, "INFO: %d", i);
    i++;
    LOGGER_LOG_DEBUG(test_Logger_Tag, "DEBUG: %d", i);
    i++;
    LOGGER_LOG_VERBOSE(test_Logger_Tag, "VERBOSE: %d", i);

    return 0;
}