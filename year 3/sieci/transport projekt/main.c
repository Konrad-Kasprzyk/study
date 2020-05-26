//Konrad Kasprzyk
//299243

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include "check_data.h"
#include "receive.h"
#include "pool_manager.h"
#include "send.h"


int main(int argc, char **argv)
{
	check_arg(argc, argv);
	char ip[20];
	strcpy(ip, argv[1]);
	unsigned short port = atoi(argv[2]);
	int size = atoi(argv[4]);

	FILE *file = fopen(argv[3], "wb");
	if (!file){
		fprintf(stderr, "fopen error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}

	struct sockaddr_in server_address;
	bzero (&server_address, sizeof(server_address));
	server_address.sin_family      = AF_INET;
	server_address.sin_port        = htons(port);
	inet_pton(AF_INET, ip, &server_address.sin_addr);
	socklen_t server_address_len = sizeof(server_address);

	int send_pool_interval = 100000;
	struct pool_pointers pool_ptr = init_pool(1000, size, send_pool_interval);
	struct rec_data datagram;
	int bytes_written = 0;
	int ready;
	int progress = 0;
	int new_progress;
	
	fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv; tv.tv_sec = 0; tv.tv_usec = send_pool_interval;
	send_datagrams(sockfd, &server_address, server_address_len, pool_ptr.head, send_pool_interval, send_pool_interval);

	while(bytes_written < size)
	{
		ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);
        if (ready < 0)
		{
			fprintf(stderr, "select error: %s\n", strerror(errno)); 
            exit(EXIT_FAILURE);
		}
        if(ready==0)
		{
			send_datagrams(sockfd, &server_address, server_address_len, pool_ptr.head, send_pool_interval, send_pool_interval);
			bytes_written = write_to_file(&pool_ptr, bytes_written, size, file);
		}
		else
		{
			receive(sockfd, &datagram);
			if (!check_and_prepare_datagram(&datagram, ip, port))
			{
				continue;
			}				
			insert_to_pool(pool_ptr.head, &datagram);
			bytes_written = write_to_file(&pool_ptr, bytes_written, size, file);
			send_datagrams(sockfd, &server_address, server_address_len, pool_ptr.head, send_pool_interval - tv.tv_usec, send_pool_interval);
		}
		FD_ZERO (&descriptors);
    	FD_SET (sockfd, &descriptors);
		tv.tv_sec = 0; tv.tv_usec = send_pool_interval;
		new_progress = (bytes_written*100)/size;
		if(progress != new_progress)
		{
			printf("%d%% done\n", new_progress);
			progress = new_progress;
		}
	}

	if (fclose(file) < 0) {
		fprintf(stderr, "fclose error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	if (close(sockfd) < 0) {
		fprintf(stderr, "close error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	return EXIT_SUCCESS;
}