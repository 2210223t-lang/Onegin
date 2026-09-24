#ifndef TRIAL_COTEXGETOPT_H
#define TRIAL_COTEXGETOPT_H

#include "../Colours.h"


/**
 * @brief Argument amount constants for COTexGetopt
 */
enum ArgumentAmount
{
    NO_ARGUMENTS = 0,
    REQUIRED_ARGUMENT = 1,
    OPTIONAL_ARGUMENT = 2
};

/**
 * @brief Custom copy of a standart option struct from getopt.h
 */
struct COTexOption
{
const char* Command;
int ArgumentAmount;
int* flag;
int value;
};

extern char* COTexoptarg; ///< Custom analogue of a standart optarg variable

/**
 * @brief Custom copy of a standart function getopt_long_only
 */
int COTexGetopt_long_only( int argc, char* argv[], struct COTexOption* long_options, int* index );


#endif // TRIAL_COTEXGETOPT_H
