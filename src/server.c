#include "../include/server.h"

int init_server(struct server_info *server, int port) {
    // Create socket
    server->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server->socket_fd < 0) {
        handle_error("Socket creation failed");
        return -1;
    }

    // Set socket options
    set_socket_options(server->socket_fd);

    // Configure server address structure
    memset(&server->server_addr, 0, sizeof(server->server_addr));
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    server->server_addr.sin_port = htons(port);

    // Bind socket to the specified port
    if (bind(server->socket_fd, (struct sockaddr *)&server->server_addr, sizeof(server->server_addr)) < 0) {
        handle_error("Bind failed");
        close(server->socket_fd);
        return -1;
    }

    log_message("Server initialized successfully");
    return 0;
}

void close_server(struct server_info *server) {
    if (server->socket_fd >= 0) {
        close(server->socket_fd);
        log_message("Server socket closed");
    }

    server->socket_fd = -1;
    free(server)
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
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        handle_error("Set socket options failed");
    }
}

void process_client_request(struct client_info* client) {
    // Placeholder for processing client requests
    // This function should be implemented to handle incoming packets from clients
}

void handle_client(struct client_info* client) {
    // Placeholder for handling individual client
    // This function should be implemented to manage client-specific logic
}

void broadcast_message(struct client_info* sender_client, struct packet* pkt) {
    // Placeholder for broadcasting messages to all clients
    // This function should be implemented to send packets to all connected clients except the sender
}

void remove_client(struct client_info* client) {
    // Placeholder for removing a client from the active clients list
    // This function should be implemented to clean up resources associated with a client
}

void list_active_clients(struct client_info* clients[], int client_count) {
    // Placeholder for listing all active clients
    // This function should be implemented to display or log the list of currently connected clients
}

