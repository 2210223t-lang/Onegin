#include <cstdint>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#include "../debug.h"

/// Holds info about some text, stored in string
struct poem
{
    char* txt; //< Pointer to a beginning of text
    uint64_t cpp; //< Size of useful data ( in bytes )
};

/// Defines inaccuracy for double and float comparing
#define EPSI 0.000001


int cmpintUP( const void* a, const void* b )
{
    assert( a );
    assert( b );

    return *( int* ) a - *( int* ) b;
}

int cmpdoubleUP( const void* a, const void* b )
{
    assert( a );
    assert( b );

    if ( fabs( *( double* ) a < *( double* ) b ) <= EPSI )
        return 0;
    return ( *( double* ) a < *( double* ) b + EPSI ) ? 1 : -1;
}

int cmpfloatUP( const void* a, const void* b )
{
    assert( a );
    assert( b );

    if ( fabs( *( float* ) a < *( float* ) b ) <= EPSI )
        return 0;
    return ( *( float* ) a < *( float* ) b + EPSI ) ? 1 : -1;
}

int cmpshortUP( const void* a, const void* b )
{
    assert( a );
    assert( b );

    return *( short* ) a - *( short* ) b;
}

int cmplonglongUP( const void* a, const void* b )
{
    assert( a );
    assert( b );

    return ( *( long long* ) a - *( long long* ) b ) / INT32_MAX; //< I divide to avoid ( int ) varible overflow
}

/**
 * @brief Compares 2 strings, which ends with '\0' or '\n'
 *
 * @param a string
 *
 * @param b string
 *
 * @warning This function ignore all symbols, except of letters
 *
 * @return 0 if ( a == b ), x > 0 if ( a > b ), x < 0 if ( a < b )
 */
int cmpstringDOWN( const void* a, const void* b )
{
    assert( a );
    assert( b );

    char* ptra = *( char** ) a;
    char* ptrb = *( char** ) b;

    while ( *ptra != '\n' && *ptrb != '\n' && *ptra && *ptrb )
    {
        while ( *ptra != '\n' && *ptra && !isalpha( *ptra ) )
            ptra++;
        while ( *ptrb != '\n' && *ptrb && !isalpha( *ptrb ) )
            ptrb++;

        if ( *ptra == 0 || *ptrb == 0 )
            return *ptra - *ptrb;
        else if ( *ptra != *ptrb )
            return tolower( *ptra ) - tolower( *ptrb );
        ptra++;
        ptrb++;
    }

    return *ptra - *ptrb;
}

/**
 * @brief cmpstringDOWN function, which takes ( struct poem ) variables
 */
int cmpstringDOWN_poem( const void* a, const void* b )
{
    assert( a );
    assert( b );

    char* ptra = ( *( ( poem* ) a ) ).txt;
    char* ptrb = ( *( ( poem* ) b ) ).txt;
    uint64_t sizea = ( *( ( poem* ) a ) ).cpp - 1;
    uint64_t sizeb = ( *( ( poem* ) b ) ).cpp - 1;

    while ( sizea > 0 && sizeb > 0 )
    {
        while ( sizea > 0 && !isalpha( *ptra ) )
        {
            sizea--;
            ptra++;
        }
        while ( sizeb > 0 && !isalpha( *ptrb ) )
        {
            sizeb--;
            ptrb++;
        }
        if ( !sizea || !sizeb )
            return *ptra - *ptrb;
        else if ( *ptra != *ptrb )
            return tolower( *ptra ) - tolower( *ptrb );
        ptra++;
        ptrb++;
    }

    return *ptra - *ptrb;
}

int cmpcharUP( const void* a, const void* b )
{
    return *( const char* ) a - *( const char* ) b;
}

int MC_PUSHKIN( const void* a, const void* b )
{
    assert( a );
    assert( b );

    char* ptra = *( char** ) a;
    char* ptrb = *( char** ) b;
    int counta = 0, countb = 0;

    while ( *ptra != '\n' || !( *ptra ) )
    {
        counta++;
        ptra++;
    }
    while ( *ptrb != '\n' || !( *ptrb ) )
    {
        ptrb++;
        countb++;
    }

    while ( counta > 0 && countb > 0 && *ptra == *ptrb )
    {
        while ( !isalpha( *ptra ) && counta > 0 )
        {
            ptra--;
            counta--;
        }
        while ( !isalpha( *ptrb ) && countb > 0 )
        {
            ptrb--;
            countb--;
        }
        if ( counta > 0 && countb > 0 && isalpha( *ptra ) && isalpha( *ptrb ) && *ptra == *ptrb )
        {
            ptra--;
            ptrb--;
            counta--;
            countb--;
        }
    }
    if ( counta <= 0 )
        *ptra = 0;
    if ( countb <= 0 )
        *ptrb = 0;
    if ( *ptrb == 0 || *ptra == 0 )
        return *ptra - *ptrb;
    return tolower( *ptra ) - tolower( *ptrb );
}

/**
 * @brief Compares string part of a and b ( struct poem ) variables from the last letter
 */
int MC_PUSHKIN_poem( const void* a, const void* b )
{
    assert( a );
    assert( b );

    char* ptra = ( *( ( poem* ) a ) ).txt;
    char* ptrb = ( *( ( poem* ) b ) ).txt;
    uint64_t sizea = ( *( ( poem* ) a ) ).cpp;
    uint64_t sizeb = ( *( ( poem* ) b ) ).cpp;


    while ( sizea > 0 && sizeb > 0 && *( ptra + sizea ) == *( ptrb + sizeb ) )
    {
        while ( !isalpha( *( ptra + sizea ) ) && sizea > 0 )
            sizea--;

        while ( !isalpha( *( ptrb + sizeb ) ) && sizeb > 0 )
            sizeb--;

        if ( sizea > 0 && sizeb > 0 && isalpha( *( ptra + sizea ) ) && isalpha( *( ptrb + sizeb ) ) && *( ptra + sizea ) == *( ptrb + sizeb ) )
        {
            sizea--;
            sizeb--;
        }
    }

    if ( sizea <= 0 || sizeb <= 0 )
        return *( ptra + sizea ) - *( ptrb + sizeb );
    return tolower( *( ptra + sizea ) ) - tolower( *( ptrb + sizeb ) );
}
