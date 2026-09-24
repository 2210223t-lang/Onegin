#ifndef TRIAL_COTEXGETOPTUTILITY_H
#define TRIAL_COTEXGETOPTUTILITY_H

#include "../Colours.h"


/// Prints in case of switch module failure in COTexGetopt.cpp
#define SWITCH_FAILURE  "\n" HRED \
                                "====================================================\n"\
                                "          COTex CRITICAL FAILURE SYSTEM v0.0.1\n"\
                                "====================================================\n"\
                                "An impossible internal state has been reached inside\n"\
                                "the command-line option parser.\n\n"\
                                "CRITICAL DIAGNOSTIC REPORT:\n"\
                                "  Severity: FATAL\n"\
                                "  Status: UNREACHABLE SWITCH BRANCH REACHED\n"\
                                "  Unexpected COTexGetopt_long_only() result: %d\n"\
                                "  Function: %s\n"\
                                "  Source file: %s\n"\
                                "  Line number: %d\n\n"\
                                "This message should never appear during normal program\n"\
                                "execution. All possible values returned by getopt() were\n"\
                                "expected to be handled before reaching this branch.\n\n"\
                                "Possible internal causes:\n"\
                                "  1. The COTexGetopt_long_only() option string and switch cases disagree.\n"\
                                "  2. A new option was added without a corresponding case.\n"\
                                "  3. The parser state or return value was corrupted.\n"\
                                "  4. The fundamental laws of command-line parsing failed.\n\n"\
                                "This is not considered a user input error. Continuing may\n"\
                                "produce unpredictable results, so the program must stop.\n\n"\
                                "Please report this failure to the developer and include\n"\
                                "the complete diagnostic information displayed above.\n"\
                                "====================================================\n"


/// Prints in case of argument absence in COTexGetopt.cpp
#define  ARGUMENT_ABSENCE "\n" HRED\
                                "====================================================\n"\
                                "       COTex AI Argument Analysis System v0.0.1\n"\
                                "====================================================\n"\
                                "The program successfully recognized the command-line\n"\
                                "option, but the option arrived without the argument\n"\
                                "required to perform the requested operation.\n\n"\
                                "AI analysis result:\n"\
                                "  Status: REQUIRED ARGUMENT MISSING\n"\
                                "  Problematic option: %s\n"\
                                "  Expected input: An argument after the option\n"\
                                "  Received input: Nothing\n"\
                                "  Function: %s\n"\
                                "  Source file: %s\n"\
                                "  Line number: %d\n\n"\
                                "Probable explanation:\n"\
                                "  The option %s requires an additional value, but the\n"\
                                "  command ended before that value could be found.\n\n"\
                                "Example of the expected command structure:\n"\
                                "  ./program %s <argument>\n\n"\
                                "Suggested AI solution:\n"\
                                "  1. Locate the option %s in your command.\n"\
                                "  2. Add the required argument immediately after it.\n"\
                                "  3. Make sure the argument is not another option.\n"\
                                "  4. Run the corrected command again.\n\n"\
                                "The program cannot safely guess the missing value,\n"\
                                "because even artificial intelligence should not invent\n"\
                                "command-line arguments without the user's permission.\n"\
                                "====================================================\n"



/// Prints in case of unknown terminal command
#define UNKNOWN_COMMAND "\n" HRED\
                                "====================================================\n"\
                                "       COTex AI Argument Analysis System v0.0.1\n"\
                                "====================================================\n"\
                                "Unfortunately, the program was unable to understand\n"\
                                "one of the command-line options provided by the user.\n\n"\
                                "AI analysis result:\n"\
                                "  Status: ARGUMENT PARSING FAILURE\n"\
                                "  Problematic option: %s\n"\
                                "  Function: %s\n"\
                                "  Source file: %s\n"\
                                "  Line number: %d\n\n"\
                                "Probable explanation:\n"\
                                "  The option is unknown, misspelled, unsupported, or\n"\
                                "  requires an argument that was not provided.\n\n"\
                                "Suggested AI solution:\n"\
                                "  1. Check the spelling of the command-line option.\n"\
                                "  2. Verify whether the option requires an argument.\n"\
                                "  3. Consult the program's help message.\n"\
                                "  4. Try again with arguments the program understands.\n\n"\
                                "The requested operation cannot continue until the\n"\
                                "command-line arguments have been corrected.\n"\
                                "====================================================\n"

/**
 * @brief COTexGetopt outputs values
 */
enum GetoptOutput
{
    UNMENTIONED_COMMAND = '?',
    FLAG_INITIALIZED_INTO_VARIABLE = 0,
    END_OF_INPUT = -1
};

/**
 * @brief Argument amount constants for COTexGetopt
 */
enum ArgumentAmount
{
    NO_ARGUMENTS = 0,
    REQUIRED_ARGUMENT = 1,
    OPTIONAL_ARGUMENT = 2
};

#endif // TRIAL_COTEXGETOPTUTILITY_H
