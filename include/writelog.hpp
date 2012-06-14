#ifndef JP_WRITELOG
#define JP_WRITELOG

const int LOG_DEBUG = 0;
const int LOG_MESSAGE = 1;
const int LOG_INFO = 2;
const int LOG_WARN = 3;
const int LOG_ERROR = 4;


void writelog(int level, std::string message);

#endif
