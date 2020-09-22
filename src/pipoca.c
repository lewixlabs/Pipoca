#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "include/pipoca.h"

static const char numbersArray[] = "0123456789";
static const char alphanumericArray[] = "0123456789abcdefghijklmnopqrstuvwxyz";

void printRandomStrings(unsigned int nRows, unsigned int nChars, unsigned char numbersOnly){
    
    unsigned int rowNumber, colNumber;

    char* p_RandomString = malloc(nChars+1);

    srand(time(NULL));

    for (rowNumber = 0; rowNumber < nRows; rowNumber++)
    {
        memset(p_RandomString,0x00,nChars+1);
        for (colNumber = 0; colNumber < nChars; colNumber++)
            *(p_RandomString+colNumber) = numbersOnly ? numbersArray[rand()%10] : alphanumericArray[rand()%strlen(alphanumericArray)];
        p_RandomString[nChars] = '\0';

        printf("%s",p_RandomString);
        printf("\n");
    }

    free(p_RandomString);
}

int main(int len, const char* args[])
{
    int prmNRows, prmLString;
    unsigned char numbersOnly = 0;

    // not enough parameters
    if (len < 3)
    {
        printf("pipoca <random string length> <number of rows to generate> [--numbers-only]\n");
        return 1;
    }

    if (len > 3 && strcmp(args[3],"--numbers-only"))
    {
        printf("pipoca <random string length> <number of rows to generate> [--numbers-only]\n");
        return 1;
    }

    // check limits
    prmNRows = atoi(args[2]);
    prmLString = atoi(args[1]);

    if (prmNRows <= 0 || prmNRows > MAX_ROWS || prmLString <= 0 || prmLString > MAX_STRING_LENGTH)
    {
        printf("pipoca [random string 1-%i] [number of rows to generate 1-%i]\n",MAX_STRING_LENGTH,MAX_ROWS);
        return 1;
    }

    numbersOnly = len > 3 && !strcmp(args[3],"--numbers-only");
    printRandomStrings(prmNRows,prmLString,numbersOnly);
}