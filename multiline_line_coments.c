#include "lexer.h"

int scanMultiLineComment(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;
    int startLine = *line;

    /* Store opening comment symbols */
    token[i++] = '/';
    token[i++] = '*';

    ch = fgetc(fp);

    while (ch != EOF)
    {
        /* Check for closing */
        if (ch == '*')
        {
            int next = fgetc(fp);

            if (next == '/')
            {
                if (i < MAX_TOKEN - 1)
                    token[i++] = '*';

                if (i < MAX_TOKEN - 1)
                    token[i++] = '/';

                token[i] = '\0';

                printf("%d  %s --> Multi-line Comment\n",
                       startLine, token);

                return 1;
            }

            /* Store '*' */
            if (i < MAX_TOKEN - 1)
                token[i++] = '*';

            /* Put next character back */
            if (next != EOF)
                ungetc(next, fp);
        }
        else
        {
            /* Count lines */
            if (ch == '\n')
                (*line)++;

            /* Store character */
            if (i < MAX_TOKEN - 1)
                token[i++] = ch;
        }

        ch = fgetc(fp);
    }

    /* EOF reached without finding */ 
    token[i] = '\0';

    reportUnterminatedComment(startLine);

    return 0;
}