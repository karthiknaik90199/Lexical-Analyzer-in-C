#include "lexer.h"

/* Preprocessor */

int isPreprocessor(const char *str)
{
    const char *pre[] =
    {
        "#include",
        "#define",
        "#ifdef",
        "#ifndef",
        "#endif",
        "#if",
        "#else",
        "#elif",
        "#pragma",
        "#error",
        "#undef",
        "#line"
    };

    int n = sizeof(pre) / sizeof(pre[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(str, pre[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}


/* Preprocessor Scanner */

int scanPreprocessor(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;

    /* Store # */
    token[i++] = '#';

    /* Read characters after # */
    ch = fgetc(fp);

    while (isalpha((unsigned char)ch))
    {
        if (i < MAX_TOKEN - 1)
        {
            token[i++] = ch;
        }

        ch = fgetc(fp);
    }

    /* End token */
    token[i] = '\0';


    /* Check preprocessor directive */

    if (isPreprocessor(token))
    {
        printf("%d  %s --> Preprocessor Directive\n",
               *line, token);
    }
    else
    {
        printf("%d  %s --> Invalid Token\n",
               *line, token);
    }


    /* Skip spaces and tabs */

    while (ch == ' ' || ch == '\t')
    {
        ch = fgetc(fp);
    }


    /* Check #include */

    if (strcmp(token, "#include") == 0)
    {

        /* =========================
           #include <stdio.h>
           ========================= */

        if (ch == '<')
        {
            i = 0;

            token[i++] = '<';

            ch = fgetc(fp);

            while (ch != '>' &&
                   ch != EOF &&
                   ch != '\n')
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i++] = ch;
                }

                ch = fgetc(fp);
            }


            if (ch == '>')
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i++] = '>';
                }

                token[i] = '\0';

                printf("%d  %s --> Header File\n",
                       *line, token);
            }
            else
            {
                token[i] = '\0';

                printf("%d  %s --> Invalid Header File\n",
                       *line, token);
            }

            return 1;
        }


        /* =========================
           #include "stdio.h"
           ========================= */

        if (ch == '"')
        {
            i = 0;

            token[i++] = '"';

            ch = fgetc(fp);

            while (ch != '"' &&
                   ch != EOF &&
                   ch != '\n')
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i++] = ch;
                }

                ch = fgetc(fp);
            }


            if (ch == '"')
            {
                if (i < MAX_TOKEN - 1)
                {
                    token[i++] = '"';
                }

                token[i] = '\0';

                printf("%d  %s --> Header File\n",
                       *line, token);
            }
            else
            {
                token[i] = '\0';

                printf("%d  %s --> Invalid Header File\n",
                       *line, token);
            }

            return 1;
        }
    }


    /* Put unused character back */

    if (ch != EOF)
    {
        ungetc(ch, fp);
    }

    return 1;
}