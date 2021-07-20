#include <stdio.h>
#include <unistd.h>
#include "Colors.h"
#include "Tools.h"
#include "Functions.h"

void parse(char* input)
{
	int argv = NumberOfWords(input);
	char** args = NULL;
	if(argv > 0)
	{
		args = CutCommand(input, argv);

		if(ComparString("print", args[0]))
		{
			Print(argv, args);
		}
		else if(ComparString("ls", args[0]))
		{
			LS();
		}
		else if(ComparString("cd", args[0]))
		{
			CD(argv, args);
		}
		else if(ComparString("help", args[0]))
		{
			Help(argv, args);
		}
		else if(ComparString("mkdir", args[0]))
		{
			MKDIR(argv, args);
		}
		else if(ComparString("touch", args[0]))
		{
			TOUCH(argv, args);
		}
		else if(ComparString("rm", args[0]))
		{
			if(argv > 1)
			{
				RM(argv, args[1]);
			}
		}
		else if(ComparString("rename", args[0]))
		{
			RENAME(argv, args);
		}
		else
		{
			printf("Unknown command, try help for more information\n");
		}
		Free2DCharArray(args, argv);
	}
}

int main()
{
	char buffer[MAX_INPUT_SIZE];
	char cwd[MAX_PATH_SIZE];
	char* input = "\0";
	char *quit = "q";
	while (!ComparString(input, quit))
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("main: getcwd() error");
			return 1;
		}
		printf(COLOR_RED "Shell" COLOR_RESET ":" COLOR_GREEN "%s" COLOR_RESET "> ", cwd);
		input = fgets(buffer, MAX_INPUT_SIZE, stdin);
		int toVoid = DeleteNewLine(input);
		parse(input);
		while(toVoid == 0)
		{
			input = fgets(buffer, MAX_INPUT_SIZE, stdin);
			toVoid = DeleteNewLine(input);
		}
	}
	return 0;
}