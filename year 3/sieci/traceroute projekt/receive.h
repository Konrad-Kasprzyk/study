//Konrad Kasprzyk
//299243


#ifndef RECEIVE_H_INCLUDED
#define RECEIVE_H_INCLUDED

struct rec_data receive(int sockfd, unsigned short id_num, short seq_nums[]);

struct rec_data{
	char* ip;
	long ms;
};

#endif // RECEIVE_H_INCLUDED