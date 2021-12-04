#include "nanoshell.h"

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
