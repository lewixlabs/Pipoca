#ifndef THREADMANAGER_DATA
#define THREADMANAGER_DATA

struct thread_params
{
    enum enStringTypes stringType;
    char* pAllocatedChar;
};

void ThreadManager_randomString(const struct stParams *paramsToUse, char* allocatedString);

#endif