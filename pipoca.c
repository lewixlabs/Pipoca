#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_ROWS 100000000
#define MAX_STRING_LENGTH 100

void printRandomStrings(unsigned int nRows, unsigned int nChars){
    
    unsigned int rowNumber, colNumber;

    srand(time(NULL));

    for (rowNumber = 0; rowNumber < nRows; rowNumber++)
    {
        for (colNumber = 0; colNumber < nChars; colNumber++)
        {
            //unsigned int currentSeed = time();
            printf("%i",rand()%10);
        }
        printf("\n");
    }
}

int main(int len, const char* args[])
{
    int prmNRows, prmLString;

    // not enough parameters
    if (len < 3)
    {
        printf("pipoca [random string length] [number of rows to generate]\n");
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

    printRandomStrings(prmNRows,prmLString);
}