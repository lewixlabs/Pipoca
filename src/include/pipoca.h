#ifndef PIPOCA_DATA
#define PIPOCA_DATA

#define MAX_ROWS 100000000
#define MAX_STRING_LENGTH 64

#define STRING_LENGTH_PARAM "-c"
#define ROWS_LENGTH_PARAM "-r"
#define NUMBERS_ONLY_PARAM "-n"

enum enStringTypes
{
    number,
    alphanumeric
};

struct stParams
{
    enum enStringTypes stringType;
    int nChars;
    int nRows;
};

#endif