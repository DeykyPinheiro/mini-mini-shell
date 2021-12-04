#include "nanoshell.h"

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
