/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** server initialization
*/

#include "socknet_dev.h"

bool nets_init(net_t *net, port_t port, const char *log_path)
{
    if (!net || !logger_init(&net->logger, log_path))
        return false;
    net->sock = open_socket(port);
    if (net->sock == -1) {
        NLOG(net, CRITICAL, "Failed to open socket");
        logger_deinit(&net->logger);
        return false;
    }
    if (listen(net->sock, QUEUE_SIZE) == -1) {
        NLOG(net, CRITICAL, "Failed to listen on socket");
        logger_deinit(&net->logger);
        close(net->sock);
        return false;
    }
    net->type = NET_SERVER;
    return TRUE_NLOG(net, INFO, "Server started on port %d", port);
}
