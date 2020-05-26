//Konrad Kasprzyk
//299243

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "pool_manager.h"
#include "send.h"


void send_datagrams(int sockfd, struct sockaddr_in *server_address, socklen_t server_address_len, struct pool_data* head, long past_time, long interval){
	int sent = 0;
	char message[30];
	struct pool_data* curr = head;
	do{
		if(curr->ready)
		{
			curr = curr->next;
			continue;
		}
		curr->time_to_send -= past_time;
		if(curr->time_to_send <= 0)
		{
			sprintf(message, "GET %d %d\n", curr->start, curr->length);
			ssize_t message_len = strlen(message);
			if (sendto(sockfd, message, message_len, 0, (struct sockaddr*) server_address, server_address_len) != message_len) 
			{
				fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
				exit(EXIT_FAILURE);	
			}
			sent++;
			curr->time_to_send = interval;
		}	
		curr = curr->next;
	}while(curr != head);
}