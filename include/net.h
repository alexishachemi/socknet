/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** Main header
*/

#pragma once

#include <netinet/in.h>
#include <linked.h>
#include <clogger.h>

#define DEFAULT_QUEUE_SIZE 10
#define SELECT_TIMEOUT_MS 100
#define RESPONSE_TIMEOUT_MS 5000
#define MAX_PACKET_SIZE 1024

typedef unsigned int port_t;

typedef enum {
    NET_SERVER,
    NET_CLIENT
} net_type_t;

typedef enum {
    NET_ERROR,
    NET_OK,
    NET_DISCONNECT
} net_status_t;

//////////////////////////////////////////////////////////////// Main Module //

typedef struct {
    list_t incoming;
    list_t outgoing;
    list_t clients;
} net_server_t;

typedef struct {
    bool is_connected;
} net_client_t;

typedef struct {
    int socket;
    net_type_t type;
    list_t to_send;
    list_t to_recv;
    logger_t logger;
    union {
        net_server_t server;
        net_client_t client;
    };
} net_t;

typedef struct {
    int sock;
} net_connection_t;

//////////////////////////////////////////////////////////////////// Packets //

typedef struct {
    net_status_t status;
    unsigned int data_size;
} net_header_t;

typedef struct {
    net_header_t header;
    void *data;
} net_packet_t;

typedef struct {
    int socket;
    unsigned int data_size;
    void *data;
} net_packet_info_t;

///////////////////////////////////////////////////////////////////// Common //

bool net_update(net_t *net);
void net_deinit(net_t *net);

bool net_will_send(net_t *net);
bool net_has_received(net_t *net);
bool net_is_busy(net_t *net);

////////////////////////////////////////////////////////////// Server (nets) //

bool nets_init(net_t *net, port_t port, size_t queue_size);

unsigned int nets_recv(net_t *net, net_connection_t *c_buf, void *buf);
bool nets_send(net_t *net, int sock, const void *data, unsigned int n);

bool nets_accept_incoming(net_t *net, net_connection_t *c_buf);
bool nets_accept_outgoing(net_t *net, net_connection_t *c_buf);
bool nets_kick(net_t *net, int sock);

////////////////////////////////////////////////////////////// Client (netc) //

bool netc_init(net_t *net, port_t port);

bool netc_recv(net_t *net, void *buf);
bool netc_send(net_t *net, void *data, unsigned int n);

bool netc_connect(net_t *net, const char *host, port_t port);
bool netc_disconnect(net_t *net);
