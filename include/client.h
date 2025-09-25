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


#define MAX_BUFFER_SIZE 512
#define TIMEOUT_SEC 5
#define RETRY_LIMIT 3
#define LOG_FILE "client.log"

struct client_info {
    int socket_fd;
    struct sockaddr_in server_addr;
};


int init_client(struct client_info *client, const char *server_ip, int server_port);
void close_client(struct client_info *client);
void handle_error(const char *msg);
void log_message(const char *msg);
void set_socket_options(int socket_fd);