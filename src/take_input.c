#include "nanoshell.h"

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
