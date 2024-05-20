/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** client initialization
*/

#include "socknet_dev.h"

static void init_lists(net_t *net)
{
    list_init(&net->to_recv);
    list_init(&net->to_send);
}

bool netc_init(net_t *net, port_t port, const char *log_path)
{
    if (!net || !logger_init(&net->logger, log_path, true))
        return false;
    net->sock = net_open_socket(port);
    if (net->sock == -1) {
        NLOG(net, CRITICAL, "Failed to open socket");
        logger_deinit(&net->logger);
        return false;
    }
    net->client.is_connected = false;
    net->type = NET_CLIENT;
    init_lists(net);
    return TRUE_NLOG(net, INFO, "Client started on port %d", port);
}
