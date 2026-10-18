
#include "lexer.h"

int isNumber(const char *str)
{
    int i = 0;
    int len = strlen(str);
    int digit = 0;

    /* Hexadecimal number */
    if (len >= 2 &&
        str[0] == '0' &&
        (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;

        if (i == len)
            return 0;

        while (i < len && isxdigit((unsigned char)str[i]))
        {
            digit = 1;
            i++;
        }

        return digit && i == len;
    }

    /* Integer digits */
    while (i < len && isdigit((unsigned char)str[i]))
    {
        digit = 1;
        i++;
    }

    /* Decimal part */
    if (i < len && str[i] == '.')
    {
        i++;

        while (i < len && isdigit((unsigned char)str[i]))
        {
            digit = 1;
            i++;
        }
    }

    if (!digit)
        return 0;

    /* Exponent */
    if (i < len && (str[i] == 'e' || str[i] == 'E'))
    {
        i++;

        if (i < len && (str[i] == '+' || str[i] == '-'))
            i++;

        if (i >= len || !isdigit((unsigned char)str[i]))
            return 0;

        while (i < len && isdigit((unsigned char)str[i]))
            i++;
    }

    return i == len;
}


int scanNumber(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;
    int invalid = 0;
    int isHex = 0;
    int hexDigits = 0;
    int exponentDigits = 0;

    ch = fgetc(fp);

    if (!isdigit((unsigned char)ch))
    {
        if (ch != EOF)
            ungetc(ch, fp);

        return 0;
    }

    token[i++] = ch;

    /* Check hexadecimal prefix */
    if (ch == '0')
    {
        ch = fgetc(fp);

        if (ch == 'x' || ch == 'X')
        {
            isHex = 1;
            token[i++] = ch;

            ch = fgetc(fp);

            while (isxdigit((unsigned char)ch))
            {
                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;

                hexDigits++;
                ch = fgetc(fp);
            }

            /* Consume invalid characters attached to hex */
            while (isalnum((unsigned char)ch) || ch == '_')
            {
                invalid = 1;

                if (i < MAX_TOKEN - 1)
                    token[i++] = ch;

                ch = fgetc(fp);
            }

            token[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (hexDigits == 0 || invalid || !isNumber(token))
                reportInvalidNumber(token, *line);
            else
                printf("%d  %s --> Hexadecimal Constant\n",
                       *line, token);

            return 1;
        }

        if (ch != EOF)
            ungetc(ch, fp);
    }

    /* Read remaining integer digits */
    while ((ch = fgetc(fp)) != EOF &&
           isdigit((unsigned char)ch))
    {
        if (i < MAX_TOKEN - 1)
            token[i++] = ch;
    }

    /* Decimal part */
    if (ch == '.')
    {
        if (i < MAX_TOKEN - 1)
            token[i++] = ch;

        ch = fgetc(fp);

        while (isdigit((unsigned char)ch))
        {
            if (i < MAX_TOKEN - 1)
                token[i++] = ch;

            ch = fgetc(fp);
        }
    }

    /* Exponent part */
    if (ch == 'e' || ch == 'E')
    {
        if (i < MAX_TOKEN - 1)
            token[i++] = ch;

        ch = fgetc(fp);

        if (ch == '+' || ch == '-')
        {
            if (i < MAX_TOKEN - 1)
                token[i++] = ch;

            ch = fgetc(fp);
        }

        while (isdigit((unsigned char)ch))
        {
            if (i < MAX_TOKEN - 1)
                token[i++] = ch;

            exponentDigits++;
            ch = fgetc(fp);
        }

        if (exponentDigits == 0)
            invalid = 1;
    }

    /* Detect malformed tokens such as 12.3.4 or 45abc */
    while (ch == '.' ||
           isalnum((unsigned char)ch) ||
           ch == '_')
    {
        invalid = 1;

        if (i < MAX_TOKEN - 1)
            token[i++] = ch;

        ch = fgetc(fp);
    }

    token[i] = '\0';

    if (ch != EOF)
        ungetc(ch, fp);

    /* Exactly one classification */
    if (invalid || !isNumber(token))
    {
        reportInvalidNumber(token, *line);
    }
    else if (strchr(token, '.') != NULL ||
             strchr(token, 'e') != NULL ||
             strchr(token, 'E') != NULL)
    {
        printf("%d  %s --> Floating-point Constant\n",
               *line, token);
    }
    else
    {
        printf("%d  %s --> Integer Constant\n",
               *line, token);
    }

    return 1;
}
