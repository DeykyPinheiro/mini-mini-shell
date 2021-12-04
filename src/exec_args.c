#include "nanoshell.h"

// funcao onde o comando do sistema é executado
void execArgs(char **parsed)
{
	//forcando
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("falha no fork\n");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nnão executou o comando");
		}
		exit(0);
	}
	else
	{
		// esperando o filho terminar
		wait(NULL);
		return ;
	}
}
