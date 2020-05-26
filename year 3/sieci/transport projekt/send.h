//Konrad Kasprzyk
//299243

#ifndef SEND_H_INCLUDED
#define SEND_H_INCLUDED

#include <arpa/inet.h>

void send_datagrams(int sockfd, struct sockaddr_in *server_address, socklen_t server_address_len, struct pool_data* head, long past_time, long interval);


#endif // SEND_H_INCLUDED