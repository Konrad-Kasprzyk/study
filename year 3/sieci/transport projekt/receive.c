//Konrad Kasprzyk
//299243


#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <string.h>
#include "receive.h"
#include "pool_manager.h"


void receive(int sockfd, struct rec_data* received){
    struct sockaddr_in sender;	
	socklen_t sender_len = sizeof(sender);
	int bytes_received = recvfrom(sockfd, received->data, 1100,  
                0, (struct sockaddr *) &sender, 
                &sender_len);
	
    char sender_ip[20];
    
    // convert IPv4 and IPv6 addresses from binary to text form
	if(inet_ntop(AF_INET, &(sender.sin_addr), sender_ip, sizeof(sender_ip)) == NULL){
        fprintf(stderr, "inet_ntop: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    }

    unsigned int sender_port = ntohs(sender.sin_port);
    strcpy(received->ip, sender_ip);
    received->port = sender_port;
}
