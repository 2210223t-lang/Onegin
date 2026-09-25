#include <cstddef>
#include <cstdint>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "debug.h"
#include "Colours.h"
#include "textfunc.h"


uint64_t Getsize( const char* filename )
{
    struct stat a = {};

    stat( filename, &a );

    return a.st_size;
}

/**
 * @brief Counts amount of '\n' symbols in frag
 */
int CountLines( const struct poem text )
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
int ReadText_Separated( char **ind, const size_t szInd, const char* filename )
{
    assert( ind );
    char* temp = NULL;
    size_t length = 0;
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
        temp = NULL;
        length = 0;

        if ( ( keepgoing = getline( &temp, &length, istream ) ) != EOF && *temp != '\n' )
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
 * @return struct frag, which contains size and pointer to the text, stored in one string
 */
struct poem ReadText_Buff( const int istream, const char* filename )
{
    assert( filename );

    // fprintf( stderr, "%s\n", filename );

    struct poem text = {};

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
 * @param text struct frag is a variable with text
 *
 * @return array of frag* where every variable is a data of a single line
 */
struct frag* Divide( const struct poem text )
{
    int count = CountLines( text );
    struct frag* lines = ( frag* ) calloc( count, sizeof( frag ) );
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
            *( lines + real ) = { .begin = temp, .end = temp + size };
            real++;
        }
        temp += size;
    }
    // fprintf( stderr, HRED "Ended sorting text and returned %d lines\n" reset, real );
    return lines;
}

/**
 * @brief Print string till 1st '\n'
 *
 * @param a ( conts char* ) string fragment
 *
 * @param ostream ( FILE* ) pointer to stream where to print text
 */
void puts_my( const char* a, FILE* ostream )
{
    assert( ostream );

    while ( *a != '\n' && *a )
        putc( *( a++ ), ostream );

    putc( '\n', ostream );
}

/**
 * @brief Prints text from array of ( struct frag )
 *
 * @param lines ( struct frag* ) array of frag
 *
 * @param size uint64_t Stores amount of variables in lines array
 *
 * @param ostream FILE* where data would be printed
 */
void Print_poem( const struct frag* lines, const  uint64_t size, FILE* ostream )
{
    assert( lines );
    assert( ostream );

    for ( int i = 0; i < size; i++ )
        puts_my( lines[ i ].begin, ostream );
}


struct poem ReadText_mmap( const int istream, const char* filename )
{
    uint64_t size = Getsize( filename );
    char* input = ( char* ) mmap( 0, size, PROT_READ, MAP_SHARED, istream, 0 );

    if ( input == MAP_FAILED )
    {
        fprintf( stderr, HRED "Map failure\n" reset );
        return { .txt = NULL, .cpp = 0 };
    }

    return { .txt = input, .cpp = size };
}
