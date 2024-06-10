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

#define NRESP ((net_header_t){.type = NET_RESPONSE, .data_size = 0})

// transfer handling

bool net_send_packet(net_t *net, const net_transfer_t *transfer);
bool net_recv_packet(net_t *net, int sock);
bool net_fetch_packets(net_t *net);
bool net_send_queued(net_t *net);

// response handling

bool net_send_response(net_t *net, int sock);
bool net_await_response(net_t *net, int sock);

// client handling

net_connection_t *nets_get_client(net_t *net, int sock);
void nets_clear_sock_transfer(net_t *net, int sock);
bool nets_fetch_clients(net_t *net);

// socket utils

int nets_get_fd_set(net_t *net, fd_set *set);
int net_open_socket(port_t port);
bool net_sock_can_write(int sock, int timeout_ms);
bool net_sock_can_read(int sock, int timeout_ms);

// memory management

void *alloc_connection(void);
void *alloc_transfer(void);

void free_transfer(void *t);
void free_connection(void *c);
