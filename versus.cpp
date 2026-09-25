#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include "Qsort/Qsort.h"
#include "Qsort/comp.h"
#include "textfunc.h"

#define VERSUS_START "---------\n\n"\
                     "I'm glad to see you on a versus battle, make some noise!!!!\n\n"\
                     "To my right stands the man, who spent decades in the shadows, warming up people's dishes,"\
                     "but today he came to heat up this stage.\n"\
                     "Ladies and gentlemen, make some noise for the one and only Microwave Oven!!!\n\n"\
                     "To my left stands the risen legend, the ancestor of the Russian rap.\n"\
                     "Make some noise, cause it's Alexandr Pushkin!!!!\n\n"

#define VERSUS_FINAL "Round, bitch\n\n"\
                     "Public: WHOOOOAH"\
                     "\n-----\n\n"


void PrintMicro( FILE* ostream )
{
    assert( ostream );
    int Oven_desc = open( "Texts/MicroWave.txt", O_RDONLY );
    struct poem oven = ReadText_Buff( Oven_desc, "MicroWave.txt" );
    fprintf( ostream, "Our first participant, Oven: \n\n" );
    fprintf( ostream, "%s", oven.txt );
    fprintf( ostream, "Round!!\n\n LET'S MOVE ON TO THE NEXT PARTICIPANT\n\n");
}

void PrintVersus( FILE* ostream, struct frag* lines, int count )
{
    fprintf( ostream, VERSUS_START );

    PrintMicro( ostream );

    qsort( lines, count, sizeof( frag ), MC_PUSHKIN_frag );

    Print_poem( lines, count, ostream );

    fprintf( ostream, VERSUS_FINAL );
}

void PrintAllText( struct iostream* InAndOut, struct frag* lines, struct poem line, int count )
{
    fprintf( stderr, "Count = %d\n", count );

    my_qsort( lines, count, sizeof( frag ), cmpstringDOWN_frag );

    Print_poem( lines, count, InAndOut->ostream );

    PrintVersus( InAndOut->ostream, lines, count );

    fprintf( InAndOut->ostream, "%s", line.txt );
}
