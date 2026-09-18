#include <stdio.h>
#include <math.h>
#include <ctype.h>

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

bool cmpstringUP( const void* a, const void* b )
{
    char* ptra = ( char* ) a;
    char* ptrb = ( char* ) b;
    bool result = false;

    while ( *ptra != '\n' && *ptrb != '\n' && *ptra && *ptrb )
    {
        while ( *ptra != '\n' && *ptra && !isalpha( *ptra ) )
            ptra++;
        while ( *ptrb != '\n' && *ptrb && !isalpha( *ptrb ) )
            ptrb++;
        if ( *( ptra++ ) != *( ptrb++ ) )
            return ( tolower( *ptra ) <= tolower( *ptrb ) ) ? true : false;
    }

    return ( *ptra <= *ptrb ) ? true : false;
}

bool cmpcharUP( const void* a, const void* b )
{
    return ( *( const char* ) a <= *( const char* ) b ) ? true : false;
}

bool MC_PUSHKIN( const void* a, const void* b )
{
    char* ptra = ( char* ) a;
    char* ptrb = ( char* ) b;
    int counta = 0, countb = 0;

    while ( *( ptra++ ) != '\n' )
        counta++;
    while ( *( ptrb++ ) != '\n' )
        countb++;
    ptra--;
    ptrb--;
    while ( counta-- > 0 && countb-- > 0 && !( *( ptra-- ) - *( ptrb-- ) ) )
    {
        while ( !isalpha( *( ptra-- ) ) )
            counta--;
        while ( !isalpha( *( ptrb-- ) ) )
            countb--;
    }

    ptra++;
    ptrb++;

    if ( counta < 0 )
        *ptra = 0;
    if ( countb < 0 )
        *ptrb = 0;

    return ( *ptra <= *ptrb ) ? true : false;

}
