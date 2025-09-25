#include "../include/client.h"

int init_client(struct client_info *client, const char *server_ip, int server_port) {
    // Create socket
    client->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->socket_fd < 0) {
        handle_error("Socket creation failed");
        return -1;
    }

    // Set socket options
    set_socket_options(client->socket_fd);

    // Configure server address structure
    memset(&client->server_addr, 0, sizeof(client->server_addr));
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &client->server_addr.sin_addr) <= 0) {
        handle_error("Invalid address/ Address not supported");
        close(client->socket_fd);
        return -1;
    }

    log_message("Client initialized successfully");
    return 0;
}

void close_client(struct client_info *client) {
    if (client->socket_fd >= 0) {
        close(client->socket_fd);
        log_message("Client socket closed");
    }

    client->socket_fd = -1;
    free(client);
}

void handle_error(const char *msg) {
    perror(msg);
    log_message(msg);
    exit(EXIT_FAILURE);
}

void log_message(const char *msg) {
    FILE *log_file = fopen(LOG_FILE, "a");
    if (log_file) {
        fprintf(log_file, "%s\n", msg);
        fclose(log_file);
    }
}

void set_socket_options(int socket_fd) {
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        handle_error("Set socket options failed");
    }
}