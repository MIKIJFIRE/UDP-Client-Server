/**
 * @file UDP_server.c
 * @brief Implementation of the UDP server in C for handling password generation requests.
 *        It listens for incoming requests from clients, processes them, and sends responses.
 * @version 1.0.1
 * @date 2024-12-20
 * @author Michele Camassa
 */

#if defined WIN32
#include <winsock.h> 		/**< Includes the Winsock header for Windows */
#else
#include <unistd.h>  		/**< Includes the standard UNIX header for close() */
#include <sys/socket.h>  	/**< Includes the socket library for UNIX */
#include <arpa/inet.h>  	/**< Includes the ARP and Internet address libraries */
#include <sys/types.h>   	/**< Includes for socket types */
#include <netinet/in.h>  	/**< Includes for Internet address family structures */
#include <netdb.h>  		/**< Includes for host and network database */
#define closesocket close  	/**< Defines closesocket as close for UNIX systems */
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "libs/password/password.h"  /**< Includes the header for password generation functions */
#include "libs/protocol/protocol.h"  /**< Includes protocol definitions for communication */
#include "libs/utils/utils.h"    	 /**< Includes utility functions */


/**
 * @brief Cleans up the Winsock library (Windows only).
 * @details This function ensures proper termination of the Winsock library to free resources.
 */
void clear_winsock() {
#if defined WIN32
	WSACleanup();  /**< Cleans up the Winsock DLL */
#endif
}

/**
 * @brief Prints an error message in the terminal with magenta color.
 * @param[in] error_message The error message to display.
 * @note On Windows, the program pauses for 3 seconds after printing the error.
 */
void error_handler(const char *error_message) {
    print_with_color(error_message, MAGENTA); /**< Displays the error message */
#if defined WIN32
	Sleep(3000);  /**< 3-second pause */
#endif
}

/**
 * @brief Creates and initializes a UDP socket.
 * @details This function creates a socket for communication using the UDP protocol.
 * @return >=0 The socket descriptor if socket creation is successful.
 * @return -1 If there is an error creating the socket.
 */
int initialize_socket() {
    int created_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (created_socket < 0) {
        error_handler("Error creating the socket.\n");
    }
    return created_socket;
}

/**
 * @brief Sets up the server address structure.
 * @param[out] server_address Pointer to the sockaddr_in structure to configure.
 * @pre `server_address` must be a valid pointer.
 * @post The `server_address` structure is configured with default values.
 */
void setup_server_address(struct sockaddr_in *server_address) {
    memset(server_address, 0, sizeof(*server_address));			/**< Clears the structure */
    server_address->sin_family = AF_INET;						/**< Sets the address family to AF_INET (IPv4) */
    server_address->sin_port = htons(DEFAULT_PORT);				/**< Sets the server's port, converted to network byte order */
    server_address->sin_addr.s_addr = inet_addr(DEFAULT_IP);	/**< Sets the server's IP address */
}

/**
 * @brief Processes a password generation request and generates the password.
 * @param[in] request Pointer to the PasswordRequest structure containing the client input.
 * @param[out] response Pointer to the PasswordResponse structure to store the generated password.
 * @pre `request` and `response` must be valid and initialized pointers.
 * @post The `response` structure is populated with the generated password.
 */
void handle_password_request(const PasswordRequest *request, PasswordResponse *response) {
	int numerical_length = atoi(request->length);
	PasswordType password_type;

	switch (tolower(request->type)) {
		case 'n': password_type = NUMERIC; break;
		case 'a': password_type = ALPHA; break;
		case 'm': password_type = MIXED; break;
		case 's': password_type = SECURE; break;
		case 'u': password_type = UNAMBIGUOUS; break;
		default: password_type = NUMERIC; break;
	}
	generate_password(response->password, password_type, numerical_length);
}

/**
 * @brief Sends a response containing the password to the client.
 * @param[in] server_socket The server's socket descriptor.
 * @param[in] response_msg Pointer to the PasswordResponse structure to send.
 * @param[in] client_address Pointer to the sockaddr_in structure containing the client's address.
 * @return `true` if the response was sent successfully, `false` otherwise.
 * @pre `server_socket` must be a valid UDP socket.
 * @pre `response_msg` and `client_address` must be valid pointers.
 * @post The client receives the response with the password if the sending is successful.
 */
bool send_response(int server_socket, const PasswordResponse *response_msg, const struct sockaddr_in *client_address) {
    if (sendto(server_socket, response_msg, sizeof(*response_msg), 0,
               (struct sockaddr *)client_address, sizeof(*client_address)) != sizeof(*response_msg)) {
        error_handler("Error sending the response (Generated password).\n");
        return false;
    }
    return true;
}

/**
 * @brief Receives a password generation request from the client.
 * @param[in] server_socket The server's socket descriptor.
 * @param[out] request_msg Pointer to the PasswordRequest structure to store the client's request.
 * @param[out] client_address Pointer to the sockaddr_in structure to store the client's address.
 * @return `true` if the request was received successfully, `false` otherwise.
 * @pre `server_socket` must be a valid UDP socket.
 * @pre `request_msg` and `client_address` must be valid pointers.
 * @post The `request_msg` and `client_address` structures are populated with the client's data if receiving is successful.
 */
bool receive_request(int server_socket, PasswordRequest *request_msg, struct sockaddr_in *client_address) {
    unsigned int client_address_size = sizeof(*client_address);
    int rcv_msg_size = recvfrom(server_socket, request_msg, sizeof(*request_msg), 0,
                                (struct sockaddr *)client_address, &client_address_size);
    if (rcv_msg_size < 0) {
        error_handler("Error receiving the request (Password settings).\n");
        return false;
    }
    return true;
}

/**
 * @brief Entry point for the UDP server program.
 * @return Program exit status.
 * @return EXIT_SUCCESS If the server ran successfully.
 * @return EXIT_FAILURE If an error occurred during execution.
 * @details Initializes the server, listens for client requests, and processes them in an infinite loop.
 */
int main() {

#if defined WIN32
	// Initialize Winsock
	WSADATA wsa_data;  /**< Contains information about the Windows Sockets implementation */
	WORD version_requested = MAKEWORD(2,2);  /**< Requests Winsock version 2.2 */
	int result = WSAStartup(version_requested, &wsa_data);  /**< Initializes the Winsock library */
	if (result != NO_ERROR) {
		error_handler("Error during WSAStartup()\nUnable to find a usable Winsock DLL.\n");
		return 0;
	}
#endif

    int server_socket = initialize_socket();
    if (server_socket < 0) {
        clear_winsock();
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_address, client_address;

    setup_server_address(&server_address);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    	error_handler("Bind failed.\n");
        closesocket(server_socket);
        clear_winsock();
        return EXIT_FAILURE;
    }

    print_with_color("Server listening...\n\n", BLUE);

    while (true) {
        PasswordRequest request;
        PasswordResponse response;

        if (!receive_request(server_socket, &request, &client_address)) {
            closesocket(server_socket);
            clear_winsock();
            return EXIT_FAILURE;
        }

        print_with_color("New connection from ", GREEN);
        print_with_color(inet_ntoa(client_address.sin_addr), YELLOW);
        print_with_color(":", CYAN);
        printf("%d\n", ntohs(client_address.sin_port));

        handle_password_request(&request, &response);

        if (!send_response(server_socket, &response, &client_address)) {
            closesocket(server_socket);
            clear_winsock();
            return EXIT_FAILURE;
        }

    }
}
