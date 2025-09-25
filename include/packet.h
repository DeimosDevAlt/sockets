#include <string.h>
#include <stdint.h>

struct packet {
    uint16_t seq_num;
    uint16_t ack_num;
    uint8_t flags; // e.g., SYN, ACK, FIN
    uint16_t length; // Length of the payload
    char payload[512]; // Adjust size as needed
};

void write_packet(struct packet* pkt, uint16_t seq_num, uint16_t ack_num, uint8_t flags, const char* payload, uint16_t length);
int read_packet(const char* buffer, size_t buffer_size, struct packet* pkt);
void print_packet(const struct packet* pkt);
void serialize_packet(const struct packet* pkt, char* buffer, size_t* buffer_size);
int deserialize_packet(const char* buffer, size_t buffer_size, struct packet* pkt);