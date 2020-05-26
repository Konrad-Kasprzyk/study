//Konrad Kasprzyk
//299243

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "check_data.h"
#include "pool_manager.h"

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

void check_arg(int argc, char **argv){

    if(argc!=5){
		fprintf(stderr, "Error parsing command line arguments.\n"
		"Usage: ./transport ip port output_file bytes\n"); 
		exit(EXIT_FAILURE);
	}

	char ip[20];
	strcpy(ip, argv[1]);

	if(!is_valid_ip(ip)){
		fprintf(stderr, "First argument is not proper ip\n"); 
		exit(EXIT_FAILURE);
	}

	if(!valid_digit(argv[2])){
		fprintf(stderr, "Second argument is not proper port\n"); 
		exit(EXIT_FAILURE);
	}


	if(!valid_digit(argv[4])){
		fprintf(stderr, "Fourth argument is not proper size.\n"); 
		exit(EXIT_FAILURE);
	}

	int size = atoi(argv[4]);

	if(size>10001000){
		fprintf(stderr, "File size is too big. Max size is 10001000 bytes\n"); 
		exit(EXIT_FAILURE);
	}

    if(size<=0){
		fprintf(stderr, "File size must be positive\n"); 
		exit(EXIT_FAILURE);
	}
}

bool check_and_prepare_datagram(struct rec_data *received, char ip[], unsigned short port){
    if(strcmp(received->ip, ip) != 0 || port != received->port)
        return false;

    if(strncmp("DATA ", received->data, 5) != 0)
        return false;

    char *start = received->data + 5;
    int space_idx = 0;
    while(start[space_idx] != ' ')
        space_idx++;
    start[space_idx] = '\0';
    if(!valid_digit(start))
        return false;

    char *length = start + space_idx + 1;
    int endline_idx = 0;
    while(length[endline_idx] != '\n')
        endline_idx++;
    length[endline_idx] = '\0';
    if(!valid_digit(length))
        return false;

    received->start = atoi(start);
    received->length = atoi(length);
    received->data_prefix = space_idx + endline_idx + 7;
    return true;
}