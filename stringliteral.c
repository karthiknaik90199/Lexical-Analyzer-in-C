#include "lexer.h"

int scanString(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;

    /* Read opening quote */
    ch = fgetc(fp);

    if (ch != '"')
    {
        return 0;
    }

    token[i++] = '"';

    /* Read string contents */
    while (1)
    {
        ch = fgetc(fp);

        /* Closing quote */
        if (ch == '"')
        {
            token[i++] = '"';
            token[i] = '\0';

            printf("%d  %s --> String Literal\n",
                   *line, token);

            return 1;
        }

        /* Unterminated string */
        if (ch == EOF || ch == '\n')
        {
            token[i] = '\0';

            reportUnterminatedString(*line);

            return 0;
        }

        /* Store character */
        if (i < MAX_TOKEN - 1)
        {
            token[i++] = ch;
        }
    }
}


int isStringLiteral(const char *str)
{
    int len = strlen(str);

    if (len >= 2 &&
        str[0] == '"' &&
        str[len - 1] == '"')
    {
        return 1;
    }

    return 0;
}