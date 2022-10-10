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
		if(args[i]=='|')
		{
			count+=1;
		}
	}
	return count;

}

char split_pipe(charr ** args, int argc)
{
	char splitted [3][3];
	int number_of_args=0;
	int argu_para=0;
	for(int i = 0 ; i<argc;i++)
	{
		if(argc[i]=='|')
		{
			splitted[number_of_args][argu_para]=NULL;
			number_of_args+=1;
			argu_para=0;
		}
		splitted[number_of_args][argu_para]=args[i];
		argu_para+=1;
	}
	return splitted;
}

int shell_execute(char ** args, int argc)
{	
	int pipe_num = count_pipe(args, argc);
	if(pipe_num=0)
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
	}
	else
	{
		int fd[2];
		int ret;
		char *cmd;
		char *argv[3];

		pipe(fd);

		if((ret=fork())>0)
		{
			close(1);
			dup(fd[1]);
			close(fd[0]);
			close(fd[1]);

			cmd=
		}
	}
			
	return 0;

}
