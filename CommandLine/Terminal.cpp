#include <cstddef>
#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>
#include <unistd.h>
#include <sys/mman.h>

#include "../debug.h"
#include "COTexGetopt.h"
#include "../Stuff.h"


/// defines how many mistakes the user can make during inputting wrong filename
#define MAX_MISTAKES 3

/**
 * @brief Parses command line arguments and checks input
 *
 * @param[ in ] argc - std argc
 *
 * @param[ in ] argv - std argv
 *
 * @param[ out ] input char[ PATH_MAX ] - name of input filestream
 *
 * @param[ out ] output char[ PATH_MAX ] - name of output filestream
 */
int Terminal( int argc, char** argv, char input[ PATH_MAX ], char output[ PATH_MAX ] )
{
    assert( argv );
    assert( input );
    assert( output );

    strcpy( input, "Texts/pushkin.txt" );
    strcpy( output, "Texts/output.txt" );

    struct option long_options[] = { {  "input", required_argument, 0, 'i' },
                                     { "output", required_argument, 0, 'o' },
                                     {   "mmap",       no_argument, 0, 'm' },
                                     {   "buff",       no_argument, 0, 'b' },
                                     {        0,                 0, 0,  0 } };

    int check = 0;
    bool keepgoing = true;
    int retval = 'm'; /// Defines original running mode

    while ( keepgoing && ( check = getopt_long_only( argc, argv, "io", long_options, NULL ) ) != -1 )
    {

        switch ( check )
        {
            case 'm':
                retval = 'm';
                break;

            case 'b':
                retval = 'b';
                break;

            case 'i':
                strcpy( input, optarg );
                break;

            case 'o':
                strcpy( output, optarg );
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
    return retval;
}

/**
 * @brief Checks either files were open correctly or not
 */
int OpenCheck( struct iostream* InAndOut )
{
    assert( InAndOut );

    char buff[ PATH_MAX ] = "";
    int mistCount = MAX_MISTAKES;

    InAndOut->istream = open( InAndOut->istream_name, O_RDONLY );
    InAndOut->ostream = fopen( InAndOut->ostream_name, "w" );

    while ( InAndOut->istream == -1 && mistCount > 0 )
    {
        printf( "You enterred wrong filename for output: %s can't be opened, try to enter again: ",
                 InAndOut->istream_name );
        scanf( "%s", buff );
        InAndOut->istream = open( buff, O_RDONLY );
        strcpy( InAndOut->istream_name, buff );
        mistCount--;
    }

    while ( !InAndOut->ostream && mistCount > 0 )
    {
        printf( "You enterred wrong filename for output: %s can't be opened, try to enter again: ", InAndOut->ostream_name );
        scanf( "%s", buff );
        InAndOut->ostream = fopen( buff, "w" );
        strcpy( InAndOut->ostream_name, buff );
        mistCount--;
    }

    if ( mistCount <= 0 )
    {
        printf( "Too many attempts\n" );
        return Too_Many_Attempts;
    }

    return Success;
}
