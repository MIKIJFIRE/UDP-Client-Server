/**
 * @file utils.h
 * @brief Provides utility functions for colored text output.
 *
 * This header file declares functions and enumerations that assist in printing
 * colored text to the terminal. It allows for text to be printed in various colors
 * by utilizing ANSI escape codes for terminal formatting.
 *
 * @version 1.1.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#ifndef UTILS_H_
#define UTILS_H_

/* - - - - - - - - - - - - - - - - - COLORS - - - - - - - - - - - - - - - - - */

/**
 * @enum textColor
 * @brief Defines colors for text output.
 *
 * This enumeration defines the standard ANSI color codes that are used to specify
 * text colors for terminal output. These color values are used with functions that
 * print colored text to the terminal.
 */
typedef enum {
    BLACK,      /**< Black text color */
    RED,        /**< Red text color */
    GREEN,      /**< Green text color */
    YELLOW,     /**< Yellow text color */
    BLUE,       /**< Blue text color */
    MAGENTA,    /**< Magenta text color */
    CYAN,       /**< Cyan text color */
    WHITE,      /**< White text color */
    RESET       /**< Resets the text color to the terminal's default */
} textColor;

/**
 * @brief Prints the specified text in the specified color.
 *
 * This function prints a string to the terminal with the text color specified by
 * the `color` parameter. The function uses ANSI escape codes to apply the color
 * and resets the text color to default after printing the string.
 *
 * @param[in] text A pointer to the string to print. The string should be null-terminated.
 * @param[in] color The color to apply to the text, specified as a value from the `textColor` enum.
 *
 * @pre `text` must be a valid, non-null pointer to a null-terminated string.
 * @post The text is printed to the console in the specified color, and the color is reset to default afterward.
 */
void print_with_color(const char *text, textColor color);

/* - - - - - - - - - - - - - - - - END COLORS - - - - - - - - - - - - - - - - */

#endif /* UTILS_H_ */
