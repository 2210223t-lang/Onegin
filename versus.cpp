#include <stdio.h>
#include <stdlib.h>

#include "Qsort/textfunc.h"


void PrintMicro( FILE* ostream )
{
    struct poem oven = ReadText_Buff( "MicroWave.txt" );
    fprintf( ostream, "Our first participant, Oven: \n\n" );
    fprintf( ostream, "%s", oven.txt );
}
