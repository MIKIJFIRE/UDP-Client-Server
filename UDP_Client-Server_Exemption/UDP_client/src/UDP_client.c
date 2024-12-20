/**
 * @file UDP_client.c
 * @brief UDP client for requesting password generation from a remote server.
 * @details This client communicates with a password generation server via UDP. It sends a request specifying
 * the desired password type and length, and receives the generated password as a response.
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#if defined WIN32
#include <winsock.h>        /**< Include Winsock library for Windows */
#else
#include <unistd.h>         /**< Include UNIX standard header for close() */
#include <sys/socket.h>     /**< Include socket library for UNIX systems */
#include <arpa/inet.h>      /**< Include ARP and Internet address family libraries */
#include <sys/types.h>      /**< Include for socket types */
#include <netinet/in.h>     /**< Include for internet address family structures */
#include <netdb.h>          /**< Include for host and network database functions */
#define closesocket close   /**< Define closesocket as close for UNIX systems */
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "libs/password/password.h"  /**< Password handling functions */
#include "libs/protocol/protocol.h"  /**< Communication protocol definitions */
#include "libs/utils/utils.h"        /**< Utility functions library */


/**
 * @brief Clean up Winsock resources (Windows only).
 * @details Ensures proper cleanup of Winsock resources before exiting the application.
 */
void clear_winsock() {
#if defined WIN32
    WSACleanup();  /**< Free resources allocated by Winsock */
#endif
}

/**
 * @brief Print error messages in magenta.
 * @param[in] error_message The error message to display.
 * @note On Windows, the program pauses for 3 seconds after showing the error message.
 */
void error_handler(const char *error_message) {
    print_with_color(error_message, MAGENTA); /**< Print the error in magenta color */
#if defined WIN32
    Sleep(3000);  /**< Pause for 3 seconds */
#endif
}

/**
 * @brief Initialize a UDP socket.
 * @details Creates and initializes a socket for UDP communication.
 * @return >=0 The socket descriptor on success.
 * @return -1 If an error occurs while creating the socket.
 */
int initialize_socket() {
    int created_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (created_socket < 0) {
        error_handler("Error creating socket.\n");
    }
    return created_socket;
}

/**
 * @brief Resolve the server hostname to an IP address.
 * @details Uses `gethostbyname` to resolve the server hostname and populate a sockaddr_in structure.
 * @param[in] server_name The hostname of the server.
 * @param[out] server_address A pointer to a sockaddr_in structure to store the resolved address.
 * @return true if the hostname is resolved successfully.
 * @return false if an error occurs during resolution.
 */
bool resolve_server_address(const char *server_name, struct sockaddr_in *server_address) {
    struct hostent *host = gethostbyname(server_name);
    if (host == NULL) {
        error_handler("Error resolving host\n");
        return false;
    }
    memset(server_address, 0, sizeof(struct sockaddr_in)); /**< Clear the structure */
    server_address->sin_family = AF_INET;                  /**< Use IPv4 */
    server_address->sin_addr = *((struct in_addr *)host->h_addr); /**< Copy server IP address */
    server_address->sin_port = htons(DEFAULT_PORT);        /**< Convert port to network byte order */
    return true;
}

/**
 * @brief Prompt user for password type and length.
 * @details Displays a menu to the user and validates the input for password generation parameters.
 * @param[out] password_request A pointer to a PasswordRequest structure to store user input.
 * @return true if the input is valid.
 * @return false if the input is invalid.
 */
