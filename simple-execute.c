#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int count_pipe(charr ** args, int argc)
{
	int count=0;
	for(int i = 0; i < argc; i++)
	{
		if(args[i]=="|")
		{
			count+=1;
		}
	}
	return count;

}
int shell_execute(char ** args, int argc)
{
	int child_pid, wait_return, status;

	if ( strcmp(args[0], "EXIT") == 0 )
		return -1; 
	
	if( (child_pid = fork()) < 0 ){
		printf("fork() error \n");
	}else if (child_pid == 0 ){
		if ( execvp(args[0], args) < 0){ 
			printf("execvp() error \n");
			exit(-1);
		}
	}else{
		if ( (wait_return = wait(&status) ) < 0 )
			printf("wait() error \n"); 
	}
			
	return 0;

}
