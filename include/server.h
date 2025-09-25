#include "client.h"
#include "packet.h"
#include "broadcast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 10
#define MAX_BUFFER_SIZE 512
#define LOG_FILE "server.log"

struct server_info {
    int socket_fd;
    struct sockaddr_in server_addr;
};

int init_server(struct server_info *server, int port);
void close_server(struct server_info *server);
void handle_error(const char *msg);
void log_message(const char *msg);
void set_socket_options(int socket_fd);
void process_client_request(struct client_info* client);
void handle_client(struct client_info* client);
void broadcast_message(struct client_info* sender_client, struct packet* pkt);
void remove_client(struct client_info* client);
void list_active_clients(struct client_info* clients[], int client_count);