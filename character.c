#include "lexer.h"

int scanCharacter(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;

    /* Store opening ' */
    token[i++] = '\'';

    /* Read character after opening ' */
    ch = fgetc(fp);

    /* Read until closing ' */
    while (ch != '\'' &&
           ch != EOF &&
           ch != '\n')
    {
        if (i < MAX_TOKEN - 1)
        {
            token[i++] = ch;
        }

        ch = fgetc(fp);
    }

    /* Closing ' found */
    if (ch == '\'')
    {
        if (i < MAX_TOKEN - 1)
        {
            token[i++] = '\'';
        }

        token[i] = '\0';

        printf("%d  %s --> Character Constant\n",
               *line, token);

        return 1;
    }

    /* Unterminated character constant */
    token[i] = '\0';

    reportUnterminatedCharacter(*line);

    return 0;
}


/* Check whether token is a character constant */

int isCharacterConstant(const char *str)
{
    int len = strlen(str);

    if (len >= 3 &&
        str[0] == '\'' &&
        str[len - 1] == '\'')
    {
        return 1;
    }

    return 0;
}