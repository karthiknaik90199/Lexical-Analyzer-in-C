#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 100

int isPreprocessor(const char *str);
int scanPreprocessor(FILE *fp, char token[], int *line);
int isSingleLineComment(const char *str);
int scanSingleLineComment(FILE *fp, char token[], int *line);
int isMultiLineComment(const char *str);
int scanMultiLineComment(FILE *fp, char token[], int *line);
int isIdentifier(const char *str);
int scanIdentifier(FILE *fp, char token[], int *line);
int isStringLiteral(const char *str);
int scanString(FILE *fp, char token[], int *line);
int isCharacterConstant(const char *str);
int scanCharacter(FILE *fp, char token[], int *line);
int isOperator(const char *str);
int scanOperator(FILE *fp, char token[], int *line);
int isNumber(const char *str);
int scanNumber(FILE *fp, char token[], int *line);
int isSpecial(const char *str);
int scanSpecial(FILE *fp, char token[], int *line); 
void reportInvalidCharacter(int ch, int line);
void reportUnterminatedString(int line);
void reportUnterminatedCharacter(int line);
void reportUnterminatedComment(int line);
void reportInvalidNumber(const char token[], int line);

#endif