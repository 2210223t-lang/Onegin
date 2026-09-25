#ifndef STUFF_H
#define STUFF_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum Getoptdef
{
    INPUT = 10,
    OUTPUT = 11,
    InAndOut = 12,
};

enum Error
{
    Too_Many_Attempts = -20,
    Getopt_Failure = -25,
    Success = 0,
    LindLeapfrog = 14,
    RindLeapfrog = 15,
    QsortError = 16,
};

struct iostream
{
    char istream_name[ PATH_MAX ];
    int istream;
    char ostream_name[ PATH_MAX ];
    FILE* ostream;
};

struct frag
{
    char* begin;
    char* end;
};

struct poem
{
    char* txt;
    uint64_t cpp;
};

#endif // STUFF_H
