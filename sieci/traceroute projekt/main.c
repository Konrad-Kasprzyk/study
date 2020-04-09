//Konrad Kasprzyk
//299243

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <stdbool.h>
#include "send.h"
#include "receive.h"

bool valid_digit(char *ip_str) 
{ 
    while (*ip_str) { 
        if (*ip_str >= '0' && *ip_str <= '9') 
            ++ip_str; 
        else
            return false; 
    } 
    return true; 
} 
  
/* return true if IP string is valid, else return false */
bool is_valid_ip(char *ip_str) 
{ 
    int num, dots = 0; 
    char *ptr; 
  
    if (ip_str == NULL) 
        return false; 
  
    ptr = strtok(ip_str, "."); 
  
    if (ptr == NULL) 
        return false; 
  
    while (ptr) { 
  
        /* after parsing string, it must contain only digits */
        if (!valid_digit(ptr)) 
            return false; 
  
        num = atoi(ptr); 
  
        /* check for valid IP */
        if (num >= 0 && num <= 255) { 
            /* parse remaining string */
            ptr = strtok(NULL, "."); 
            if (ptr != NULL) 
                ++dots; 
        } else
            return false; 
    } 
  
    /* valid IP string must contain 3 dots */
    if (dots != 3) 
        return false; 
    return true; 
} 

int main(int argc, char **argv)
{
	if(argc==1){
		fprintf(stderr, "No arguments. Please pass ip.\n"); 
		return EXIT_FAILURE;
	}
	if(argc>2){
		fprintf(stderr, "Too many arguments. Please pass one ip.\n"); 
		return EXIT_FAILURE;
	}

	char final_ip[20];
	strcpy(final_ip, argv[1]);

	if(!is_valid_ip(argv[1])){
		fprintf(stderr, "Argument is not proper ip. Please pass proper ip.\n"); 
		return EXIT_FAILURE;
	}

	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		fprintf(stderr, "socket error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	
	
	struct rec_data rec_data;
	unsigned short pid = getpid();
	short seq_num = 0;
	short seq_nums[3];
	int ttl = 0;
	while(++ttl <= 30){
		seq_nums[0] = seq_num++;
		seq_nums[1] = seq_num++;
		seq_nums[2] = seq_num++;
		if(setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) < 0){
			fprintf(stderr, "setsockopt error: %s\n", strerror(errno)); 
			return EXIT_FAILURE;
		}
		send2(sockfd, final_ip, pid, seq_nums);
		rec_data = receive(sockfd, pid, seq_nums);
		if(rec_data.ms == -1)
			printf("*\n");
		else if(rec_data.ms == 0)
			printf("%s ???\n",rec_data.ip);
		else
			printf("%s %lums\n", rec_data.ip, rec_data.ms);
		if(strcmp(final_ip, rec_data.ip) == 0)
			break;
	}

	if (close(sockfd) < 0) {
		fprintf(stderr, "close error: %s\n", strerror(errno)); 
		return EXIT_FAILURE;
	}	

	return EXIT_SUCCESS;
}