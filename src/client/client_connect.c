/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** client connection functions
*/

#include <arpa/inet.h>
#include "socknet_dev.h"

bool netc_connect(net_t *net, const char *host, port_t port)
{
    struct sockaddr_in addr = {0};
    socklen_t addr_len = sizeof(addr);

    if (!net || !host || net->type != NET_CLIENT)
        return FALSE_NLOG(net, ERROR, "Failed to connect");
    if (net->client.is_connected)
        return FALSE_NLOG(net, ERROR,
            "Failed to connect, already connected");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_aton(host, &addr.sin_addr) != 1)
        return FALSE_NLOG(net, ERROR, "Failed to connect, bad host");
    if (connect(net->sock, (struct sockaddr *)&addr, addr_len) == -1)
        return FALSE_NLOG(net, ERROR, "Failed to connect, bad connect");
    net->client.is_connected = true;
    return TRUE_NLOG(net, INFO, "Connected to %s:%d", host, port);
}

bool netc_disconnect(net_t *net)
{
    if (!net || net->type != NET_CLIENT)
        return FALSE_NLOG(net, ERROR, "Failed to disconnect");
    close(net->sock);
    net->sock = -1;
    net->client.is_connected = false;
    return TRUE_NLOG(net, INFO, "Disconnected");
}

bool netc_is_connected(net_t *net)
{
    return net && net->type == NET_CLIENT && net->client.is_connected;
}
