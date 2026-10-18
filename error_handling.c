#include "lexer.h"

void reportInvalidCharacter(int ch, int line)
{
    printf("%d  %c --> Invalid Character\n", line, ch);
}

void reportUnterminatedString(int line)
{
    printf("%d  --> Lexical Error: Unterminated String Literal\n",
           line);
}

void reportUnterminatedCharacter(int line)
{
    printf("%d  --> Lexical Error: Unterminated Character Constant\n",
           line);
}

void reportUnterminatedComment(int line)
{
    printf("%d  --> Lexical Error: Unterminated Comment\n",
           line);
}

void reportInvalidNumber(const char token[], int line)
{
    printf("%d  %s --> Invalid Number\n", line, token);
}