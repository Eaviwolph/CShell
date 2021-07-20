#include <stdio.h>
#include <stdlib.h>

int ComparString(char *s1, char *s2)
{
	int i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] == s2[i]);
}

int DeleteNewLine(char *s)
{
	int i = 0;
	while (s[i] != '\0' && s[i] != '\n')
	{
		i++;
	}
	if (s[i] == '\n')
	{
		s[i] = '\0';
		return 1;
	}
	return 0;
}

int NumberOfWords(char* input)
{
    int spaceNum = 0;
    int afterSpace = 1;
    for(int i = 0; input[i] != '\0'; i++)
    {
        if(input[i] == '"')
        {
            i++;
            afterSpace = 0;
            spaceNum++;
            while(input[i] != '\0' && input[i] != '"')
            {
                i++;
            }
        }
        else if(input[i] == ' ')
        {
            afterSpace = 1;
        }
        else if(afterSpace == 1 && input[i] != ' ')
        {
            afterSpace = 0;
            spaceNum++;
        }
    }
    return spaceNum;
}

char** CutCommand(char* input, int numWords)
{
    char** array = malloc(sizeof (char **) * numWords);
    int arrayIndex = 0;
    for(int i = 0; input[i] != '\0'; i++)
    {
        int j = -1;
        if(input[i] == '"')
        {
            i++;
            j = i;
            while(input[j] != '\0' && input[j] != '"')
            {
                j++;
            }
        }
        else if(input[i] != ' ')
        {
            j = i;
            while(input[j] != '\0' && input[j] != ' ')
            {
                j++;
            }
            
        }
        if(j != -1)
        {
            array[arrayIndex] = malloc(sizeof(char*) * (j-i+1));

            for(int t = i; t < j; t++)
            {
                array[arrayIndex][t-i] = input[t];
            }
            array[arrayIndex][j-i] = '\0';
            arrayIndex++;
            i = j;
            if(input[j] == '\0')
            {
                i--;
            }
        }
    }
    return array;
}

void Free2DCharArray(char** array, int lenght)
{
    for(int i = 0; i<lenght; i++)
    {
        free(array[i]);
    }
    free(array);
}

void Concat(char* dest, char** sL, int sLLength)
{
    int i = 0;
    while(dest[i] != '\0')
    {
        i++;
    }
    for(int j = 0; j < sLLength; j++)
    {
        //printf("%s\n", sL[j]);
        int t = 0;
        while(sL[j][t] != '\0')
        {
            dest[i] = sL[j][t];
            t++;
            i++;
        }
    }
    dest[i] = '\0';
}

int StringLength(char* s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return i;
}