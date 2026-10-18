#include "lexer.h"

int main()
{
    FILE *fp;
    char token[MAX_TOKEN];

    int line = 1;
    int ch;
    int next;

    fp = fopen("input", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        /* New line */
        if (ch == '\n')
        {
            line++;
        }

        /* Space / tab */
        else if (ch == ' ' || ch == '\t')
        {
            /* Ignore */
        }

        /* Preprocessor */
        else if (ch == '#')
        {
            scanPreprocessor(fp, token, &line);
        }

        /* Comments / Division */
        else if (ch == '/')
        {
            next = fgetc(fp);

            /* Single-line comment */
            if (next == '/')
            {
                scanSingleLineComment(fp, token, &line);
            }

            /* Multi-line comment */
            else if (next == '*')
            {
                scanMultiLineComment(fp, token, &line);
            }

            /* Division operator */
            else
            {
                if (next != EOF)
                {
                    ungetc(next, fp);
                }

                scanOperator(fp, token, &line);
            }
        }

        /* String literal */
        else if (ch == '"')
  {
       ungetc(ch, fp);

    scanString(fp, token, &line);
}

        /* Character constant */
        else if (ch == '\'')
        {
            ungetc(ch, fp);

            scanCharacter(fp, token, &line);
        }

        /* Identifier / Keyword */
        else if (isalpha((unsigned char)ch) || ch == '_')
        {
            ungetc(ch, fp);

            scanIdentifier(fp, token, &line);
        }

        /* Number */
        else if (isdigit((unsigned char)ch))
        {
            ungetc(ch, fp);

            scanNumber(fp, token, &line);
           //reportInvalidNumber(token, line);

        }
        /* Operators / Special symbols */
        else if (ispunct((unsigned char)ch))
        {
            ungetc(ch, fp);

            /* Try operator first */
            if (!scanOperator(fp, token, &line))
            {
                /* Try special symbol */
                if (!scanSpecial(fp, token, &line))
                {
                    /*
                     * Neither operator nor special symbol.
                     * Read the same character and report error.
                     */
                    ch = fgetc(fp);

                    reportInvalidCharacter(ch, line);
                }
            }
        }

        /* Invalid character */
        else
        {
            reportInvalidCharacter(ch, line);
        }
    }

    fclose(fp);

    return 0;
}