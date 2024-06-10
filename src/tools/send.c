/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** packet sending
*/

#include "socknet_dev.h"

static bool handle_send_fail(net_t *net, int sock, int size, int status)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "Failed to send packet to socket %d (size: %d, status: %d), "
            "kicking client...", sock, size, status);
        nets_kick(net, sock);
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL,
            "Failed to send packet to server (size: %d, status: %d), "
            "disconnecting...", size, status);
        netc_disconnect(net);
    }
    return false;
}

bool net_send_packet(net_t *net, const net_transfer_t *transfer)
{
    int status = 0;
    int sock = -1;
    const net_packet_t *packet = transfer ? &transfer->packet : NULL;
    size_t size = 0;

    if (!net || !transfer || transfer->connection.sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to send packet, bad args");
    if (!net_sock_can_write(transfer->connection.sock, SELECT_TIMEOUT_MS))
        return FALSE_NLOG(net, DEBUG, "Cannot write to socket %d",
            transfer->connection.sock);
    sock = transfer->connection.sock;
    size = transfer->packet.header.data_size;
    status = send(sock, &packet->header, sizeof(net_header_t), MSG_NOSIGNAL);
    status += send(sock, packet->data, size, MSG_NOSIGNAL);
    if ((size_t)status != size + sizeof(net_header_t))
        return handle_send_fail(net, sock, size, status);
    if (!net_await_response(net, sock))
        return false;
    return TRUE_NLOG(net, DEBUG, "Successfully sent packet to socket %d",
        sock);
}

bool net_send_queued(net_t *net)
{
    net_transfer_t *transfer = NULL;

    if (!net)
        return FALSE_NLOG(net, ERROR,
            "Failed to send queued packets, bad args");
    if (!net_will_send(net))
        return true;
    transfer = list_at(&net->to_send, 0);
    if (!net_send_packet(net, transfer))
        return false;
    list_remove(&net->to_send, free_transfer, 0);
    return true;
}
