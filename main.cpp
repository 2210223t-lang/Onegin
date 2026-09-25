#include "Modes.h"
#include "Stuff.h"
#include "CommandLine/Terminal.h"


int main( int argc, char** argv )
{
    struct iostream InAndOut = {};
    int mode = Terminal( argc, argv, InAndOut.istream_name, InAndOut.ostream_name );

    switch ( mode )
    {
        case 'b':
            localbuff( argc, argv, &InAndOut );
        case 'm':
            Nobuff( argc, argv, &InAndOut );
    }

    return 0;
}
