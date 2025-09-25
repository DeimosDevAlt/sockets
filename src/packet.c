#include "../include/packet.h"

void write_packet(struct packet* pkt, uint16_t seq_num, uint16_t ack_num, uint8_t flags, const char* payload, uint16_t length) {
    // Minimal packet information
    
    pkt->seq_num = seq_num;
    pkt->ack_num = ack_num;
    pkt->flags = flags;
    pkt->length = length > sizeof(pkt->payload) ? sizeof(pkt->payload) : length;
    if (payload && length > 0) {
        memcpy(pkt->payload, payload, pkt->length);
    } else {
        memset(pkt->payload, 0, sizeof(pkt->payload));
    }
}

int read_packet(const char* buffer, size_t buffer_size, struct packet* pkt) {
    if (buffer_size < sizeof(struct packet)) {
        return -1; // Buffer too small
    }
    memcpy(pkt, buffer, sizeof(struct packet));
    return 0;
}

void print_packet(const struct packet* pkt) {
    // Simple print function for debugging

    printf("Packet:\n");
    printf("  Seq Num: %u\n", pkt->seq_num);
    printf("  Ack Num: %u\n", pkt->ack_num);
    printf("  Flags: %u\n", pkt->flags);
    printf("  Length: %u\n", pkt->length);
    printf("  Payload: %.*s\n", pkt->length, pkt->payload);
}   