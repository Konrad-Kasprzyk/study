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


bool is_packet_good(struct icmp* icmp_header, unsigned short id_num, short seq_nums[]){
    // Normal echo response or ttl exceeded
    if (icmp_header -> icmp_type != 0  && icmp_header -> icmp_type != 11)
        return false;

    // ttl exceeded, take second icmp packet in response, this is a copy of what we sent
    if(icmp_header -> icmp_type == 11){
        struct ip* second_ip_header = (struct ip*) ((void*)icmp_header + (ssize_t)sizeof(struct icmphdr));
        ssize_t second_ip_header_len = 4 * second_ip_header->ip_hl;
        icmp_header = (struct icmp*) ((void*)second_ip_header  + second_ip_header_len);
    }

    if(ntohs(icmp_header -> icmp_hun.ih_idseq.icd_id)!= id_num)
        return false;

    short seq_num = ntohs(icmp_header -> icmp_hun.ih_idseq.icd_seq);
    bool good_packet = false;
    for(int i=0; i< 3; i++)
        if(seq_num == seq_nums[i]){
            good_packet = true;
            break;
        }
    if(!good_packet)
        return false;
    return true;
}

struct rec_data prepare_ret_data(char rec_ips[3][20], unsigned long ms[3]){
    char ips_to_ret[60];
    bool no_ret_ips = true;
    bool no_avg_ms = false;
    unsigned long average_ms = 0;
    for (int i=0; i<3; i++){
        if(ms[i] == 0)
            no_avg_ms = true;
        else{
            no_ret_ips = false;
            if(i==0)
                strcpy(ips_to_ret, rec_ips[0]);
            else if(i==1){
                if(strcmp(rec_ips[0], rec_ips[1]) != 0){
                    strcat(ips_to_ret, " ");
                    strcat(ips_to_ret, rec_ips[1]);
                }
            }else{
                if(strcmp(rec_ips[0], rec_ips[2]) != 0 || strcmp(rec_ips[1], rec_ips[2]) != 0){
                    strcat(ips_to_ret, " ");
                    strcat(ips_to_ret, rec_ips[2]);
                }
            }     
        }    
        average_ms += ms[i];
    }
    struct rec_data ret = {ips_to_ret, average_ms};
    if(no_ret_ips)
        ret.ms = -1;
    else if(no_avg_ms)
        ret.ms = 0;
    else
        ret.ms /= 3000;
    return ret;
}

struct rec_data receive(int sockfd, unsigned short id_num, short seq_nums[]){
    fd_set descriptors;
    FD_ZERO (&descriptors);
    FD_SET (sockfd, &descriptors);
    struct timeval tv; tv.tv_sec = 1; tv.tv_usec = 0;
    unsigned long ms[3] = {0, 0, 0};
    char rec_ips[3][20] = {"", "", ""};
    int rec_num = 0;
    char sender_ip_str[20];
    while(rec_num < 3){
		struct sockaddr_in sender;	
		socklen_t sender_len = sizeof(sender);
		u_int8_t buffer[IP_MAXPACKET];

		int ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);
        if (ready < 0) {
			fprintf(stderr, "select error: %s\n", strerror(errno)); 
            exit(EXIT_FAILURE);
		}
        if(ready==0)
            break;       
            
		ssize_t packet_len = recvfrom (sockfd, buffer, IP_MAXPACKET, 0, (struct sockaddr*)&sender, &sender_len);
		if (packet_len < 0) {
			fprintf(stderr, "recvfrom error: %s\n", strerror(errno)); 
            exit(EXIT_FAILURE);
		}
			
		// convert IPv4 and IPv6 addresses from binary to text form
		if(inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str)) == NULL){
            fprintf(stderr, "inet_ntop: %s\n", strerror(errno)); 
            exit(EXIT_FAILURE);
        }
        struct ip* ip_header = (struct ip*) buffer;
		ssize_t ip_header_len = 4 * ip_header->ip_hl;
        struct icmp* icmp_header = (struct icmp*) (buffer + ip_header_len);

        if(!is_packet_good(icmp_header, id_num, seq_nums))
            continue;
            
        strcpy(rec_ips[rec_num], sender_ip_str);
        ms[rec_num] = (unsigned long)1000000 - tv.tv_usec;
        rec_num++;
    }
    return prepare_ret_data(rec_ips, ms);
}
