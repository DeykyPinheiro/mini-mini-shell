#ifndef NANOSHELL
#define NANOSHELL


// C Program to design a shell in Linux
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

#define clear() printf("\033[H\033[J")

int ownCmdHandler(char** parsed);
int parsePipe(char* str, char** strpiped);
void execArgsPiped(char **parsed, char **parsedpipe);
void execArgs(char **parsed);
void init_shell();
void openHelp();
void	parseSpace(char* str, char** parsed);
void	printDir();
int processString(char* str, char** parsed, char** parsedpipe);
int	takeInput(char *str);







#endif
