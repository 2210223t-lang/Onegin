#include <cstddef>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Colours.h"
#include "CommandLine/Terminal.h"
#include "Qsort/Qsort.h"
#include "Qsort/comp.h"
#include "versus.h"
#include "textfunc.h"
#include "debug.h"


int main( int argc, char** argv )
{
    struct stream InAndOut ={};
    Terminal( argc, argv, InAndOut.istream_name, InAndOut.ostream_name );

    int status = OpenCheck( &InAndOut );

    if ( status != Success )
        return 1;

    struct poem line = ReadText_Buff( InAndOut.istream, InAndOut.istream_name );

    struct frag* lines = Divide( line );
    int count = CountLines( line );

    fprintf( stderr, "Count = %d\n", count );

    my_qsort( lines, count, sizeof( frag ), cmpstringDOWN_frag );

    Print_poem( lines, count, InAndOut.ostream );

    fprintf( InAndOut.ostream, VERSUS_START );

    PrintMicro( InAndOut.ostream );

    qsort( lines, count, sizeof( frag ), MC_PUSHKIN_frag );

    Print_poem( lines, count, InAndOut.ostream );

    fprintf( InAndOut.ostream, VERSUS_FINAL );

    fprintf( InAndOut.ostream, "%s", line.txt );


    free( line.txt );
    fclose( InAndOut.ostream );
    return 0;
}

