/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** server_status
*/

#include "socknet_dev.h"

bool nets_has_incoming(net_t *net)
{
    return net && !list_empty(&net->server.incoming);
}

bool nets_has_outgoing(net_t *net)
{
    return net && !list_empty(&net->server.outgoing);
}
