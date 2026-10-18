#include "lexer.h"


/* Check whether character can start an operator */
int isOperatorStart(int ch)
{
    if (ch == '+' ||
        ch == '-' ||
        ch == '*' ||
        ch == '/' ||
        ch == '%' ||
        ch == '=' ||
        ch == '<' ||
        ch == '>' ||
        ch == '!' ||
        ch == '&' ||
        ch == '|')
    {
        return 1;
    }

    return 0;
}


/* Scan and classify operator */
int scanOperator(FILE *fp, char token[], int *line)
{
    int i = 0;
    int ch;
    int next;

    /* Read first character */
    ch = fgetc(fp);

    /* Not an operator */
    if (!isOperatorStart(ch))
    {
        if (ch != EOF)
        {
            ungetc(ch, fp);
        }

        return 0;
    }

    /* Store first character */
    token[i++] = ch;

    /* Read next character */
    next = fgetc(fp);


    /* +  ++  += */
    if (ch == '+')
    {
        if (next == '+' || next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* -  --  -= */
    else if (ch == '-')
    {
        if (next == '-' || next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* *  *= */
    else if (ch == '*')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* /  /= */
    else if (ch == '/')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* %  %= */
    else if (ch == '%')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* =  == */
    else if (ch == '=')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* <  <= */
    else if (ch == '<')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* >  >= */
    else if (ch == '>')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* !  != */
    else if (ch == '!')
    {
        if (next == '=')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* &  && */
    else if (ch == '&')
    {
        if (next == '&')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* |  || */
    else if (ch == '|')
    {
        if (next == '|')
        {
            token[i++] = next;
        }
        else if (next != EOF)
        {
            ungetc(next, fp);
        }
    }


    /* End the string */
    token[i] = '\0';


    /* =========================
       CLASSIFICATION
       ========================= */

    /* Increment / Decrement */
    if (strcmp(token, "++") == 0 ||
        strcmp(token, "--") == 0)
    {
        printf("%d  %s --> Increment/Decrement Operator\n",
               *line, token);
    }


    /* Compound Assignment */
    else if (strcmp(token, "+=") == 0 ||
             strcmp(token, "-=") == 0 ||
             strcmp(token, "*=") == 0 ||
             strcmp(token, "/=") == 0 ||
             strcmp(token, "%=") == 0)
    {
        printf("%d  %s --> Compound Assignment Operator\n",
               *line, token);
    }


    /* Relational */
    else if (strcmp(token, "==") == 0 ||
             strcmp(token, "!=") == 0 ||
             strcmp(token, "<") == 0 ||
             strcmp(token, ">") == 0 ||
             strcmp(token, "<=") == 0 ||
             strcmp(token, ">=") == 0)
    {
        printf("%d  %s --> Relational Operator\n",
               *line, token);
    }


    /* Logical */
    else if (strcmp(token, "&&") == 0 ||
             strcmp(token, "||") == 0 ||
             strcmp(token, "!") == 0)
    {
        printf("%d  %s --> Logical Operator\n",
               *line, token);
    }


    /* Bitwise */
    else if (strcmp(token, "&") == 0 ||
             strcmp(token, "|") == 0)
    {
        printf("%d  %s --> Bitwise Operator\n",
               *line, token);
    }


    /* Assignment */
    else if (strcmp(token, "=") == 0)
    {
        printf("%d  %s --> Assignment Operator\n",
               *line, token);
    }


    /* Arithmetic */
    else
    {
        printf("%d  %s --> Arithmetic Operator\n",
               *line, token);
    }

    return 1;
}