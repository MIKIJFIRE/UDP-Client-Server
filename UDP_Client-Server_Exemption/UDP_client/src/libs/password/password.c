/**
 * @file password.c
 * @brief Implementation of functions for password parameter validation.
 *
 * This file contains the implementation of the following functionalities:
 * - Validity check of the password type.
 * - Password length check.
 * - Determining whether to continue or stop password generation.
 *
 * @version 1.0.0
 * @date 2024-12-20
 * @author Michele Camassa
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "password.h"

/* - - - - - - - - - - - - - - - - - PASSWORD CHECKS - - - - - - - - - - - - - - - - - */

/**
 * @brief Determines whether to continue password generation based on the specified type for termination.
 *
 * This function compares the current password type with a predefined type for termination.
 * If the two types match (ignoring case), the password generation stops.
 *
 * @param[in] type Current password type to be processed.
 * @param[in] type_for_ending Type indicating the end of password generation.
 *
 * @return `true` if `type` is different from `type_for_ending`, indicating that generation can continue.
 * @return `false` if `type` is equal to `type_for_ending`, indicating that generation should stop.
 *
 * @pre `type` and `type_for_ending` must be valid characters.
 * @post The function returns a boolean value indicating whether to continue or not.
 * @note The comparison is case-insensitive.
 */
bool keep_generating(const char type, const char type_for_ending) {
    return tolower(type) != tolower(type_for_ending);
}

/**
 * @brief Checks if the specified type is valid for password generation.
 *
 * This function checks if the `type` character is present in a string of allowed types.
 * The comparison is case-sensitive (distinguishes between uppercase and lowercase).
 *
 * @param[in] allowed_type Null-terminated string containing the valid allowed types.
 * @param[in] type Type to validate.
 *
 * @return `true` if `type` is found in `allowed_type`.
 * @return `false` if `type` is not found in `allowed_type`.
 *
 * @pre `allowed_type` must be a valid null-terminated string.
 * @pre `type` must be a valid character.
 * @post The function returns a boolean value indicating the validity of the type.
 * @warning Passing `NULL` as `allowed_type` causes undefined behavior.
 */
bool control_type(const char *allowed_type, const char type) {
    return strchr(allowed_type, type) != NULL;
}

/**
 * @brief Validates the password length based on an allowed range.
 *
 * The function checks that the string `length` contains only numeric characters.
 * It then converts the string to an integer and checks if the resulting value falls within
 * the specified `min_length` and `max_length` range.
 *
 * @param[in] length Null-terminated string representing the requested password length.
 * @param[in] min_length Minimum allowed password length.
 * @param[in] max_length Maximum allowed password length.
 *
 * @return `true` if `length` is numeric and represents a value within the allowed range.
 * @return `false` if `length` is not numeric or falls outside the allowed range.
 *
 * @pre `length` must be a valid null-terminated string.
 * @pre `min_length` and `max_length` must be positive numbers, with `min_length < max_length`.
 * @post The function returns a boolean value indicating the validity of the length.
 * @note Leading zeros in the `length` string are ignored during validation.
 * @warning Overflow is not explicitly handled when converting long numeric strings into integers.
 */
bool control_length(const char *length, const int min_length, const int max_length) {
    // Check that all characters in `length` are numeric digits
    for (int i = 0; length[i] != '\0'; i++) {
        if (!isdigit(length[i])) {
            return false;
        }
    }

    // Convert `length` to an integer and validate the range
    int numerical_length = atoi(length);
    return numerical_length >= min_length && numerical_length <= max_length;
}

/* - - - - - - - - - - - - - - - END PASSWORD CHECKS - - - - - - - - - - - - - - - - - */
