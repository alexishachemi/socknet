/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** list state functions
*/

#include "socknet_dev.h"

bool net_has_to_send(net_t *net)
{
    return net && !list_empty(&net->to_send);
}

bool net_has_to_recv(net_t *net)
{
    return net && !list_empty(&net->to_recv);
}

bool nets_has_incoming(net_t *net)
{
    return net && !list_empty(&net->server.incoming);
}

bool nets_has_outgoing(net_t *net)
{
    return net && !list_empty(&net->server.outgoing);
}
