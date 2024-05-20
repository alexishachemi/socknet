/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** server client handling
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

bool nets_accept_incoming(net_t *net, net_connection_t *c_buf)
{
    net_connection_t *connection = NULL;

    if (!net || !c_buf)
        return FALSE_NLOG(net, ERROR,
            "Failed to accept incoming connection, bad args");
    if (!nets_has_incoming(net))
        return FALSE_NLOG(net, DEBUG, "No incoming connection to accept");
    if (!list_move(&net->server.incoming, 0, &net->server.clients))
        return FALSE_NLOG(net, ERROR, "Failed to accept incoming connection");
    connection = list_at(&net->server.clients, -1);
    memcpy(c_buf, connection, sizeof(net_connection_t));
    return TRUE_NLOG(net, INFO, "Accepted incoming client %d",
        connection->sock);
}

bool nets_accept_outgoing(net_t *net, net_connection_t *c_buf)
{
    net_connection_t *connection = NULL;

    if (!net || !c_buf || !nets_has_outgoing(net))
        return FALSE_NLOG(net, ERROR,
            "Failed to accept outgoing connection");
    connection = list_pop(&net->server.outgoing, 0);
    memcpy(c_buf, connection, sizeof(net_connection_t));
    free(connection);
    return TRUE_NLOG(net, INFO, "Accepted outgoing client %d",
        connection->sock);
}

bool nets_kick(net_t *net, int sock)
{
    bool found = false;
    net_connection_t *connection = NULL;
    size_t i = 0;

    if (!net || sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to kick client %d", sock);
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        connection = n->data;
        if (connection->sock == sock) {
            found = true;
            break;
        }
        i++;
    }
    if (!found
        || !list_move(&net->server.clients, i, &net->server.outgoing))
        return FALSE_NLOG(net, ERROR, "Failed to kick client %d", sock);
    nets_clear_sock_transfer(net, connection->sock);
    return TRUE_NLOG(net, INFO, "Kicked client %d", sock);
}
