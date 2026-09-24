#include <stdio.h>
#include <assert.h>


void puts_debug( const char* a, FILE* ostream )
{
    assert( ostream );

    while ( *a != '\n' && *a )

        switch ( *( a++ ) )
            {
            case '\n': printf ( "\\n" ); break;
            case '\a': printf ( "\\a" ); break;
            case '\t': printf ( "\\t" ); break;
            case '\b': printf ( "\\b" ); break;
            case '\r': printf ( "\\r" ); break;
            default:   putc( *( a ), ostream );
            }

    putc( '\n', ostream );
}
