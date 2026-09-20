#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Qsort/Qsort.h"
#include "debug.h"
#include "Qsort/textfunc.h"
#include "Qsort/comp.h"
#include "versus.h"
#include "Qsort/Colours.h"


void puts_my( const char* a, FILE* ostream )
{
    while ( *a != '\n' && *a )
        putc( *( a++ ), ostream );
    putc( '\n', ostream );
}

void Print_poem( poem* lines, uint64_t size, FILE* ostream )
{
    for ( int i = 0; i < size; i++ )
        puts_my( lines[ i ].txt, ostream );
}

int main()
{
    FILE* output = fopen( "output.txt", "w" );
    assert( output );

    struct poem line = ReadText_Buff( "pushkin.txt" );
    struct poem* lines = Sort( line );
    int count = CountLines( line );
    // fprintf( stderr, "Count = %d\n", count );

    my_qsort( lines, count, sizeof( poem ), cmpstringDOWN_poem );
    // fprintf( stderr, "Passed 1st my_qsort\n" );
    Print_poem( lines, count, output );
    // fprintf( stderr, "Printed 1st text into output.txt\n" );
    fprintf( output, HCYN VERSUS_START reset );

    qsort( lines, count, sizeof( poem ), MC_PUSHKIN_poem );
    // fprintf( stderr, "Passed std qsort\n" );
    Print_poem( lines, count, output );
    // fprintf( stderr, "Printed 2nd text into output.txt\n" );
    fprintf( output, HCYN VERSUS_FINAL reset );

    fprintf( output, "\n-----\n\n" );

    fprintf( output, "%s", line.txt );
    // fprintf( stderr, "Printed original text" );

    free( line.txt );
    free( lines );
    fclose( output );
    return 0;
}
