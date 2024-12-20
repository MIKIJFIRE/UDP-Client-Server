 /**
 * @file protocol.h
 * @brief Header file used to define constants, structs, and protocol-specific
 *        data structures for supporting server communication in the `UDP_server.c` file.
 *
 * This file centralizes communication parameters, such as buffer size, password constraints,
 * and data structures for handling request-response communication between the client and server.
 *
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

/* - - - - - - - - - - - - - - - - - - - CONSTANTS - - - - - - - - - - - - - - - - */

/**
 * @brief Defines the maximum size of the buffer used for communication.
 *
 * The buffer is utilized for various purposes, including:
 * - Storing server names.
 * - Handling password lengths during requests.
 * - General data transfer between the client and server.
 *
 * By choosing an adequate buffer size, we ensure flexibility for various operations
 * while avoiding memory overflow risks.
 */
#define BUFFER_SIZE 1024        /**< Maximum buffer size used for communication */


/**
 * @brief Maximum allowable length for a generated password.
 *
 * Passwords exceeding this length will not be accepted by either the client or server.
 * This constant ensures compatibility and usability across different systems and avoids
 * potential security risks related to extremely long passwords.
 */
#define MAX_PASSWORD_LENGTH 32  /**< Maximum permissible password length */

/**
 * @brief Minimum allowable length for a generated password.
 *
 * Passwords shorter than this length are considered insecure and will be rejected
 * by the system to ensure strong password policies.
 */
#define MIN_PASSWORD_LENGTH 6   /**< Minimum allowed password length */


/**
 * @brief Default port number for client-server communication.
 *
 * The default port, 8080, is typically used for development and testing. It is the
 * default port number that clients will attempt to use when connecting to the server.
 */
#define DEFAULT_PORT 8080       /**< Default port number for communication */

/**
 * @brief Default IP address used for client-server communication.
 *
 * The default IP is set to `127.0.0.1`, the loopback address, which facilitates local
 * communication between the client and server during development and testing.
 */
#define DEFAULT_IP "127.0.0.1"  /**< Default IP address used for the server-client connection */

/* - - - - - - - - - - - - - - - - - - - END CONSTANTS - - - - - - - - - - - - - - - - */

/* - - - - - - - - - - - - - - - - - - STRUCTURES - - - - - - - - - - - - - - - - - - - - */

/**
 * @struct PasswordRequest
 * @brief Represents a client request for password generation.
 *
 * This structure is sent from the client to the server, containing:
 * - `type`: Specifies the type of password (e.g., numeric, alphanumeric).
 * - `length`: Specifies the desired length of the generated password.
 *
 * @note The `length` is stored as a string to allow for flexible validation and
 *       to avoid potential overflow issues during parsing on the server.
 */
typedef struct {
    char type;        				/**< Type of password requested (e.g., 'n' for numeric, 'a' for alphabetic) */
    char length[BUFFER_SIZE];       /**< Desired length of the password (stored as a string for flexibility) */
} PasswordRequest;

/**
 * @struct PasswordResponse
 * @brief Represents the server's response containing the generated password.
 *
 * This structure is sent from the server back to the client and includes:
 * - `password`: The generated password string.
 *
 * @note The `password` field is null-terminated to ensure proper handling as a C string.
 */
typedef struct {
    char password[MAX_PASSWORD_LENGTH + 1];  /**< The generated password, null-terminated */
} PasswordResponse;

/* - - - - - - - - - - - - - - - - - - - END STRUCTURES - - - - - - - - - - - - - - - - - - - - - */

#endif // PROTOCOL_H
