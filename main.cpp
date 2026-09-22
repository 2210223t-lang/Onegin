#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Colours.h"
#include "Qsort/Qsort.h"
#include "Qsort/comp.h"
#include "versus.h"
#include "textfunc.h"
#include "debug.h"


int main()
{
    char oputfile[] = "output.txt";
    FILE* ostream = fopen( oputfile, "w" );
    if ( !ostream )
    {
        fprintf( stderr, "Failed to open %s in %s", oputfile, __func__ );
        return 0;
    }

    struct frag line = ReadText_Buff( "pushkin.txt" );
    struct frag* lines = Sort( line );
    int count = CountLines( line );

    // fprintf( stderr, "Count = %d\n", count );

    my_qsort( lines, count, sizeof( frag ), cmpstringDOWN_frag );
    // fprintf( stderr, "Passed 1st my_qsort\n" );
    Print_frag( lines, count, ostream );
    // fprintf( stderr, "Printed 1st text into output.txt\n" );
    fprintf( ostream, VERSUS_START );

    PrintMicro( ostream );

    qsort( lines, count, sizeof( frag ), MC_PUSHKIN_frag );
    // fprintf( stderr, "Passed std qsort\n" );
    Print_frag( lines, count, ostream );
    // fprintf( stderr, "Printed 2nd text into output.txt\n" );
    fprintf( ostream, VERSUS_FINAL );

    fprintf( ostream, "%s", line.txt );
    // fprintf( stderr, "Printed original text" );

    free( line.txt );
    free( lines );
    fclose( ostream );
    return 0;
}
