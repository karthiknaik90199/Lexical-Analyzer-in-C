#include "lexer.h"

const char *special[] =
{
    "(",
    ")",
    "{",
    "}",
    "[",
    "]",
    ";",
    ",",
    "."
};

int n = sizeof(special) / sizeof(special[0]);


int isSpecial(const char *str)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, special[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}


int scanSpecial(FILE *fp, char token[], int *line)
{
    int ch;

    ch = fgetc(fp);

    if (ch == EOF)
    {
        return 0;
    }

    token[0] = ch;
    token[1] = '\0';

    /* Check special symbol */
    if (isSpecial(token))
    {
        printf("%d  %s --> Special Symbol\n",
               *line, token);

        return 1;
    }

    /*
     * Not a special symbol.
     * Put it back so main can report it.
     */
    ungetc(ch, fp);

    return 0;
}