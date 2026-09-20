#include <cstddef>
#include <stdio.h>
#include <cstdint>
#include <assert.h>

#include "../Colours.h"
#include "../debug.h"

enum Error
{
    LindLeapfrog = 14,
    RindLeapfrog = 15,
    QsortError = 16,
    Success = 0,
};

int CallRec( void* array, int nElem, size_t szElem, int status, int middle,
             int ( *Comp )( const void*, const void* ) );

// #define getchar() fprintf( stderr, HRED " There could be your getchar\n" reset )

/**
 * @brief Swap values of 2 variables a and b
 */
void swap( size_t size, void* a, void* b )
{
    assert( a );
    assert( b );

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

/**
 * @brief Debugging function which print current position of Lind, Ring and Middle elements
 */
int Status( double* array, int Lind, int Rind, int nElem, int middle )
{
    assert( array );

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

int my_qsort( void* array, int nElem, size_t szElem, int ( *Comp )( const void*, const void* ) )
{
    assert( array );

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

        /// Looking for Left uncorrect element
        while ( Lind < Rind && Lind != middle && Comp( ( char* ) array + Lind * szElem, ( char* ) array + middle * szElem ) <= 0 )
        {
            // fprintf( stderr, HCYN "Looking for Lind\n" reset );
            Lind++;
        }
        // fprintf( stderr, WHT "I found Lind = %d, moving to Rind, press Enter to continue:", Lind );
        // getchar();

        /// Looking for right bad element
        while ( Rind != middle && Lind < Rind && Comp( ( char* ) array + middle * szElem , ( char* ) array + Rind * szElem ) <= 0 )
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

    status = CallRec( array, nElem, szElem, status, middle, Comp );

    return status;
}

/**
 * @brief Is an extracted recursion call from my_qsort
 *
 * @param array void* pointer to a sorting part of the array
 *
 * @param nElem int Amount of sorting elements
 *
 * @param szElem size_t Size in bytes of a single variable in array
 *
 * @param status int Stores current status of pogramm
 *
 * @param middle int Stores koef of the middle element
 *
 * @param Comp Pointer to a comparing function
 *
 * @return Status of exit
 */
int CallRec( void* array, int nElem, size_t szElem, int status, int middle,
             int ( *Comp )( const void*, const void* ) )
{
    assert( array );

    // fprintf( stderr, HCYN "Starting new recursion level\n" reset );
    if ( status == Success && middle > 2 )
    {
        // fprintf( stderr, "Left root\n" );
        status = my_qsort( array, middle, szElem, Comp );
    }
    /// To enhance code speed, I check 2 - sized arrays manually
    else if ( status == Success && middle == 2 && Comp( array, ( char* ) array + 1 * szElem ) > 0 )
        swap( szElem, array, ( char* ) array + 1 * szElem );

    if ( status == Success && nElem - middle - 1 > 1 )
    {
        // fprintf( stderr, "Right root\n" );
        status = my_qsort( ( char* ) array + ( middle + 1 ) * szElem, nElem - middle - 1, szElem, Comp );
    }
    /// To enhance code speed, I check 2 - sized arrays manually
    else if (  status == Success && nElem - middle - 1 == 2 &&
               Comp( ( char* ) array + ( nElem - 1 ) * szElem, ( char* ) array + ( nElem - 2 ) * szElem ) > 0 )
        swap( szElem, ( char* ) array + ( nElem - 1 ) * szElem, ( char* ) array + ( nElem - 2 ) * szElem );

    return status;
}
