#include <cstddef>
#include <stdio.h>
#include <cstdint>

#include "Colours.h"
#include "../debug.h"

enum Error
{
    LindLeapfrog = 14,
    RindLeapfrog = 15,
    QsortError = 16,
    Success = 0,
};

#define getchar() fprintf( stderr, HRED " There could be your getchar\n" reset )


void swap( size_t size, void* a, void* b )
{
    uint64_t buff = 0;
    while ( size >= 8 && ( ( size_t ) a ) % 8 == 0 && ( ( size_t ) b ) % 8 == 0 )
    {
        buff = *( uint64_t* ) b;
        *( uint64_t* ) b = *( uint64_t* ) a;
        *( uint64_t* ) a = buff;
        a = ( uint64_t* ) a + 1;
        b = ( uint64_t* ) b + 1;
        size -= 8;
    }
    while ( size >= 4 && ( ( size_t ) a % 4 == 0 ) && ( ( size_t ) b ) % 4 == 0  )
    {
        buff = *( uint32_t* ) b;
        *( uint32_t* ) b = *( uint32_t* ) a;
        *( uint32_t* ) a = buff;
        a = ( uint32_t* ) a + 1;
        b = ( uint32_t* ) b + 1;
        size -= 4;
    }
    while ( size >= 2 && ( ( size_t ) a ) % 2 == 0 && ( ( size_t ) b ) % 2 == 0)
    {
        buff = *( uint16_t* ) b;
        *( uint16_t* ) b = *( uint16_t* ) a;
        *( uint16_t* ) a = buff;
        a = ( uint16_t* ) + 1;
        b = ( uint16_t* ) + 1;
        size -= 2;
    }
    if ( size == 1 )
    {
        buff = *( uint8_t* ) b;
        *( uint8_t* ) b = *( uint8_t* ) a;
        *( uint8_t* ) a = buff;
        size--;
    }
}

int Status( double* array, int Lind, int Rind, int nElem, int middle )
{
    if ( Lind > nElem )
        return LindLeapfrog;
    if ( Rind < 0 )
        return RindLeapfrog;


    int i = -1;
    while ( ++i < nElem )
        fprintf( stderr, WHT "[ %2d ] ", i );
    fprintf( stderr, "Lind = %d, Rind = %d, Middle = %d, nElem = %d\n", Lind, Rind, middle, nElem );

    i = 0;
    while ( i < Lind )
    {
        fprintf( stderr, BLU "%5.1lf  ", *( array + i ) );
        i++;
    }
    if ( i == Lind && i != middle )
    {
        fprintf( stderr, GRN "%5.1lf  ", *( array + i ) );
        i++;
    }
    while ( i < middle )
    {
        fprintf( stderr, WHT "%5.1lf  ", *( array + i ) );
        i++;
    }
    if ( i == middle )
    {
        fprintf( stderr, YEL "%5.1lf  ", *( array + i ) );
        i++;
    }
    while ( i < Rind )
    {
        fprintf( stderr, WHT "%5.1lf  ", *( array + i ) );
        i++;
    }
    if ( i == Rind )
    {
        fprintf( stderr, GRN "%5.1lf  ", *( array + i ) );
        i++;
    }
    while ( i < nElem )
    {
        fprintf( stderr, RED "%5.1lf ", *( array + i ) );
        i++;
    }
    fprintf( stderr, "\n" );
    return Success;
}

int my_qsort( void* array, int nElem, size_t szElem, bool ( *Comp )( const void*, const void* ) )
{
    // fprintf( stderr, HCYN "Starting new recursion level\n" reset );
    int middle = nElem / 2, Lind = 0, Rind = nElem - 1;
    int status = 0;

    while ( Lind < Rind && Rind > 0 && Lind < nElem - 1 )
    {
        /* status = Status( ( double* ) array, Lind, Rind, nElem, middle );
        if ( status != Success ) /// Debugging loop
        {
            fprintf( stderr, "Program exited with code : %d\n", status );
            return QsortError;
        } */
        // fprintf( stderr, HCYN "Starting a new loop\n" reset );

        while ( Lind < Rind && Lind != middle && Comp( ( char* ) array + Lind * szElem, ( char* ) array + middle * szElem ) )
        {
            // fprintf( stderr, HCYN "Looking for Lind\n" reset );
            Lind++;
        }
        // fprintf( stderr, WHT "I found Lind = %d, moving to Rind, press Enter to continue:", Lind );
        // getchar();

        while ( Rind != middle && Lind < Rind && Comp( ( char* ) array + middle * szElem , ( char* ) array + Rind * szElem ) )
        {
            // fprintf( stderr, HCYN "Looking for Rind\n" reset );
            Rind--;
        }
        // fprintf ( stderr, WHT "I found Rind = %d and i'm going to swap" HRED " Lind = %d and Rind = %d " WHT " please, press Enter to continue:\n", Rind, Lind, Rind );
        // getchar();
        if ( Lind < Rind )
        {
            // fprintf( stderr, "Changing [%d] <-> [%d]\n", Lind, Rind );
            // getchar();

            swap( szElem, ( char* ) array + Lind * szElem, ( char* ) array + Rind * szElem );

            if ( Lind == middle )
            {
                if ( Lind < Rind )
                    Lind++;
                middle = Rind;
            }
            else if ( Rind == middle )
            {
                if ( Lind < Rind )
                    Rind--;
                middle = Lind;
            }
            else if ( Lind < Rind )
            {
                Lind++;
                Rind--;
            }
        }
    }
    // status = Status( ( double* ) array, Lind, Rind, nElem, middle );
    // fprintf( stderr, WHT "---------------\n" );
    // getchar();
    if ( status == Success && middle > 1 )
    {
        // fprintf( stderr, "Left root\n" );
        status = my_qsort( array, middle, szElem, Comp );
    }
    if ( status == Success && nElem - middle - 1 > 1 )
    {
        // fprintf( stderr, "Right root\n" );
        status = my_qsort( ( char* ) array + ( middle + 1 ) * szElem, nElem - middle - 1, szElem, Comp );
    }

    return status;
}

//TODO learn about emulator
