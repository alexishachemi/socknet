/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** response handling
*/

#include "socknet_dev.h"

static bool handle_send_fail(net_t *net, int sock)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "No response from socket %d, kicking client...", sock);
        nets_kick(net, sock);
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL, "No response from server, disconnecting...");
        netc_disconnect(net);
    }
    return false;
}

static int get_timeout_ms(net_t *net)
{
    if (net->type == NET_SERVER)
        return CLIENT_RESPONSE_TIMEOUT;
    return SERVER_RESPONSE_TIMEOUT;
}

bool net_send_response(net_t *net, int sock)
{
    int status = 0;
    net_header_t response = NRESP;

    if (!net || sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to send response, bad args");
    if (!net_sock_can_write(sock, get_timeout_ms(net)))
        return FALSE_NLOG(net, ERROR, "Cannot write to socket %d", sock);
    status = send(sock, &response, sizeof(net_header_t), MSG_NOSIGNAL);
    if (status != sizeof(net_header_t))
        return handle_send_fail(net, sock);
    return TRUE_NLOG(net, DEBUG, "Successfully sent response to socket %d",
        sock);
}

static bool handle_recv_fail(net_t *net, int sock)
{
    if (net->type == NET_SERVER) {
        NLOG(net, CRITICAL,
            "Failed to get response from socket %d, kicking client...", sock);
        nets_kick(net, sock);
    } else if (net->type == NET_CLIENT) {
        NLOG(net, CRITICAL,
            "Failed to get response from server, disconnecting...");
        netc_disconnect(net);
    }
    return false;
}

bool net_await_response(net_t *net, int sock)
{
    net_header_t response = {0};
    int status = 0;

    if (!net || sock < 0)
        return FALSE_NLOG(net, ERROR, "Failed to await response, bad args");
    if (!net_sock_can_read(sock, get_timeout_ms(net)))
        return FALSE_NLOG(net, ERROR, "Cannot read from socket %d", sock);
    status = recv(sock, &response, sizeof(net_header_t), MSG_NOSIGNAL);
    if (status != sizeof(net_header_t) || response.type != NET_RESPONSE)
        return handle_recv_fail(net, sock);
    return TRUE_NLOG(net, DEBUG,
        "Successfully received response from socket %d", sock);
}
