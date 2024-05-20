/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** client transfer functions
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

static bool can_send(net_t *net, const void *data, unsigned int n)
{
    if (!net || !data || n == 0)
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    if (n > MAX_PACKET_SIZE)
        return FALSE_NLOG(
            net, ERROR,
            "Failed to queue transfer, packet too big (n: %d, max: %d)",
            n, MAX_PACKET_SIZE
        );
    return true;
}

bool netc_send(net_t *net, const void *data, unsigned int n)
{
    net_transfer_t *transfer = NULL;
    net_packet_t packet = {0};

    if (!can_send(net, data, n))
        return false;
    packet.header.type = NET_DATA;
    packet.header.data_size = n;
    packet.data = malloc(n);
    if (!packet.data)
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    memcpy(packet.data, data, n);
    transfer = list_add(&net->to_send, alloc_transfer);
    if (!transfer) {
        free(packet.data);
        return FALSE_NLOG(net, ERROR, "Failed to queue transfer");
    }
    transfer->connection.sock = net->sock;
    transfer->packet = packet;
    return TRUE_NLOG(net, INFO, "Queued transfer to server");
}

bool netc_recv(net_t *net, net_transfer_t *t_buf)
{
    net_transfer_t *transfer = NULL;

    if (!net || !t_buf)
        return FALSE_NLOG(net, ERROR, "Failed to receive transfer");
    if (!net_has_to_recv(net))
        return false;
    transfer = list_pop(&net->to_recv, 0);
    memcpy(t_buf, transfer, sizeof(net_transfer_t));
    free(transfer);
    return TRUE_NLOG(net, INFO, "Received transfer from server");
}
