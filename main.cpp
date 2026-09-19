#include <stdio.h>
#include <stdlib.h>

#include "Qsort/Qsort.h"
#include "debug.h"
#include "Qsort/textfunc.h"
#include "Qsort/comp.h"
#include "versus.h"

#define PUSH_LINE 3


int main()
{
    FILE* text = fopen( "try.txt", "r" );
    FILE* output = fopen( "draft.txt", "w" );
    char* ind[ PUSH_LINE ] = {};

    int lines = ReadText( ind, PUSH_LINE, text );
    fclose( text );

    my_qsort( ind, lines, sizeof( ind[ 0 ] ), MC_PUSHKIN );

    for ( int i = 0; i < lines; i++ )
        printf( "%s", ind[ i ] );



    // fprintf( output, VERSUSSTART );

    // my_qsort( ind, lines, sizeof( ind[ 0 ] ), MC_PUSHKIN );

    fclose( output );
    return 0;
}
