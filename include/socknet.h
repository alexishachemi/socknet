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

#define QUEUE_SIZE 10
#define SELECT_TIMEOUT_MS 100
#define CLIENT_RESPONSE_TIMEOUT 30000
#define SERVER_RESPONSE_TIMEOUT 30000
#define MAX_PACKET_SIZE 1024

typedef unsigned int port_t;

typedef enum {
    NET_SERVER,
    NET_CLIENT
} net_type_t;

typedef enum {
    NET_DATA,
    NET_RESPONSE
} net_packet_type_t;

typedef enum {
    NET_OK,
    NET_ERROR,
    NET_DISCONNECT
} net_status_t;

//////////////////////////////////////////////////////////////// Main Module //

typedef struct {
    list_t incoming; // connection_t
    list_t outgoing; // connection_t
    list_t clients; // connection_t
} net_server_t;

typedef struct {
    bool is_connected;
} net_client_t;

typedef struct {
    int sock;
    net_type_t type;
    list_t to_send; // transfer_t
    list_t to_recv; // transfer_t
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
    net_packet_type_t type;
    unsigned int data_size;
} net_header_t;

typedef struct {
    net_header_t header;
    void *data;
} net_packet_t;

typedef struct {
    net_connection_t connection;
    net_packet_t packet;
} net_transfer_t;

///////////////////////////////////////////////////////////////////// Common //

/// @brief Deinitializes a network module of any type.
/// @param net the network module
void net_deinit(net_t *net);

net_status_t net_update(net_t *net);

/// @brief Checks if a network module has packets to send of to revieve
/// @param net the network module
/// @return true if the network module has packets to send or to recieve,
/// false otherwise
bool net_is_busy(net_t *net);

/// @brief Sets the log level of the network module
/// @param net the network module to set the log level of
/// @param lvl the log level to set
/// @return true if the log level was set, false otherwise
bool net_set_log_level(net_t *net, log_level_t lvl);

////////////////////////////////////////////////////////////// Server (nets) //

/// @brief Initializes a network module as a server
/// @param net the server module to initialize
/// @param port the port to listen on, 0 to let the kernel choose
/// @param log_path the path to the log file, NULL to disable logging
/// @return true if the initialization was successful, false otherwise
bool nets_init(net_t *net, port_t port, const char *log_path);

/// @brief Queues a packet to be sent. `data` is copied to an internal list.
/// @param net the server module
/// @param sock the socket to send the packet to
/// @param data the data to send
/// @param n the size of the data, must be less of equal to MAX_PACKET_SIZE
/// @return true if the packet was queued, false otherwise
bool nets_send(net_t *net, int sock, const void *data, unsigned int n);

/// @brief Dequeues a packet from the recieved packets.
/// The caller gains ownership of all allocated memory contained in `t_buf`
/// @param net the server module
/// @param t_buf the transfer buffer to store the transfer info
/// @return true if a packet was recieved, false otherwise
bool nets_recv(net_t *net, net_transfer_t *t_buf);

/// @brief "Accepts" incoming connections. This does not call the
/// `accept` syscall. It moves already accepted connections from the internal
/// incoming list to the connected clients list. One example use of this
/// function is sending a welcome message when a user connects. Note that
/// even if you do not plan to have such behaviour in your program, the
/// function must be called either way.
/// @param net the server module
/// @param c_buf the connection buffer to store the connection info
/// @return true if an incoming connection was accepted, false otherwise
bool nets_accept_incoming(net_t *net, net_connection_t *c_buf);

/// @brief "Accepts" outgoing connections. Outgoing connection are clients that
/// have been disconnected and are now ready to be removed from the outgoing
/// list.
/// @param net the server module
/// @param c_buf the connection buffer to store the connection info
/// @return true if an outgoing connection was accepted, false otherwise
bool nets_accept_outgoing(net_t *net, net_connection_t *c_buf);

/// @brief Kicks a client from the server. This moves the client from the
/// connected clients list to the outgoing list.
/// @param net the server module
/// @param sock the socket of the client to kick
/// @return true if the client was kicked, false otherwise
bool nets_kick(net_t *net, int sock);

////////////////////////////////////////////////////////////// Client (netc) //

/// @brief Initializes a network module as a client
/// @param net the client module to initialize
/// @param port the port to connect to, 0 to let the kernel choose
/// @param log_path the path to the log file, NULL to disable logging
/// @return true if the initialization was successful, false otherwise
bool netc_init(net_t *net, port_t port, const char *log_path);

/// @brief Queues a packet to be sent to the server.
/// `data` is copied to an internal list.
/// @param net the client module
/// @param data the data to send
/// @param n the size of the data, must be less of equal to MAX_PACKET_SIZE
/// @return true if the packet was sent, false otherwise
bool netc_send(net_t *net, const void *data, unsigned int n);

/// @brief Dequeues a packet from the recieved packets.
/// The caller gains ownership of all allocated memory contained in `t_buf`
/// @param net the client module
/// @param t_buf the transfer buffer to store the transfer info
/// @return true if a packet was recieved, false otherwise
bool netc_recv(net_t *net, net_transfer_t *t_buf);

/// @brief Connects a client to a server
/// @param net the client module
/// @param host string representation of an ipv4 host address
/// (i.e. 127.0.0.1)
/// @param port port to open the connection to (i.e. server's port)
/// @return true if the connection was successful, false otherwise
bool netc_connect(net_t *net, const char *host, port_t port);

/// @brief Disconnects a client from a server
/// @param net the client module
/// @return true if the disconnection was successful, false otherwise
bool netc_disconnect(net_t *net);

/// @brief Checks if a client is connected to a server
/// @param net the client module
/// @return true if the client is connected, false otherwise
bool netc_is_connected(net_t *net);
