#include "nanoshell.h"

// funcao onde os comandos do sistema canalizados são executados
void execArgsPiped(char **parsed, char **parsedpipe)
{
	// 0 é leitura, 1 é escrita
	int pipefd[2];
	pid_t p1, p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nproblema no pipe");
		return ;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nproblema no fork");
		return ;
	}
	if (p1 == 0)
	{
		// filho 1 executando
		// ele só escreve no fim da gravacao
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);

		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nnão pode executar comando 1");
			exit(0);
		}
		else
		{
			p2 = fork();

			if (p2 < 0)
			{
				printf("\nnão pode forkar");
				return ;
			}

			// crianca dois executando
			// ele só le no fim da leitura
			if (p2 == 0)
			{
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);

				if (execvp(parsedpipe[0], parsedpipe) < 0)
				{
					printf("\nnão executa comando 2");
					exit (0);
				}
				else
				{
					// pai esperando os dois filhos
					wait(NULL);
					wait(NULL);
				}
			}

		}
	}
}
