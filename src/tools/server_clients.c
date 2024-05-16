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
