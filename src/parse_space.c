#include "nanoshell.h"

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
