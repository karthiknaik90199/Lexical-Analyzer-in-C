#include "lexer.h"

int scanSingleLineComment(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;

    token[i++] = '/';
    token[i++] = '/';

    ch = fgetc(fp);

    while (ch != '\n' && ch != EOF)
    {
        if (i < MAX_TOKEN - 1)
        {
            token[i++] = ch;
        }

        ch = fgetc(fp);
    }

    token[i] = '\0';

    printf("%d  %s --> Single-line Comment\n",
           *line, token);

    if (ch == '\n')
    {
        (*line)++;
    }

    return 1;
}