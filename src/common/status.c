/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** status function
*/

#include "socknet_dev.h"

bool net_is_busy(net_t *net)
{
    return net_will_send(net) || net_will_recv(net);
}

bool net_will_send(net_t *net)
{
    return net && !list_empty(&net->to_send);
}

bool net_will_recv(net_t *net)
{
    return net && !list_empty(&net->to_recv);
}

bool net_will_send_to(net_t *net, int sock)
{
    return net && list_get_if(&net->to_send, list_int_eq, &sock);
}
