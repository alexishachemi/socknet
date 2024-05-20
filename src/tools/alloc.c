/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** allocators
*/

#include <stdlib.h>
#include "socknet_dev.h"

void *alloc_connection(void)
{
    return malloc(sizeof(net_connection_t));
}

void *alloc_transfer(void)
{
    return malloc(sizeof(net_transfer_t));
}

void free_transfer(void *t)
{
    net_transfer_t *transfer = t;

    if (!transfer)
        return;
    if (transfer->packet.data)
        free(transfer->packet.data);
    free(transfer);
}

void free_connection(void *c)
{
    net_connection_t *connection = c;

    if (!connection)
        return;
    if (connection->sock >= 0)
        close(connection->sock);
    free(connection);
}
