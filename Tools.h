#ifndef TOOLS
#define TOOLS

#define MAX_INPUT_SIZE 200
#define MAX_PATH_SIZE 200

void Free2DCharArray(char** array, int lenght);
int NumberOfWords(char* input);
char** CutCommand(char* input, int numWords);
int ComparString(char *s1, char *s2);
int DeleteNewLine(char *s);
int StringLength(char* s);
char* Concat(char* dest, char** sL, int sLLength);

#endif