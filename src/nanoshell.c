#include "nanoshell.h"

void init_shell()
{
	clear();
	printf("\n\n\n\n******************"
		"************************");
	printf("\n\n\n\t****MY SHELL****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n*******************"
		"***********************");
	char* username = getenv("USER");
	printf("\n\n\nUSER is: @%s", username);
	printf("\n");
	sleep(1);
	clear();
}

// funcao que pega a entrada
int	takeInput(char *str)
{
	char *buf;

	buf = readline("\n>>> "); //esses tres pontos é tipo here_doc
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
	{
		return (1);
	}
}

// funcao que pega o diretorio atual
void	printDir()
{
	char cwd[1024]; //currente work dir
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}

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

void openHelp()
{
	puts("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ Suprotik Dey"
		"\n-Use the shell at your own risk..."
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");

	return;
}

// funcao para executar comandos buitin
int ownCmdHandler(char** parsed)
{
	int NoOfOwnCmds = 4, i, switchOwnArg = 0;
	char* ListOfOwnCmds[NoOfOwnCmds];
	char* username;

	ListOfOwnCmds[0] = "exit";
	ListOfOwnCmds[1] = "cd";
	ListOfOwnCmds[2] = "help";
	ListOfOwnCmds[3] = "hello";

	for (i = 0; i < NoOfOwnCmds; i++) {
		if (strcmp(parsed[0], ListOfOwnCmds[i]) == 0) {
			switchOwnArg = i + 1;
			break;
		}
	}

	switch (switchOwnArg)
	{
	case 1:
		printf("\nGoodbye\n");
		exit(0);
	case 2:
		chdir(parsed[1]);
		return 1;
	case 3:
		openHelp();
		return 1;
	case 4:
		username = getenv("USER");
		printf("\nHello %s.\nMind that this is "
			"not a place to play around."
			"\nUse help to know more..\n",
			username);
		return 1;
	default:
		break;
	}

	return 0;
}

int parsePipe(char* str, char** strpiped)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else {
		return 1;
	}
}


// funcao para parsear os comandos
void	parseSpace(char* str, char** parsed)
{
	int	i;

	for (i = 0; i < MAXLIST; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
			break ;
		if (strlen(parsed[i]) == 0)
			i--;
	}
}

int processString(char* str, char** parsed, char** parsedpipe)
{
	char* strpipe[2];
	int piped = 0;

	piped = parsePipe(str, strpipe);

	if (piped)
	{
		parseSpace(strpipe[0], parsed);
		parseSpace(strpipe[0], parsedpipe);
	}
	else
	{
		parseSpace(str, parsed);
	}

	if (ownCmdHandler(parsed))
		return (0);
	else
		return (1 + piped);
}

int main(void)
{
	char inputString[MAXCOM], *parsedArgs[MAXLIST];
	char* parserdArgsPiped[MAXLIST];
	int execFlag = 0;
	init_shell();

	while (1)
	{
		// mostra alinha do shell
		printDir();
		// pega a saida
		if (takeInput(inputString))
			continue;
		// processo
		execFlag = processString(inputString, parsedArgs, parserdArgsPiped);
		//

		// executa
		if (execFlag == 1)
			execArgs(parsedArgs);

		if (execFlag == 2)
			execArgsPiped(parsedArgs, parserdArgsPiped);
	}
	return (0);
}
