#ifndef TERMINAL_H
#define TERMINAL_H

#include <limits.h>

enum Error
{
    Too_Many_Attempts = -20,
    Getopt_Failure = -25,
    Success = 0,
};

struct stream
{
    char istream_name[ PATH_MAX ];
    int istream;
    char ostream_name[ PATH_MAX ];
    FILE* ostream;
};

struct stream Terminal( int argc, char** argv, char* input, char* output );
int OpenCheck( struct stream* InAndOut );

#endif // TERMINAL_H
