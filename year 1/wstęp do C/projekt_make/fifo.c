//Konrad Kasprzyk

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "fifo.h"

struct pipes {
    FILE *fifo_in, *fifo_out;
    int isb;
} ;

int fileno(FILE *file);
void pokazBlad(char *komunikat);
static FILE *openOutPipe(char *name);
static FILE *openInPipe(char *name);

void closePipes(PipesPtr pipes)
{
  fclose(pipes->fifo_in);
  fclose(pipes->fifo_out);
  free(pipes);
}

PipesPtr initPipes(int argc,char *argv[])
{
    if (argc < 2 || (argv[1][0] != 'c' && argv[1][0] != 'b') || argv[1][1] != '\0')
    {
        fprintf(stderr,"\nProgram nalezy otworzyc z argumentem b lub c. b= biale pionki, c= czarne pionki\n\n");
	mkfifo("b_do_c",0664);
	mkfifo("c_do_b",0664);
	fprintf(stderr,"Utworzono pliki FIFO b_do_c oraz c_do_b \n");
        return NULL;
    }
    PipesPtr pipes=(PipesPtr)malloc(sizeof(struct pipes));
    if (pipes == NULL) {
        fprintf(stderr,"Memory allocation error\n");
    } else {
        pipes->isb=(argv[1][0] == 'b');
        pipes->fifo_out = openOutPipe(pipes->isb ? "b_do_c" : "c_do_b");
        pipes->fifo_in = openInPipe(pipes->isb ? "c_do_b" : "b_do_c");
    }
    return pipes;
}

static FILE *openOutPipe(char *name) {
    FILE *pipe = fopen(name, "w+");
    if (pipe == NULL)
    {
        pokazBlad("Error in creating output pipe");
        exit(-1);
    }
    return pipe;
}

static FILE *openInPipe(char *name){
    FILE *pipe = fopen(name, "r+");
    if (pipe == NULL)
    {
        pokazBlad("Error in creating input pipe");
        exit(-1);
    }
    int flags, fd;
    fd = fileno(pipe);
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return pipe;
}

void sendStringToPipe(PipesPtr pipes, const char *data)
{
    int result = fprintf(pipes->fifo_out,"%s",data);
    fflush(pipes->fifo_out);
    if (result == 0)
        pokazBlad("Failed to send data");
}

bool getStringFromPipe(PipesPtr pipes, char *buffer, size_t size)
{
    char *result = fgets(buffer,size,pipes->fifo_in);
    fflush(pipes->fifo_in);
    //if (result == NULL) pokazBlad("Failed to read data");
    return result != NULL;
}
