#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "include/pipoca.h"
#include "include/threadmanager.h"

/*
 * With threads it's slower, to investigate
 */ 

volatile int running_threads = 0;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;

void* randomChar(void* pThreadParams)
{
    pthread_mutex_lock(&running_mutex);

    struct thread_params* threadPrm = (struct thread_params*)pThreadParams;

    *threadPrm->pAllocatedChar = threadPrm->stringType == alphanumeric ? ALPHANUMERIC_ARRAY[rand()%strlen(ALPHANUMERIC_ARRAY)] : NUMBERS_ARRAY[rand()%strlen(NUMBERS_ARRAY)];
    //printf("randomChar() char: %c\n",*threadPrm->pAllocatedChar);

    running_threads--;
    pthread_mutex_unlock(&running_mutex);


    return NULL;
}

void ThreadManager_randomString(const struct stParams *paramsToUse, char allocatedString[])
{
    pthread_t threads[paramsToUse->nChars];
    struct thread_params currentThreadParams[paramsToUse->nChars];
    int idxThread;

    running_threads = paramsToUse->nChars;

    
    for(idxThread = 0; idxThread < paramsToUse->nChars; idxThread++)
    {
        currentThreadParams[idxThread].stringType = paramsToUse->stringType;
        currentThreadParams[idxThread].pAllocatedChar = allocatedString+idxThread;

        pthread_create(&threads[idxThread],NULL,randomChar,&currentThreadParams[idxThread]);
    }
        

    while (running_threads > 0);
    // {
    //     usleep(1);
    // }
    //printf("ThreadManager_randomString(): %s\n",allocatedString);
}