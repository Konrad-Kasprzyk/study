//Konrad Kasprzyk
//299243

#ifndef CHECK_DATA_H_INCLUDED
#define CHECK_DATA_H_INCLUDED

#include "pool_manager.h"

void check_arg(int argc, char **argv);
bool check_and_prepare_datagram(struct rec_data *received, char ip[], unsigned short port);

#endif // CHECK_DATA_H_INCLUDED