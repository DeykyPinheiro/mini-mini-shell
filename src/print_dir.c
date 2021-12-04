#include "nanoshell.h"

// funcao que pega o diretorio atual
void	printDir()
{
	char cwd[1024]; //currente work dir
	getcwd(cwd, sizeof(cwd));
	printf("\nDir: %s", cwd);
}
