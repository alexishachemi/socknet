/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** server's clients handling
*/

#include "socknet_dev.h"

net_connection_t *nets_get_client(net_t *net, int sock)
{
    net_connection_t *connection = NULL;

    if (!net)
        return NULL_NLOG(net, WARN, "Couldn't get client %s", sock);
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        connection = n->data;
        if (connection->sock == sock) {
            NLOG(net, DEBUG, "Found user %s", sock);
            return n->data;
        }
    }
    return NULL_NLOG(net, WARN, "Couldn't get client %s", sock);
}

void nets_clear_sock_transfer(net_t *net, int sock)
{
    net_transfer_t *transfer = NULL;

    if (!net)
        return NLOG(net, ERROR, "Couldn't clear client %s's packets", sock);
    for (size_t i = 0; i < list_size(&net->to_send); i++) {
        transfer = list_at(&net->to_send, i);
        if (transfer->connection.sock == sock) {
            list_remove(&net->to_send, free_transfer, i);
            i--;
        }
    }
    NLOG(net, DEBUG, "Cleared all to_send packets of client %d", sock);
}

bool nets_fetch_clients(net_t *net)
{
    net_connection_t *connection = NULL;
    int sock = -1;

    if (!net)
        return FALSE_NLOG(net, ERROR, "Couldn't fetch clients");
    if (!net_sock_can_read(net->sock, SELECT_TIMEOUT_MS))
        return true;
    sock = accept(net->sock, NULL, NULL);
    if (sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to accept client");
    connection = list_add(&net->server.clients, alloc_connection);
    if (!connection) {
        close(sock);
        return FALSE_NLOG(net, ERROR, "Failed to add client to list");
    }
    connection->sock = sock;
    return TRUE_NLOG(net, DEBUG, "Successfully fetched client %d", sock);
}
