#include "lexer.h"

/* Check whether token is a keyword */
int isIdentifier(const char *str)
{
    const char *keywords[] =
    {
        "auto",
        "break",
        "case",
        "char",
        "const",
        "continue",
        "default",
        "do",
        "double",
        "else",
        "enum",
        "extern",
        "float",
        "for",
        "goto",
        "if",
        "inline",
        "int",
        "long",
        "register",
        "restrict",
        "return",
        "short",
        "signed",
        "sizeof",
        "static",
        "struct",
        "switch",
        "typedef",
        "union",
        "unsigned",
        "void",
        "volatile",
        "while"
    };

    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    /* Check whether string is a keyword */
    for (int i = 0; i < numKeywords; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 0;       // Keyword
        }
    }

    /* First character must be alphabet or '_' */
    if (!isalpha((unsigned char)str[0]) && str[0] != '_')
    {
        return 0;
    }

    /* Remaining characters */
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!isalnum((unsigned char)str[i]) && str[i] != '_')
        {
            return 0;
        }
    }

    return 1;               // Identifier
}


/* Scan identifier / keyword */
int scanIdentifier(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;

    /* Read first character */
    ch = fgetc(fp);

    /* Check first character */
    if (isalpha((unsigned char)ch) || ch == '_')
    {
        token[i++] = ch;

        /* Read remaining characters */
        ch = fgetc(fp);

        while (isalnum((unsigned char)ch) || ch == '_')
        {
            if (i < MAX_TOKEN - 1)
            {
                token[i++] = ch;
            }

            ch = fgetc(fp);
        }

        /* End string */
        token[i] = '\0';

        /* Put next character back */
        if (ch != EOF)
        {
            ungetc(ch, fp);
        }

        /* Check keyword or identifier */
        if (isIdentifier(token))
        {
            printf("%d  %s --> Identifier\n",
                   *line, token);
        }
        else
        {
            printf("%d  %s --> Keyword\n",
                   *line, token);
        }

        return 1;
    }

    /* Not an identifier */
    if (ch != EOF)
    {
        ungetc(ch, fp);
    }

    return 0;
}