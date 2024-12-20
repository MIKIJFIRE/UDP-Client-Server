/**
 * @file utils.c
 * @brief Implementation of utility functions for printing colored text.
 *
 * This file provides utility functions for managing ANSI color codes for terminal output.
 * Specifically, it includes functions to:
 *  - Map color values from the `textColor` enumeration to their corresponding ANSI escape codes.
 *  - Print text in the specified color to the terminal.
 *
 * @version 1.1.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "utils.h"

/* - - - - - - - - - - - - - - - - - COLORS - - - - - - - - - - - - - - - - - */

/**
 * @brief Returns the ANSI escape code for the specified color.
 *
 * This function maps a value from the `textColor` enumeration to the corresponding
 * ANSI escape code used for terminal color formatting. The color is returned as a
 * string that can be embedded in terminal output to change the text color.
 *
 * @param[in] color The color to be applied, represented as a value from the `textColor` enum.
 *
 * @return A string containing the ANSI escape code for the requested color.
 *         If the `color` is invalid, the function defaults to returning the reset code.
 *
 * @note The return value should be used to format text in the terminal using `printf` or other output functions.
 */
const char *generate_ansi_color_code(textColor color) {
    switch(color) {
        case BLACK:     return "\033[30m";   /**< ANSI escape code for black */
        case RED:       return "\033[31m";   /**< ANSI escape code for red */
        case GREEN:     return "\033[32m";   /**< ANSI escape code for green */
        case YELLOW:    return "\033[33m";   /**< ANSI escape code for yellow */
        case BLUE:      return "\033[34m";   /**< ANSI escape code for blue */
        case MAGENTA:   return "\033[35m";   /**< ANSI escape code for magenta */
        case CYAN:      return "\033[36m";   /**< ANSI escape code for cyan */
        case WHITE:     return "\033[37m";   /**< ANSI escape code for white */
        case RESET:     return "\033[0m";    /**< ANSI escape code for resetting color */
        default:        return "\033[0m";    /**< Default to reset color if invalid */
    }
}

/**
 * @brief Prints a string in the specified color.
 *
 * This function wraps the provided text in the appropriate ANSI escape codes for the specified color.
 * The text is printed to the terminal, and the color is reset to the default color afterward.
 * This allows for printing colored text while ensuring the terminal's color settings are restored.
 *
 * @param[in] text The text to be printed. Must be a valid null-terminated string.
 * @param[in] color The color to apply, specified as a value from the `textColor` enum.
 *
 * @pre `text` must not be NULL. If `text` is NULL, the function will not print anything.
 * @post The text is printed to the terminal in the specified color, followed by a reset to the default terminal color.
 *
 * @note This function does not modify the `text` string itself but prints it in color to the terminal.
 */
void print_with_color(const char *text, textColor color) {
    if (text == NULL) return;  /**< If text is NULL, return without printing */
    printf("%s%s%s", generate_ansi_color_code(color), text, generate_ansi_color_code(RESET));
}

/* - - - - - - - - - - - - - - - - END COLORS - - - - - - - - - - - - - - - - */