bool handle_user_input(PasswordRequest *password_request) {
    char input[BUFFER_SIZE];
    int arguments;

    do {
        show_password_menu();                /**< Show the menu options */
        fgets(input, sizeof(input), stdin); /**< Get user input */
        input[BUFFER_SIZE - 1] = '\0';      /**< Ensure null termination */

        arguments = sscanf(input, " %c %s %s", &password_request->type, password_request->length, input);
        password_request->length[BUFFER_SIZE - 1] = '\0';

        if (tolower(password_request->type) == 'h') {
            show_help_menu(); /**< Show help menu */
        }
    } while (tolower(password_request->type) == 'h');

    if (arguments == 1) {
        strcpy(password_request->length, "8"); /**< Default to length 8 */
    } else if (arguments != 2) {
        print_with_color("Invalid input. Please provide a valid type and length.\n", RED);
        return false;
    }

    if (!control_type("namsuq", password_request->type)) {
        print_with_color("Invalid type. Please choose a valid option.\n", RED);
        return false;
    }

    if (!control_length(password_request->length, MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH)) {
        print_with_color("Invalid length. Please choose a valid range.\n", RED);
        return false;
    }

    return true;
}

/**
 * @brief Send a password request to the server.
 * @details Sends a PasswordRequest structure to the server address specified.
 * @param[in] client_socket The socket descriptor.
 * @param[in] password_request Pointer to the PasswordRequest structure.
 * @param[in] server_address Pointer to the server's sockaddr_in structure.
 * @return true if the request is sent successfully.
 * @return false if an error occurs during sending.
 */
bool send_request(int client_socket, const PasswordRequest *password_request, const struct sockaddr_in *server_address) {
    if (sendto(client_socket, password_request, sizeof(*password_request), 0,
               (struct sockaddr *)server_address, sizeof(*server_address)) != sizeof(*password_request)) {
        error_handler("Error sending password request.\n");
        return false;
    }
    return true;
}

/**
 * @brief Receive the password response from the server.
 * @param[in] client_socket The socket descriptor.
 * @param[out] response_msg Pointer to the PasswordResponse structure to store the response.
 * @param[in] server_address Pointer to the sockaddr_in structure of the server.
 * @return true if the response is received successfully.
 * @return false if an error occurs during reception.
 */
bool receive_response(int client_socket, PasswordResponse *response_msg, struct sockaddr_in *server_address) {
    unsigned int server_address_size = sizeof(*server_address);
    int rcv_msg_size = recvfrom(client_socket, response_msg, sizeof(*response_msg), 0,
                                (struct sockaddr *)server_address, &server_address_size);
    if (rcv_msg_size < 0) {
        error_handler("Error receiving password response.\n");
        return false;
    }
    return true;
}

/**
 * @brief Main function of the UDP client.
 * @details Initializes the socket, resolves the server address, and communicates with the password generation server.
 * The client continues until the user decides to quit.
 * @return EXIT_SUCCESS on successful completion.
 * @return EXIT_FAILURE if an error occurs during execution.
 */
int main() {

#if defined WIN32
    WSADATA wsa_data;
    WORD version_requested = MAKEWORD(2,2);
    int result = WSAStartup(version_requested, &wsa_data);
    if (result != NO_ERROR) {
        error_handler("Error initializing Winsock.\n");
        return EXIT_FAILURE;
    }
#endif

    struct sockaddr_in server_address;

    if (!resolve_server_address("passwdgen.uniba.it", &server_address)) {
        clear_winsock();
        return EXIT_FAILURE;
    }

    int client_socket = initialize_socket();
    if (client_socket < 0) {
        clear_winsock();
        return EXIT_FAILURE;
    }

    PasswordRequest password_request;
    PasswordResponse response_msg;

    while (true) {
        if (!handle_user_input(&password_request)) {
            continue;
        }

        if (!keep_generating(password_request.type, 'q')) {
            break;
        }

        if (!send_request(client_socket, &password_request, &server_address)) {
            closesocket(client_socket);
            clear_winsock();
            return EXIT_FAILURE;
        }

        if (!receive_response(client_socket, &response_msg, &server_address)) {
            closesocket(client_socket);
            clear_winsock();
            return EXIT_FAILURE;
        }

        print_with_color("Password generated: ", GREEN);
        print_with_color(response_msg.password, GREEN);
        printf("\n\n");
    }

    closesocket(client_socket);
    clear_winsock();
#if defined WIN32
    Sleep(3000);
#endif
    return EXIT_SUCCESS;
}
