#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "textfunc.h"


void PrintMicro( FILE* ostream )
{
    assert( ostream );
    struct poem oven = ReadText_Buff( "MicroWave.txt" );
    fprintf( ostream, "Our first participant, Oven: \n\n" );
    fprintf( ostream, "%s", oven.txt );
    fprintf( ostream, "Round!!\n\n LET'S MOVE ON TO THE NEXT PARTICIPANT\n\n");
}
