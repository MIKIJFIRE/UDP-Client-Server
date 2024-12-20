/**
 * @file password.h
 * @brief Header file providing functions to generate passwords
 *        based on user-specified criteria.
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_

#include <stdbool.h>


/* - - - - - - - - - - - - - - - - - - - PASSWORD TYPES - - - - - - - - - - - - - - - - - */

/**
 * @enum PasswordType
 * @brief Enumerates the types of passwords that can be generated.
 *
 * This enumeration defines various password formats that the system can generate:
 * - `NUMERIC`: Generates a password consisting of numeric digits (0-9) only.
 * - `ALPHA`: Generates a password using lowercase alphabetic characters (a-z).
 * - `MIXED`: Generates a password with a mix of lowercase alphabetic characters and numeric digits.
 * - `SECURE`: Generates a password using both lowercase and uppercase alphabetic characters, digits, and symbols.
 * - `UNAMBIGUOUS`: Generates a secure password excluding visually similar characters (e.g., O/0, l/1, etc.).
 */
typedef enum {
    NUMERIC,     /**< Numeric password: contains digits only (0-9) */
    ALPHA,       /**< Alphabetic password: contains lowercase letters only (a-z) */
    MIXED,       /**< Alphanumeric password: combination of lowercase letters and digits */
    SECURE,      /**< Secure password: includes lowercase, uppercase letters, digits, and symbols */
    UNAMBIGUOUS  /**< Unambiguous password: excludes visually similar characters (e.g., O/0, l/1) */
} PasswordType;

/* - - - - - - - - - - - - - - - - - - END PASSWORD TYPES - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - PASSWORD GENERATION - - - - - - - - - - - - - - - - - - */

/**
 * @brief Generates a password based on the specified type and length.
 *
 * This function generates a password according to the specified `type` (NUMERIC, ALPHA, MIXED, SECURE, or UNAMBIGUOUS)
 * and the desired `length`. The generated password is stored in the `password` array, which must be pre-allocated
 * by the caller. The resulting password will be null-terminated.
 *
 * ### Password Type Details:
 * - **NUMERIC**: A password consisting of numeric digits (e.g., "837261").
 * - **ALPHA**: A password made up of lowercase alphabetic characters (e.g., "qwerty").
 * - **MIXED**: A combination of lowercase alphabetic characters and digits (e.g., "abc123").
 * - **SECURE**: A password containing lowercase/uppercase letters, digits, and symbols (e.g., "Pa$sW0rd!").
 * - **UNAMBIGUOUS**: Similar to SECURE, but excludes visually ambiguous characters such as `O`, `0`, `l`, `1` (e.g., "Tg@8%Yk").
 *
 * @param[out] password A pre-allocated array to store the generated password.
 *                      The array must have space for at least `length + 1` characters,
 *                      accounting for the null terminator.
 * @param[in] type The type of password to generate, as defined in the `PasswordType` enum.
 * @param[in] length The desired length of the generated password. It must be greater than 0.
 *
 * @pre The `password` array must be a valid pointer to a pre-allocated memory region.
 * @pre The `length` parameter must be greater than 0 and less than or equal to the maximum supported length.
 * @post The `password` array will contain a null-terminated password of the specified type and length.
 * @note If the `password` array is not allocated correctly or the `length` is invalid, the behavior is undefined.
 */
void generate_password(char *password, PasswordType type, int length);

/* - - - - - - - - - - - - - - - - - END PASSWORD GENERATION - - - - - - - - - - - - - - - - - */

#endif /* PASSWORD_H_ */
