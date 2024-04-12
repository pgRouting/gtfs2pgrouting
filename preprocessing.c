#include "preprocessing.h"

int is_in(char *string, char **list, int list_length)
{
    int result = -1;

    int i = 0;

    for (i = 0; i < list_length; i++)
    {
        if(strcmp(string, list[i]) == 0)
        {
            result = i;
            break;
        }
    }

    return result;
}

int ignore_kth_column(int k, char *line, char delimiter)
{
    int i, string_length = 0;

    string_length = strlen(line);

    for (i = 0; i < string_length; i++)
    {
        if (line[i] == delimiter)
        {
            
        }
    }
}