/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** client initialization
*/

#include "socknet_dev.h"

bool netc_init(net_t *net, port_t port, const char *log_path)
{
    if (!net || !logger_init(&net->logger, log_path))
        return false;
    net->sock = open_socket(port);
    if (net->sock == -1) {
        NLOG(net, CRITICAL, "Failed to open socket");
        logger_deinit(&net->logger);
        return false;
    }
    net->type = NET_CLIENT;
    return TRUE_NLOG(net, INFO, "Client started on port %d", port);
}
