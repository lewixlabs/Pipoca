#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int len, const char* args[])
{
    // not enough parameters
    if (len < 3)
    {
        printf("pipoca [random string length] [number of rows to generate]\n");
        return 0;
    }

    unsigned int seedInt = time(NULL)%1000;
    unsigned int rowNumber, colNumber;
    for (rowNumber = 0; rowNumber < atoi(args[2]); rowNumber++)
    {
        for (colNumber = 0; colNumber < atoi(args[1]); colNumber++)
        {
            //unsigned int currentSeed = time();
            printf("%i",rand_r(&seedInt)%10);
        }
        printf("\n");
    }
}