#include <stdio.h>
#include <assert.h>

#include "COTexGetoptUtility.h"
#include "../debug.h"


/**
 * @brief Custom copy of a standart option command from getopt.h
 */
struct COTexOption
{
const char* Command;
int ArgumentAmount;
int* flag;
int value;
};



/**
 * @brief Checks if inputted command corresponds a flag
 *
 * @param[ in ] Command char* Command is a inputted by user command
 *
 * @param[ in ] Flag const char* Flag flag from the programm's code
 *
 * @return False if command don't correspondes Flag and true if correspondes
 */
bool CheckCommand( char* Command, const char* Flag )
{
    Command++;

    while ( *Command )
    {
        if ( *Command != *Flag || !( *Flag ) )
            return false;

        Command++;
        Flag++;
    }

    return true;
}

// char* COTexoptarg = 0; ///< Custom analogue of a standart optarg variable
// int COTexoptind = 0; ///< Custom analogue of a standart optind variable

int COTexGetopt_long_only( int argc, char* argv[], struct COTexOption* long_options, int* index )
{
$RT
    assert(  argv );
    assert( *argv );
    assert( long_options );

    static int number = 1; ///< Static variable for COTexGetopt, which stores number of current argv element

    /// If no more arguments to parse
    if ( number > argc - 1 ) return END_OF_INPUT;

    /// If argument is a command
    if ( *argv[ number ] == '-' )
    {

        /// While there are unchecked Commands
        while ( long_options->Command )
        {

            if ( CheckCommand( argv[ number ], long_options->Command ) )
            {

                if ( index ) *index = number; ///< If user  mentioned index as a poiner to a variable where to store current option's number

                switch ( long_options->ArgumentAmount )
                {
                    case NO_ARGUMENTS :

                        if ( long_options->flag )
                        {
                            number++;
                            *long_options->flag = long_options->value;
                            return FLAG_INITIALIZED_INTO_VARIABLE;
                        }
                        else
                        {
                            number++;
                            return long_options->value;
                        }

                    case REQUIRED_ARGUMENT :

                        if ( argc - 1 >= number ) ///< There is an argument
                        {
                            number++;
                            COTexoptarg = argv[ number ];

                            if ( *long_options->flag )
                            {
                                number++;
                                *long_options->flag = long_options->value;
                                return FLAG_INITIALIZED_INTO_VARIABLE;
                            }
                            else
                            {
                                number++;
                                return long_options->value;
                            }
                        }
                        else ///< There is no arguments
                        {
                            fprintf( stderr, ARGUMENT_ABSENCE,
                                    long_options->Command, __func__, __FILE__, __LINE__,
                                    long_options->Command, long_options->Command, long_options->Command );
                            number++;
                            return UNMENTIONED_COMMAND;
                        }

                    case OPTIONAL_ARGUMENT :

                        if ( argc - 2 >= number && *argv[ number + 1 ] != '-' ) ///< There is an argument
                        {
                            number++;
                            COTexoptarg = argv[ number ];

                            if ( long_options->flag ) ///< There is a pointer to a variable to store flag
                            {
                                number++;
                                *long_options->flag = long_options->value;
                                return FLAG_INITIALIZED_INTO_VARIABLE;
                            }
                            else ///< There is no pointer to a variable to store flag
                            {
                                number++;
                                return long_options->value;
                            }

                        }
                        else ///< There is no arguments
                        {
                            number++;
                            return long_options->value;
                        }

                    default :

                        fprintf( stderr, SWITCH_FAILURE, long_options->ArgumentAmount, __func__, __FILE__, __LINE__ );
                        number++;
                        return END_OF_INPUT;

                }

            }
            long_options++;
        }
    }
    else if ( number > argc - 1 )
        return END_OF_INPUT;

    fprintf( stderr, UNKNOWN_COMMAND, argv[ number ], __func__, __FILE__, __LINE__ );
    number++;
    return UNMENTIONED_COMMAND;
}
