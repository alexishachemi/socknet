/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** server initialization
*/

#include "socknet_dev.h"

static void init_lists(net_t *net)
{
    list_init(&net->server.clients);
    list_init(&net->server.incoming);
    list_init(&net->server.outgoing);
    list_init(&net->to_recv);
    list_init(&net->to_send);
}

bool nets_init(net_t *net, port_t port, const char *log_path)
{
    if (!net || !logger_init(&net->logger, log_path, true))
        return false;
    net->sock = net_open_socket(port);
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
    init_lists(net);
    return TRUE_NLOG(net, INFO, "Server started on port %d", port);
}
