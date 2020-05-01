//Konrad Kasprzyk
//299243

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <string.h>
#include "pool_manager.h"


void send_datagrams(int sockfd, struct sockaddr_in *server_address, socklen_t server_address_len, struct pool_data* head){
	int sent = 0;
	char message[30];
	struct pool_data* curr = head;
	do{
		if(curr->ready){
			curr = curr->next;
			continue;
		}	
		sprintf(message, "GET %d %d\n", curr->start, curr->length);
		ssize_t message_len = strlen(message);
		if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) server_address, server_address_len) != message_len) {
			fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
			exit(EXIT_FAILURE);	
		}	
		curr = curr->next;
		sent++;
	}while(curr != head);
	


/*	POTEM USTAL ILE NARAZ WYSYŁAĆ WIADOMOŚCI ITD.

    char* message = "GET 0 1000\n";
	ssize_t message_len = strlen(message);
	if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) server_address, server_address_len) != message_len) {
		fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
		exit(EXIT_FAILURE);		
	}
	*/

}