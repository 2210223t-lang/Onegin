#include <cstddef>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/mman.h>

#include "CommandLine/Terminal.h"
#include "Qsort/Qsort.h"
#include "Qsort/comp.h"
#include "versus.h"
#include "textfunc.h"
#include "debug.h"
#include "Stuff.h"


int localbuff( int argc, char** argv, struct iostream* InAndOut )
{
    assert( argv );
    assert( InAndOut );

    Terminal( argc, argv, InAndOut->istream_name, InAndOut->ostream_name );

    int status = OpenCheck( InAndOut );

    if ( status != Success )
        return 1;

    struct poem line = ReadText_Buff( InAndOut->istream, InAndOut->istream_name );

    struct frag* lines = Divide( line );
    int count = CountLines( line );

    PrintAllText( InAndOut, lines, line, count );

    free( line.txt );
    fclose( InAndOut->ostream );
    return 0;
}

int Nobuff( int argc, char** argv, struct iostream* InAndOut )
{

    int status = OpenCheck( InAndOut );

    if ( status != Success )
        return 1;

    struct poem line = ReadText_mmap( InAndOut->istream, InAndOut->istream_name );
    struct frag* lines = Divide( line );
    int count = CountLines( line );

    PrintAllText( InAndOut, lines, line, count );

    munmap( line.txt, line.cpp );
    close( InAndOut->istream );
    fclose( InAndOut->ostream );
    return 0;
}
