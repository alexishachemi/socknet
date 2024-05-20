/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** initialization functions
*/

#include "socknet_dev.h"

static void deinit_server(net_t *net)
{
    list_clear(&net->server.clients, free_connection);
    list_clear(&net->server.incoming, free_connection);
    list_clear(&net->server.outgoing, free_connection);
    close(net->sock);
    NLOG(net, INFO, "Deinitialized server");
}

static void deinit_client(net_t *net)
{
    if (netc_is_connected(net))
        netc_disconnect(net);
    NLOG(net, INFO, "Deinitialized client");
}

void net_deinit(net_t *net)
{
    if (!net)
        return;
    if (net->type == NET_SERVER)
        deinit_server(net);
    else if (net->type == NET_CLIENT)
        deinit_client(net);
    else
        NLOG(net, CRITICAL, "Deinit error, bad net type");
    list_clear(&net->to_recv, free_transfer);
    list_clear(&net->to_send, free_transfer);
}
