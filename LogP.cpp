#include "LogP.h"

LOG::logLevel LogProxy::currentLevel = LOG::ERROR;

bool LogProxy::logMillisec = true;
bool LogProxy::logThreadId = true;
bool LogProxy::logFilename = false;
bool LogProxy::logLinenum = false;
bool LogProxy::logPrettyFunc = true;
