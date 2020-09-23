#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "include/pipoca.h"

static const char numbersArray[] = "0123456789";
static const char alphanumericArray[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

 struct stParams Main_ParseArgs(int len, const char* args[])
 {
    struct stParams params;
    params.stringType = alphanumeric;
    params.nRows = params.nChars = -1;

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
    }

    return params;
 }

void printRandomStrings(const struct stParams *paramsToUse){
    
    unsigned int rowNumber, colNumber;

    char* p_RandomString = malloc(paramsToUse->nChars+1);

    srand(time(NULL));
    memset(p_RandomString,0x00,paramsToUse->nChars+1);

    switch (paramsToUse->stringType)
    {
    case number:
        for (rowNumber = 0; rowNumber < paramsToUse->nRows; rowNumber++)
        {
            for (colNumber = 0; colNumber < paramsToUse->nChars; colNumber++)
                *(p_RandomString+colNumber) = numbersArray[rand()%strlen(numbersArray)];

            printf("%s\n",p_RandomString);
        }
        break;
    
    default: // alphanumeric
        for (rowNumber = 0; rowNumber < paramsToUse->nRows; rowNumber++)
        {
            for (colNumber = 0; colNumber < paramsToUse->nChars; colNumber++)
                *(p_RandomString+colNumber) = alphanumericArray[rand()%strlen(alphanumericArray)];

            printf("%s\n",p_RandomString);
        }
        break;
    }

    free(p_RandomString);
}

int main(int len, const char* args[])
{
    // not enough parameters
    if (len < 3)
    {
        printf("pipoca <random string length> <number of rows to generate> [--numbers-only]\n");
        return 1;
    }

    // check params & limits
    struct stParams paramsReceived = Main_ParseArgs(len,args);
    if (paramsReceived.nRows <= 0 || paramsReceived.nRows > MAX_ROWS || paramsReceived.nChars <= 0 || paramsReceived.nChars > MAX_STRING_LENGTH)
    {
        printf("pipoca [random string 1-%i] [number of rows to generate 1-%i]\n",MAX_STRING_LENGTH,MAX_ROWS);
        return 1;
    }

    printRandomStrings(&paramsReceived);
    return 0;
}