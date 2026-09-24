#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>

#include "textfunc.h"


void PrintMicro( FILE* ostream )
{
    assert( ostream );
    int Oven_desc = open( "MicroWave.txt", O_RDONLY );
    struct poem oven = ReadText_Buff( Oven_desc, "MicroWave.txt" );
    fprintf( ostream, "Our first participant, Oven: \n\n" );
    fprintf( ostream, "%s", oven.txt );
    fprintf( ostream, "Round!!\n\n LET'S MOVE ON TO THE NEXT PARTICIPANT\n\n");
}
