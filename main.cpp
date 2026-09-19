#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Qsort/Qsort.h"
#include "debug.h"
#include "Qsort/textfunc.h"
#include "Qsort/comp.h"
#include "versus.h"

#define PUSH_LINE 3


int main()
{
    FILE* text = fopen( "pushkin.txt", "r" );
    assert( text );
    FILE* output = fopen( "output.txt", "w" );
    assert( output );

    char* ind[ PUSH_LINE ] = {};
    char* ind_backup[ PUSH_LINE ] = {};

    int lines = ReadText_Separated( ind, PUSH_LINE, text );
    fclose( text );

    for ( int i = 0; i < lines; i++ )
        ind_backup[ i ] = ind[ i ];

    my_qsort( ind, lines, sizeof( ind[ 0 ] ), cmpstringDOWN );

    for ( int i = 0; i < lines; i++ )
        fprintf( output, "%s", ind[ i ] );

    my_qsort( ind, lines, sizeof( ind[ 0 ] ), MC_PUSHKIN );

    fprintf( output, VERSUSSTART );

    for ( int i = 0; i < lines; i++ )
        fprintf( output, "%s", ind[ i ] );

    fprintf( output, "\n------------\n" );

    for ( int i = 0; i < lines; i++ )
        fprintf( output, "%s", ind_backup[ i ] );

    fclose( output );
    return 0;
}
