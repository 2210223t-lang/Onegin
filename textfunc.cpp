#include <cstddef>
#include <cstdint>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "debug.h"
#include "Colours.h"

struct poem
{
    char* txt;
    uint64_t cpp;
};


uint64_t Getsize( const char* filename )
{
    struct stat a = {};
    stat( filename, &a );
    return a.st_size;
}

/**
 * @brief Counts amount of '\n' symbols in poem
 */
int CountLines( struct poem text )
{
    int count = 0;
    for ( int i = 1; i < text.cpp; i++ )
        if ( text.txt[ i ] == '\n' && text.txt[ i - 1 ] != '\n' )
            count++;
    return count;
}

/**
 * @brief Read text from .txt file into many different arrays
 *
 * @param ind char** is a pointer to a beginning of a 2d array of lines
 *
 * @param szInd size_t max amount of lines
 *
 * @param filename char* name of the file, where from to read lines
 *
 * @return amount of stored lines
 */
int ReadText_Separated( char **ind, size_t szInd, const char* filename )
{
    assert( ind );
    size_t count = 0;
    int keepgoing = 0;
    FILE* istream = fopen( filename, "r" );

    if ( !istream )
    {
        fprintf( stderr, "Failed to open %s in %s", filename, __func__ );
        abort();
    }

    while( keepgoing != EOF && count < szInd )
    {
        char* temp = NULL;
        size_t lenght = 0;

        if ( ( keepgoing = getline( &temp, &lenght, istream ) ) != EOF && *temp != '\n' )
                ind[ count++ ] =  temp;
    }
    fclose( istream );
    return count;
}

/**
 * @brief Reads text into one buff
 *
 * @param filename const char* takes name of the file, where from function take text
 *
 * @return struct poem, which contains size and pointer to the text, stored in one string
 */
struct poem ReadText_Buff( const char* filename )
{
    struct poem text = {};
    int istream = open( filename, O_RDONLY );
    if ( !istream )
    {
        fprintf( stderr, "Failed to open %s in %s\n", filename, __func__ );
        abort();
    }
    text.cpp = Getsize( filename );

    text.txt = ( char* ) calloc( text.cpp, sizeof( char ) );

    text.cpp = read( istream, text.txt, text.cpp );

    close( istream );
    // fprintf( stderr, HRED "Ended reading text with %llu symbols\n" reset, text.cpp );
    return text;
}

/**
 * @brief Sorts text data into different lines
 *
 * @param text struct poem is a variable with text
 *
 * @return array of poem* where every variable is a data of a single line
 */
struct poem* Sort( struct poem text )
{
    int count = CountLines( text );
    struct poem* lines = ( poem* ) calloc( count, sizeof( poem ) );
    char* temp = text.txt;
    size_t size = 0;
    int real = 0;

    while ( real < count )
    {
        size = 0;
        while ( *( temp + size ) != '\n' && *( temp + size ) )
            size++;
        if ( ( size++ ) >= 1 )
        {
            *( lines + real ) = { .txt = temp, .cpp = size };
            real++;
        }
        temp += size;
    }
    // fprintf( stderr, HRED "Ended sorting text and returned %d lines\n" reset, real );
    return lines;
}
