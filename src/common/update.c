/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** update function
*/

#include "socknet_dev.h"

static net_status_t update_server(net_t *net)
{
    (void)net;
    return NET_OK;
}

static net_status_t update_client(net_t *net)
{
    if (!netc_is_connected(net))
        return NET_DISCONNECT;
    return NET_OK;
}

net_status_t net_update(net_t *net)
{
    if (!net)
        return NET_ERROR;
    if (net->type == NET_SERVER)
        return update_server(net);
    else if (net->type == NET_CLIENT)
        return update_client(net);
    return NET_ERROR;
}
