#include <stdio.h>
#include "Tools.h"
#include "Colors.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#ifndef WIN32
#include <sys/types.h>
#endif

void Help(int argv, char **args)
{
    if (argv == 1)
    {
        printf(COLOR_GREEN "help" COLOR_RESET " [command]: print a general help or print a precise help depending the command. e.g. help ls\n");
        printf(COLOR_GREEN "print" COLOR_RESET " [text]: print text depending colors typed. e.g. print -red hello -reset \"   World\"\n");
        printf(COLOR_GREEN "ls" COLOR_RESET ": print all files contained in the current working directory\n");
        printf(COLOR_GREEN "cd" COLOR_RESET " [path]: change current working directory. e.g. \"parent/child1\"\n");
    }
    else if (ComparString("ls", args[1]))
    {
        printf(COLOR_GREEN "ls" COLOR_RESET ":\n print all files contained in the current working directory\n");
    }
    else if (ComparString("cd", args[1]))
    {
        printf(COLOR_GREEN "cd" COLOR_RESET " [path]:\n change current working directory. e.g. \"parent/child1\"\n");
    }
    else if (ComparString("print", args[1]))
    {
        printf(COLOR_GREEN "print" COLOR_RESET " [text]:\n print text depending colors typed. e.g. print -red hello -reset \"   World\"\n");
        printf(" all colors: " COLOR_RED "-red " COLOR_GREEN "-green " COLOR_YELLOW "-yellow " COLOR_BLUE "-blue " COLOR_MAGENTA "-magenta " COLOR_CYAN "-cyan " COLOR_RESET "-reset\n");
    }
    else if (ComparString("help", args[1]))
    {
        printf(COLOR_GREEN "help" COLOR_RESET " [command]: print a general help or print a precise help depending the command. e.g. help ls\n");
    }
    else
    {
        printf("Unknown command, try help for more information\n");
    }
}

void Print(int argv, char **args)
{
    for (int i = 1; i < argv; i++)
    {
        if (ComparString("-red", args[i]))
        {
            printf(COLOR_RED);
        }
        else if (ComparString("-green", args[i]))
        {
            printf(COLOR_GREEN);
        }
        else if (ComparString("-yellow", args[i]))
        {
            printf(COLOR_YELLOW);
        }
        else if (ComparString("-blue", args[i]))
        {
            printf(COLOR_BLUE);
        }
        else if (ComparString("-magenta", args[i]))
        {
            printf(COLOR_MAGENTA);
        }
        else if (ComparString("-cyan", args[i]))
        {
            printf(COLOR_CYAN);
        }
        else if (ComparString("-reset", args[i]))
        {
            printf(COLOR_RESET);
        }
        else
        {
            printf("%s ", args[i]);
        }
    }
    printf("\n");
}

void LS()
{
    char cwd[MAX_PATH_SIZE];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("ls: getcwd() error");
    }
    DIR *dir = NULL;
    dir = opendir(cwd);
    if (dir == NULL)
    {
        perror("ls: Path error");
    }
    struct dirent *allFiles = NULL;
    allFiles = readdir(dir);
    while (allFiles != NULL)
    {
        if (allFiles->d_type == 4)
        {
            printf(COLOR_BLUE);
        }
        else
        {
            printf(COLOR_RESET);
        }
        printf("%s", allFiles->d_name);
        printf(COLOR_RESET " | ");
        allFiles = readdir(dir);
    }
    printf("\n");
    closedir(dir);
}

void CD(int argv, char **args)
{
    if (argv > 1)
    {
        chdir(args[1]);
    }
    else
    {
        chdir("..");
    }
}

//avoid error of called function
extern int mkdir (const char *__path, mode_t __mode);

void MKDIR(int argv, char **args)
{
    if (argv > 1)
    {
        int check;
        check = mkdir(args[1], 0777);
        if (!check)
        {
            printf("Directory created\n");
        }
        else
        {
            printf("Unable to create directory\n");
        }
    }
}

void TOUCH(int argv, char **args)
{
    if (argv > 1)
    {
        if (access(args[1], F_OK))
        {
            FILE *f = NULL;
            f = fopen(args[1], "ab+");
            if (f != NULL)
            {
                printf("File created\n");
                fclose(f);
            }
            else
            {
                printf("Unable to create file\n");
            }
        }
        else
        {
            printf("File already exist\n");
        }
    }
}

void RM(int argv, char *path)
{
    DIR *dir = NULL;
    dir = opendir(path);
    if (dir != NULL)
    {
        struct dirent *allFiles = NULL;
        allFiles = readdir(dir);
        while (allFiles != NULL)
        {
            if (!ComparString(allFiles->d_name, ".") && !ComparString(allFiles->d_name, ".."))
            {
                int length = StringLength(path) + 1 + StringLength(allFiles->d_name) + 1;
                char *concat = malloc(sizeof(char) * length);
                concat[0] = '\0';
                char *temp[3] = {path, "/", allFiles->d_name};

                Concat(concat, temp, 3);
                RM(argv, concat);
                free(concat);
            }
            allFiles = readdir(dir);
        }
        printf("Deleted directory: %s\n", path);
    }
    else if(access(path, F_OK))
    {
        printf("Rm: file does not exists\n");
    }
    else
    {
        printf("Deleted file: %s\n", path);
    }
    remove(path);
    closedir(dir);
}

void RENAME(int argv, char **args)
{
    if(argv > 2)
    {
        int i = rename(args[1], args[2]);
        if(i == 0)
        {
            printf("File has been renamed\n");
        }
        else
        {
            printf("File cannot be renamed\n");
        }
    }
}