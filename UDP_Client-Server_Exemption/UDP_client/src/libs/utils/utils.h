/**
 * @file utils.h
 * @brief Declaration of utility functions for colored text output and displaying user menus.
 *
 * This header file declares functions and enumerations that assist with printing
 * colored text to the terminal and displaying menus for password generation.
 *
 * @date 2024-12-20
 * @author Michele Camassa
 * @version 1.1.0
 */

#ifndef UTILS_H_
#define UTILS_H_

/* - - - - - - - - - - - - - - - - - COLORS - - - - - - - - - - - - - - - - - */

/**
 * @enum textColor
 * @brief Defines the colors for text output.
 *
 * This enumeration includes ANSI color codes for specifying text colors
 * in terminal output.
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
    RESET       /**< Resets the text color to default */
} textColor;


/**
 * @brief Prints the specified text in the desired color.
 *
 * This function prints a string with the ANSI color specified by the `color` parameter.
 * After printing, the text color is reset to the default value.
 *
 * @param[in] text Pointer to the string to be printed. Must be a null-terminated string.
 * @param[in] color The text color to apply, as specified in the `textColor` enum.
 *
 * @pre `text` must be a valid, non-NULL pointer.
 * @post The text is printed to the terminal in the specified color.
 */
void print_with_color(const char *text, textColor color);

/* - - - - - - - - - - - - - - - - END COLORS - - - - - - - - - - - - - - - - */

/**
 * @brief Displays the help menu for the password generator.
 *
 * This function prints a detailed help menu that explains the available options and commands
 * for password generation.
 *
 * @post The help menu is displayed in the terminal.
 */
void show_help_menu();

/**
 * @brief Displays the password type and length selection menu.
 *
 * This function prints a menu that prompts the user to choose the type of password
 * and specify its length. The menu provides detailed descriptions for each option.
 *
 * @post The password selection menu is displayed in the terminal.
 */
void show_password_menu();

#endif /* UTILS_H_ */
