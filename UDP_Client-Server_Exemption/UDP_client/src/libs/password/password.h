/**
 * @file password.h
 * @brief Header file that defines functions for password validation.
 *
 * This file provides declarations for the following functions:
 * - Password type validation.
 * - Password length check.
 * - Control of password generation continuation or termination.
 *
 * @version 1.0.0
 * @date 2024-12-20
 * @author Michele Camassa
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include <stdbool.h>

/* - - - - - - - - - - - - - - - - - PASSWORD CHECKS - - - - - - - - - - - - - - - - - */

/**
 * @brief Determines whether to continue password generation.
 *
 * Compares the current password type (`type`) with a termination type (`type_for_ending`).
 * Password generation continues only if the two types are different.
 *
 * @param[in] type Current password type to process.
 * @param[in] type_for_ending Type that signals the end of generation.
 *
 * @pre `type` and `type_for_ending` must be valid characters.
 * @return `true` if `type` is different from `type_for_ending`, allowing generation to continue.
 * @return `false` if `type` matches `type_for_ending`, signaling the end of generation.
 */
bool keep_generating(const char type, const char type_for_ending);


/**
 * @brief Validates the requested password type against allowed types.
 *
 * Verifies that `type` belongs to a predefined set of valid characters.
 * Valid types could include numeric ('n'), alphabetical ('a'), mixed ('m'), etc.
 *
 * @param[in] allowed_type A string containing valid password types (e.g., "nams").
 * @param[in] type The specific password type to validate.
 *
 * @pre `allowed_type` must not be `NULL` and must be a null-terminated string.
 * @pre `type` must be a single character.
 * @return `true` if `type` is present in `allowed_type`.
 * @return `false` if `type` is not present in `allowed_type`.
 */
bool control_type(const char *allowed_type, const char type);


/**
 * @brief Checks if the requested password length is valid.
 *
 * Verifies that the string `length` represents a positive integer within the range
 * specified (`[min_length, max_length]`). Handles non-numeric or invalid input appropriately.
 *
 * @param[in] length String representing the desired password length.
 * @param[in] min_length Minimum allowed length for the password.
 * @param[in] max_length Maximum allowed length for the password.
 *
 * @pre `length` must be a numeric string terminated by `NULL`.
 * @return `true` if `length` is numeric and falls within the valid range.
 * @return `false` if `length` is invalid, negative, or out of range.
 */
bool control_length(const char *length, const int min_length, const int max_length);

/* - - - - - - - - - - - - - - - END PASSWORD CHECKS - - - - - - - - - - - - - - - - - - */

#endif /* PASSWORD_H_ */
