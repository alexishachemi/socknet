/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** socket utils
*/

#include "socknet_dev.h"

int nets_get_fd_set(net_t *net, fd_set *set)
{
    net_connection_t *connection = NULL;
    int max = 0;

    if (!net || !set)
        return -1;
    FD_ZERO(set);
    FD_SET(net->sock, set);
    max = net->sock;
    for (node_t *n = net->server.clients.head; n; n = n->next) {
        connection = n->data;
        FD_SET(connection->sock, set);
        if (connection->sock > max)
            max = connection->sock;
    }
    return max;
}

int net_open_socket(port_t port)
{
    struct sockaddr_in saddr = {0};
    int sock = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        return -1;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr*) &saddr, sizeof(saddr))) {
        close(sock);
        return -1;
    }
    return sock;
}
