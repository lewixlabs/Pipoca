#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include "include/pipoca.h"
//#include "include/threadmanager.h"


 struct stParams ParseArgs(int len, const char* args[])
 {
    struct stParams params;
    params.stringType = alphanumeric;
    params.nRows = params.nChars = -1;
    params.appendToFile = false;

    for(int i = 1;i < len; i++)
    {
        // -c [string length] or -c[string length]
        if (!strncmp(args[i],STRING_LENGTH_PARAM,strlen(STRING_LENGTH_PARAM)))
        {
            if (strlen(args[i]) == strlen(STRING_LENGTH_PARAM))
            {
                params.nChars = atoi(args[i+1]);
                i++;
            }
            else
            {
                params.nChars = atoi(&args[i][2]);
            }
            
            continue;
        }

        // -r [rows length] or -r[string length]
        if (!strncmp(args[i],ROWS_LENGTH_PARAM,strlen(ROWS_LENGTH_PARAM)))
        {
            if (strlen(args[i]) == strlen(ROWS_LENGTH_PARAM))
            {
                params.nRows = atoi(args[i+1]);
                i++;
            }
            else
            {
                params.nRows = atoi(&args[i][2]);
            }
            
            continue;
        }

        // -n [numbers only]
        if (!strcmp(args[i],NUMBERS_ONLY_PARAM))
        {
            params.stringType = number;
            continue;
        }

        // -l [lowercase only]
        if (!strcmp(args[i],LOWERCASE_ONLY_PARAM))
        {
            params.stringType = lowercase;
            continue;
        }

        // -o [file name to overwrite]
        if (!strncmp(args[i],OVERWRITE_TO_FILE,strlen(OVERWRITE_TO_FILE)))
        {
            if (strlen(args[i]) == strlen(OVERWRITE_TO_FILE))
            {
                params.fileToWrite = args[i+1];
                i++;
            }
            else
            {
                params.fileToWrite = &args[i][2];
            }
            
            continue;
        }

        // -a [file name to append]
        if (!strncmp(args[i],APPEND_TO_FILE,strlen(APPEND_TO_FILE)))
        {
            if (strlen(args[i]) == strlen(APPEND_TO_FILE))
            {
                params.fileToWrite = args[i+1];
                i++;
            }
            else
            {
                params.fileToWrite = &args[i][2];
            }
            
            params.appendToFile = true;
            continue;
        }
    }

    return params;
 }

char PrintRandomStrings(const struct stParams *paramsToUse){
    
    FILE *pf = NULL;
    unsigned int rowNumber, colNumber;

    // fix "Overflow in uncontrolled allocation size" by Github CodeQL (CWE-190)
    if (paramsToUse == NULL || paramsToUse->nChars > MAX_STRING_LENGTH)
        return -2;

    char* p_RandomString = malloc(paramsToUse->nChars + 2);// n chars + carriage return + string terminator

    printf("Pipoca 🍿 is working...\n");
    
    time_t secondsStart,secondsStop;
    secondsStart =  time(NULL);

    if (paramsToUse->fileToWrite != NULL && strlen(paramsToUse->fileToWrite) > 0)
    {
        pf = fopen(paramsToUse->fileToWrite,paramsToUse->appendToFile ? "a" : "w");
        if (pf == NULL)
        {
            printf("file open error\n");
            return -1;
        }
    }
        

    srand(time(NULL));
    memset(p_RandomString,0x00,paramsToUse->nChars + 2);

    switch (paramsToUse->stringType)
    {
    case number:
        for (rowNumber = 0; rowNumber < paramsToUse->nRows; rowNumber++)
        {
            //ThreadManager_randomString(paramsToUse,p_RandomString);
            for (colNumber = 0; colNumber < paramsToUse->nChars; colNumber++)
                *(p_RandomString+colNumber) = NUMBERS_ARRAY[rand()%strlen(NUMBERS_ARRAY)];

            *(p_RandomString+paramsToUse->nChars) = '\n';

            pf != NULL ? fputs(p_RandomString,pf) : printf("%s\n",p_RandomString);
        }
        break;

    case lowercase: // alphanumeric
        for (rowNumber = 0; rowNumber < paramsToUse->nRows; rowNumber++)
        {
            for (colNumber = 0; colNumber < paramsToUse->nChars; colNumber++)
                *(p_RandomString+colNumber) = tolower(ALPHANUMERIC_ARRAY[rand()%strlen(ALPHANUMERIC_ARRAY)]);

            *(p_RandomString+paramsToUse->nChars) = '\n';

            pf != NULL ? fputs(p_RandomString,pf) : printf("%s\n",p_RandomString);
        }
        break;
    
    default: // alphanumeric
        for (rowNumber = 0; rowNumber < paramsToUse->nRows; rowNumber++)
        {
            for (colNumber = 0; colNumber < paramsToUse->nChars; colNumber++)
                *(p_RandomString+colNumber) = ALPHANUMERIC_ARRAY[rand()%strlen(ALPHANUMERIC_ARRAY)];
            
            *(p_RandomString+paramsToUse->nChars) = '\n';

            pf != NULL ? fputs(p_RandomString,pf) : printf("%s\n",p_RandomString);
        }
        break;
    }

    if (pf != NULL)
    {
        fflush(pf);
        fclose(pf);
    }
        
    secondsStop =  time(NULL);
    printf("Elapsed time to produce %i rows of %i chars: %lds\n",paramsToUse->nRows,paramsToUse->nChars,secondsStop-secondsStart);

    free(p_RandomString);
    
    return 0;
}

/*
 * Help
 */

void PrintHelp()
{
    printf("Pipoca 🍿\n");
    printf("pipoca [options] -r <number_of_rows> -c <number_of_chars>\n");
    printf("\nOptional params:\n");
    printf("-o <file_to_write>: save rows to a file (overwrite mode)\n");
    printf("-a <file_to_write>: save rows to a file (append mode)\n");
    printf("-n : numbers only (default is alphanumeric)\n");
    printf("-l : lowercase chars only\n");
    printf("\n");
}

int main(int len, const char* args[])
{
    // not enough parameters
    if (len < 3)
    {
        PrintHelp();
        return 1;
    }

    // check params & limits
    struct stParams paramsReceived = ParseArgs(len,args);
    if (paramsReceived.nRows <= 0 || paramsReceived.nRows > MAX_ROWS || paramsReceived.nChars <= 0 || paramsReceived.nChars > MAX_STRING_LENGTH)
    {
        PrintHelp();
        return 1;
    }

    return PrintRandomStrings(&paramsReceived);
}