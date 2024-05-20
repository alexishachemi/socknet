/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** packet receiving
*/

#include <string.h>
#include <stdlib.h>
#include "socknet_dev.h"

static bool handle_recv_fail(net_t *net, int sock)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "Failed to receive packet from socket %d, kicking client...",
                sock);
        nets_kick(net, sock);
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL,
            "Failed to receive packet from server, disconnecting...");
        netc_disconnect(net);
    }
    return false;
}

static bool handle_bad_header(net_t *net, int sock)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "Bad header from socket %d, kicking client...", sock);
        nets_kick(net, sock);
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL, "Bad header from server, disconnecting...");
        netc_disconnect(net);
    }
    return false;
}

static bool recv_header(net_t *net, int sock, net_header_t *h_buf)
{
    int status = 0;

    status = recv(sock, h_buf, sizeof(net_header_t), MSG_NOSIGNAL);
    if (status != sizeof(net_header_t))
        return handle_recv_fail(net, sock);
    if (h_buf->type != NET_DATA || h_buf->data_size > MAX_PACKET_SIZE)
        return handle_bad_header(net, sock);
    return true;
}

static bool recv_data(net_t *net, int sock, void **d_buf, unsigned int n)
{
    int status = 0;

    *d_buf = malloc(n);
    if (!d_buf)
        return handle_recv_fail(net, sock);
    status = recv(sock, *d_buf, n, MSG_NOSIGNAL);
    if ((unsigned int)status != n) {
        free(*d_buf);
        return handle_recv_fail(net, sock);
    }
    return true;
}

static bool queue_transfer(net_t *net, int sock, const net_transfer_t *t)
{
    net_transfer_t *transfer = NULL;

    transfer = list_add(&net->to_recv, alloc_transfer);
    if (!transfer) {
        free(t->packet.data);
        return FALSE_NLOG(net, ERROR,
            "Failed to queue packet received from socket %d", sock);
    }
    memcpy(transfer, t, sizeof(net_transfer_t));
    return true;
}

bool net_recv_packet(net_t *net, int sock)
{
    net_transfer_t transfer = {0};
    net_header_t *header = &transfer.packet.header;
    void **data = &transfer.packet.data;

    transfer.connection.sock = sock;
    if (!net || sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to receive packet, bad args");
    if (!net_sock_can_read(sock, SELECT_TIMEOUT_MS))
        return true;
    if (!recv_header(net, sock, header)
        || !recv_data(net, sock, data, header->data_size))
        return false;
    if (!net_send_response(net, sock)) {
        free(*data);
        return false;
    }
    if (!queue_transfer(net, sock, &transfer))
        return false;
    return TRUE_NLOG(net, DEBUG, "Successfully received packet from socket %d",
        sock);
}

static bool server_fetch_packets(net_t *net)
{
    net_connection_t *connection = NULL;

    for (size_t i = 0; i < list_size(&net->server.clients); i++) {
        connection = list_at(&net->server.clients, i);
        if (!net_recv_packet(net, connection->sock))
            return false;
    }
    return true;
}

static bool client_fetch_packets(net_t *net)
{
    return net_recv_packet(net, net->sock);
}

bool net_fetch_packets(net_t *net)
{
    if (!net)
        return FALSE_NLOG(net, ERROR, "Failed to fetch packets, bad args");
    if (net->type == NET_SERVER)
        return server_fetch_packets(net);
    if (net->type == NET_CLIENT)
        return client_fetch_packets(net);
    return FALSE_NLOG(net, ERROR, "Failed to fetch packets, bad type");
}
