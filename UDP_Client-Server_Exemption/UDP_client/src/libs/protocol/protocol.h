/**
 * @file protocol.h
 * @brief Header file used to define constants, structures, and data specific
 *        to the protocol supporting client communication in the `UDP_client.c` file.
 *
 * This file centralizes communication parameters, such as buffer size,
 * password constraints, and data structures for handling requests and responses.
 *
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

/* - - - - - - - - - - - - - - - - - - - CONSTANTS - - - - - - - - - - - - - - - - - */

/**
 * @brief Defines the maximum buffer size used for communication.
 *
 * The buffer serves multiple purposes, including:
 * - Storing server names.
 * - Managing password lengths during requests.
 * - General communication between the client and the server.
 *
 * Using a large buffer size ensures flexibility for various operations
 * while avoiding memory overflow risks.
 */
#define BUFFER_SIZE 1024        /**< Maximum buffer size */


/**
 * @brief Maximum allowed length for a generated password.
 *
 * Passwords longer than this value will not be accepted by either the client or the server.
 * This constant ensures compatibility and usability across different systems.
 */
#define MAX_PASSWORD_LENGTH 32  /**< Maximum password length */

/**
 * @brief Minimum allowed length for a generated password.
 *
 * Passwords shorter than this value are considered insecure and will be rejected.
 */
#define MIN_PASSWORD_LENGTH 6  /**< Minimum password length */


/**
 * @brief Default port number used for client-server communication.
 *
 * The client will connect to the server using this port unless specified otherwise.
 * The default value of 8080 is commonly used for development and testing purposes.
 */
#define DEFAULT_PORT 8080       /**< Default communication port */

/* - - - - - - - - - - - - - - - - - - - END CONSTANTS - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - STRUCTURES - - - - - - - - - - - - - - - - - - - */

/**
 * @struct PasswordRequest
 * @brief Represents the client's request for password generation.
 *
 * This structure is sent by the client to the server and includes:
 * - `type`: Specifies the type of password requested (e.g., numeric, alphanumeric, etc.).
 * - `length`: A string indicating the desired length of the generated password.
 *
 * @note `length` is stored as a string to facilitate flexible input validation
 *       and avoid overflow issues during parsing.
 */
typedef struct {
    char type;        				/**< Requested password type ('n', 'a', 'm', etc.) */
    char length[BUFFER_SIZE];       /**< Desired password length as a string */
} PasswordRequest;

/**
 * @struct PasswordResponse
 * @brief Represents the server's response containing the generated password.
 *
 * This structure is sent by the server to the client and includes:
 * - `password`: The password actually generated by the server.
 *
 * @note The `password` field is null-terminated to ensure correct handling as a C string.
 */
typedef struct {
    char password[MAX_PASSWORD_LENGTH + 1];  /**< The generated password */
} PasswordResponse;

/* - - - - - - - - - - - - - - - - - - - END STRUCTURES - - - - - - - - - - - - - - - - - - - - - */

#endif // PROTOCOL_H