/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** library utils functions
*/

#pragma once

#include <sys/select.h>
#include "socknet.h"

#define NLOG(netptr, lvl, f...) (LOG(&netptr->logger, lvl, f))
#define FALSE_NLOG(netptr, lvl, f...) (LOG_FALSE(&netptr->logger, lvl, f))
#define TRUE_NLOG(netptr, lvl, f...) (LOG_TRUE(&netptr->logger, lvl, f))
#define NULL_NLOG(netptr, lvl, f...) (LOG_NULL(&netptr->logger, lvl, f))

bool net_has_to_send(net_t *net);
bool net_has_to_recv(net_t *net);
bool nets_has_incoming(net_t *net);
bool nets_has_outgoing(net_t *net);

net_connection_t *nets_get_client(net_t *net, int sock);
void nets_clear_sock_transfer(net_t *net, int sock);

// Socket utils

int nets_get_fd_set(net_t *net, fd_set *set);
int open_socket(port_t port);

// Allocators

void *alloc_connection(void);
void *alloc_transfer(void);
void free_transfer(void *t);
void free_connection(void *c);
