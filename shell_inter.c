#include "unique_shell.h"

/**
 * Check if the shell is in interactive mode.
 * 
 * @param info Pointer to the info_t struct
 * @return 1 if in interactive mode, 0 otherwise
 */
int check_interactive_mode(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * Check if a character is a delimiter.
 * 
 * @param character The character to check
 * @param delimiters Delimiter string
 * @return 1 if the character is a delimiter, 0 otherwise
 */
int is_delimiter(char character, char *delimiters) {
    while (*delimiters) {
        if (*delimiters++ == character) {
            return 1;
        }
    }
    return 0;
}

/**
 * Check if a character is alphabetic.
 * 
 * @param character The character to check
 * @return 1 if the character is alphabetic, 0 otherwise
 */
int is_alpha(int character) {
    return ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z'));
}

/**
 * Convert a string to an integer.
 * 
 * @param string The string to convert
 * @return The converted integer
 */
int convert_to_integer(char *string) {
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; string[i] != '\0' && flag != 2; i++) {
        if (string[i] == '-') {
            sign *= -1;
        }

        if (string[i] >= '0' && string[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (string[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    if (sign == -1) {
        output = -result;
    } else {
        output = result;
    }

    return output;
}
