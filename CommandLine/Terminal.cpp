#include <cstddef>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

#include "../debug.h"
#include "COTexGetopt.h"

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
};

struct stream
{
    char istream_name[ PATH_MAX ];
    int istream;
    char ostream_name[ PATH_MAX ];
    FILE* ostream;
};

/// defines how many mistakes the user can make during inputting wrong filename
#define MAX_MISTAKES 3


void Terminal( int argc, char** argv, char* input, char* output )
{
    assert( argv );
    assert( input );
    assert( output );

    strcpy( input, "pushkin.txt" );
    strcpy( output, "output.txt" );

    struct COTexOption long_options[] = { {  "input", required_argument, 0,  'i' },
                                     { "output", required_argument, 0,  'o' },
                                     {        0,                 0, 0,   0 } };

    int check = 0;
    bool keepgoing = true;

    while ( keepgoing && ( check = COTexGetopt_long_only( argc, argv, long_options, NULL ) ) != -1 )
    {

        switch ( check )
        {
            case 'i':
                strcpy( input, COTexoptarg );
                break;
            case 'o':
                strcpy( output, COTexoptarg );
                break;

            case '?':
                printf( "Incorrect parsing flag in getopt\n" );
                keepgoing = false;

            default:
                fprintf( stderr, "Getopt failure\n" );
                keepgoing = false;
        }
    }
    // fprintf( stderr, "Output filename - %s\nInput filename - %s\n", output, input );

}

/**
 * @brief Checks either files were open correctly or not
 */
int OpenCheck( struct stream* InAndOut )
{
    assert( InAndOut );

    char buff[ PATH_MAX ] = "";
    int mistCount = MAX_MISTAKES;

    InAndOut->ostream = fopen( InAndOut->ostream_name, "w" );
    InAndOut->istream = open( InAndOut->istream_name, O_RDONLY );

    while ( !InAndOut->ostream && mistCount > 0 )
    {
        printf( "You enterred wrong filename for output: %s can't be opened, try to enter again: ", InAndOut->ostream_name );
        scanf( "%s", buff );
        InAndOut->ostream = fopen( buff, "w" );
        strcpy( InAndOut->ostream_name, buff );
        mistCount--;
    }

    while ( InAndOut->istream == -1 && mistCount > 0 )
    {
        printf( "You enterred wrong filename for output: %s can't be opened, try to enter again: ",
                 InAndOut->istream_name );
        scanf( "%s", buff );
        InAndOut->istream = open( buff, O_RDONLY );
        strcpy( InAndOut->istream_name, buff );
        mistCount--;
    }



    if ( mistCount <= 0 )
    {
        printf( "Too many attempts\n" );
        return Too_Many_Attempts;
    }

    return Success;
}
