//Konrad Kasprzyk
//299243

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <assert.h>

u_int16_t compute_icmp_checksum (const void *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}

void send2(int sockfd, char* ip, unsigned short id_num, short seq_nums[]){

    struct sockaddr_in recipient;
    bzero (&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    if(inet_pton(AF_INET, ip, &recipient.sin_addr) < 0){
        fprintf(stderr, "inet_pton error: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
	}

    struct icmp header;
    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = htons(id_num);

    for(int i=0; i<3; i++){
        header.icmp_hun.ih_idseq.icd_seq = htons(seq_nums[i]);
        header.icmp_cksum = 0;
        header.icmp_cksum = compute_icmp_checksum (
        (u_int16_t*)&header, sizeof(header));
        ssize_t bytes_sent = sendto (
            sockfd,
            &header,
            sizeof(header),
            0,
            (struct sockaddr*)&recipient,
            sizeof(recipient)
        );
        if(bytes_sent < 0){
            fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
            exit(EXIT_FAILURE);
        }
    }
}
