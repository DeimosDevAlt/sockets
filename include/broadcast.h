#include "client.h"
#include "packet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct packet* receive_data(struct client_info* client);
int send_data(struct client_info* client, struct packet* pkt);
void handle_client(struct client_info* client);