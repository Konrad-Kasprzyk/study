//Konrad Kasprzyk
//299243

#ifndef POOL_MANAGER_H_INCLUDED
#define POOL_MANAGER_H_INCLUDED

struct rec_data{
	int start;
	unsigned int length;
	char ip[20];
	unsigned short port;
	int data_prefix;
	char data[1100];
};

struct pool_data{
	bool ready;
	long time_to_send;
	int start;
	unsigned int length;
	struct pool_data *next;
	char data[1000];
};

struct pool_pointers{
	struct pool_data *head;
	struct pool_data *tail;
};

struct pool_pointers init_pool(int pool_size, int file_size, long interval);
int write_to_file(struct pool_pointers* pool_ptr, int bytes_written_to_file, int file_size, FILE *file);
void insert_to_pool(struct pool_data* head, struct rec_data* rec_data);

#endif // POOL_MANAGER_H_INCLUDED