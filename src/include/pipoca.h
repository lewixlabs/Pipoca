#ifndef PIPOCA_DATA
#define PIPOCA_DATA

#define MAX_ROWS 100000000
#define MAX_STRING_LENGTH 64

#define STRING_LENGTH_PARAM     "-c"
#define ROWS_LENGTH_PARAM       "-r"
#define NUMBERS_ONLY_PARAM      "-n"
#define LOWERCASE_ONLY_PARAM    "-l"
#define OVERWRITE_TO_FILE       "-o"
#define APPEND_TO_FILE          "-a"

enum enBoolean
{
    false   = 0,
    true    = 1
};
typedef enum enBoolean bool;

enum enStringTypes
{
    number,
    alphanumeric,
    lowercase
};

struct stParams
{
    enum enStringTypes stringType;
    const char *fileToWrite;
    int nChars;
    int nRows;
    bool appendToFile;
};

#define NUMBERS_ARRAY "0123456789"
#define ALPHANUMERIC_ARRAY "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

#endif