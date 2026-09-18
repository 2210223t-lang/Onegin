#include <cstddef>
#include <stdio.h>
#include <assert.h>

#include "debug.h"


void ReadText( char **ind, size_t szInd, FILE* text )
{
    size_t count = 0;
    int keepgoing = 0;
    while( keepgoing != EOF && count < szInd )
    {
        char* temp = NULL;
        size_t lenght = 0;

        if ( ( keepgoing = getline( &temp, &lenght, text ) ) != EOF )
            if ( *temp != '\n' )
                ind[ count++ ] =  temp;
    }
    // fprintf( stderr, "Ended reading file\n" );
}
