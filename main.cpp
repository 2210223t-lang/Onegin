#include <stdio.h>
#include <stdlib.h>

#include "Qsort/Qsort.h"
#include "debug.h"
#include "Qsort/textfunc.h"
#include "Qsort/comp.h"

#define PUSH_LINE 3


int main()
{
    FILE* text = fopen( "try.txt", "r" );
    char* ind[ PUSH_LINE ] = {};
    ReadText( ind, PUSH_LINE, text );
    $RT
    my_qsort( ind, PUSH_LINE, sizeof( ind[ 0 ] ), cmpstringUP );

    $RT
    FILE* output = fopen( "draft.txt", "w" );

    for ( int i = 0; i < PUSH_LINE; i++ )
        fprintf( output, "%s", ind[ i ] );


    fclose( text );
    fclose( output );
    return 0;
}
