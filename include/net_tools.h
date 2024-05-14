/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** library utils functions
*/

#pragma once

#include <sys/select.h>
#include "net.h"

bool send_packet(int socket, net_packet_t *packet);

bool netc_fetch(net_t *net);
bool nets_fetch(net_t *net);
bool nets_fetch_clients(net_t *net);
bool net_send_queued(net_t *net);

net_status_t net_await_response(net_t *net);
bool net_send_response(net_t *net, int socket, net_status_t status);

int nets_get_fd_set(list_t *clients, fd_set *set);

int open_socket(port_t port, size_t queue_size);
void *alloc_connection(void);
void *alloc_packet_info(void);
