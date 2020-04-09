#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/csapp.h"
#include "include/pipeio.h"


int main()
{
	extern char **environ;
	printf("\n");

	pipe_t pipe = MakePipe();

	if (fork() == 0){
		printf("Hello World from child \n");
		char *temp[] = {"/bin/echo","siemanko",NULL};
		int ret;

		CloseReadEnd(pipe);
		dup2(pipe.write,STDOUT_FILENO);
		//CloseWriteEnd(pipe);

		ret = execve(temp[0], temp, environ);
		printf("execve return = %d \n", ret);
	}else
	{ /*
		CloseWriteEnd(pipe);
		char line[10];
		int n = read(pipe.read, line, 10);
		printf("Hello World from parent, message: %s \n", line);
		*/
		int b;
		CloseWriteEnd(pipe);
		dup2(pipe.read,STDIN_FILENO);
		//CloseReadEnd(pipe);

		char *temp[] = {"/bin/cat",NULL,NULL};
		int ret;
		printf("Hello World from parent before execve \n");
		ret = execve(temp[0], temp, environ);
		printf("execve return = %d \n", ret);
	}
	
    

    return 0;
}
