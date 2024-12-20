/**
 * @file password.c
 * @brief Implementation of password generation functions based on various types and lengths.
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 *
 * This file provides the implementation for generating passwords of different types:
 * numeric, alphabetic, alphanumeric, secure, and unambiguous. Each password type
 * follows specific criteria, and the functions are designed to generate passwords
 * that meet user-defined requirements.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "password.h"


/* - - - - - - - - - - - - - - - - - PASSWORD GENERATION - - - - - - - - - - - - - - - - - */

/**
 * @brief Generates a numeric password.
 *
 * This function generates a password consisting of numeric digits (0-9) based on the
 * specified length.
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @post The `password` array contains a null-terminated numeric password.
 */
void generate_numeric(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = '0' + rand() % 10; /**< Generate digits between 0 and 9 */
    }
    password[length] = '\0'; /**< Null-terminate the password */
}

/**
 * @brief Generates a lowercase alphabetic password.
 *
 * This function generates a password consisting of lowercase alphabetic characters (a-z)
 * based on the specified length.
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @post The `password` array contains a null-terminated alphabetic password.
 */
void generate_alpha(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = 'a' + rand() % 26; /**< Generate letters between 'a' and 'z' */
    }
    password[length] = '\0'; /**< Null-terminate the password */
}

/**
 * @brief Generates an alphanumeric password.
 *
 * This function generates a password consisting of both numeric digits (0-9) and lowercase
 * alphabetic characters (a-z).
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @post The `password` array contains a null-terminated alphanumeric password.
 */
void generate_mixed(char *password, int length) {
    for (int i = 0; i < length; i++) {
        password[i] = (rand() % 2) ? 'a' + rand() % 26 : '0' + rand() % 10; /**< Randomly select a letter or digit */
    }
    password[length] = '\0'; /**< Null-terminate the password */
}

/**
 * @brief Generates a secure password.
 *
 * This function generates a password containing a mix of lowercase and uppercase letters,
 * numeric digits, and special characters.
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @post The `password` array contains a null-terminated secure password.
 */
void generate_secure(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)]; /**< Select a random character from the charset */
    }
    password[length] = '\0'; /**< Null-terminate the password */
}

/**
 * @brief Generates an unambiguous secure password.
 *
 * This function generates a password that avoids visually similar characters (e.g., `1`, `l`, `I`,
 * `O`, and `0`). This is useful for environments where passwords may be read aloud or viewed on screens.
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @post The `password` array contains a null-terminated unambiguous secure password.
 */
void generate_unambiguous(char *password, int length) {
    const char charset[] = "abcdefghjkmnpqrtuvwxyACDEFGHJKLMNPQRTUVWXY34679!@#$%^&*()";
    for (int i = 0; i < length; i++) {
        password[i] = charset[rand() % (sizeof(charset) - 1)]; /**< Select a random character from the charset */
    }
    password[length] = '\0'; /**< Null-terminate the password */
}

/**
 * @brief Generates a password based on the specified type and length.
 *
 * This function serves as the main interface for password generation. It delegates password
 * creation to the appropriate function based on the `type` parameter.
 *
 * @param[out] password Pointer to a pre-allocated array where the password will be stored.
 * @param[in] type The type of password to generate (see `PasswordType` enum).
 * @param[in] length The desired length of the password. Must be a positive integer.
 *
 * @pre The `password` array should be large enough to hold `length + 1` characters.
 * @pre `type` must be one of the valid values defined in the `PasswordType` enum.
 * @post The `password` array contains a null-terminated password of the specified type.
 *
 * @note This function initializes the random number generator automatically on the first call.
 */
void generate_password(char *password, PasswordType type, int length) {
    switch(type) {
        case NUMERIC:
            generate_numeric(password, length);
            break;
        case ALPHA:
            generate_alpha(password, length);
            break;
        case MIXED:
            generate_mixed(password, length);
            break;
        case SECURE:
            generate_secure(password, length);
            break;
        case UNAMBIGUOUS:
            generate_unambiguous(password, length);
            break;
    }
}

/* - - - - - - - - - - - - - - - - END PASSWORD GENERATION - - - - - - - - - - - - - - - - */
