#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>

#include "../debug.h"

#define EPSI 0.000001


bool cmpintUP( const void* a, const void* b )
{
    return ( *( int* ) a <= *( int* ) b ) ? true : false;
}

bool cmpdoubleUP( const void* a, const void* b )
{
    return ( *( double* ) a <= *( double* ) b + EPSI ) ? true : false;
}

bool cmpfloatUP( const void* a, const void* b )
{
    return( *( float* ) a <= *( float* ) b + EPSI ) ? true : false;
}

bool cmpshortUP( const void* a, const void* b )
{
    return ( *( short* ) a <= *( short* ) b ) ? true : false;
}

bool cmplonglongUP( const void* a, const void* b )
{
    return ( *( long long* ) a <= *( long long* ) b ) ? true : false;
}

bool cmpstringDOWN( const void* a, const void* b )
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
            return ( *ptra <= *ptrb ) ? true : false;
        else if ( *ptra != *ptrb )
            return ( tolower( *ptra ) <= tolower( *ptrb ) ) ? true : false;
        ptra++;
        ptrb++;
    }

    return ( *ptra < *ptrb ) ? true : false;
}

bool cmpcharUP( const void* a, const void* b )
{
    return ( *( const char* ) a <= *( const char* ) b ) ? true : false;
}
//TODO delete ptra++, leave only counta++ and countb++
bool MC_PUSHKIN( const void* a, const void* b )
{
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
        return ( *ptra < *ptrb ) ? true : false;
    return ( tolower( *ptra ) <= tolower( *ptrb ) ) ? true : false;

}
