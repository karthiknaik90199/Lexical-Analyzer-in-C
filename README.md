# Lexical-Analyzer-in-C
A modular C-based Lexical Analyzer that identifies tokens in C source code, including keywords, identifiers, constants, operators, strings, comments, and preprocessor directives, with lexical error handling.
# Lexical Analyzer in C

A modular Lexical Analyzer developed using C programming to read and analyze C source code, identify tokens, and detect common lexical errors.

## Features

- **Keyword and Identifier Detection** – Identifies C keywords and user-defined identifiers.
- **Numeric Constants** – Recognizes integer, hexadecimal, and floating-point constants.
- **Operator Recognition** – Identifies arithmetic, relational, logical, assignment, increment/decrement, compound assignment, and bitwise operators.
- **String and Character Constants** – Detects string literals and character constants.
- **Preprocessor Directives** – Recognizes directives such as `#include` and `#define`, along with header files.
- **Comment Detection** – Identifies single-line and multi-line comments.
- **Special Symbols** – Recognizes symbols such as parentheses, braces, brackets, commas, and semicolons.
- **Lexical Error Handling** – Detects invalid characters, malformed numeric constants, and unterminated strings, character constants, and comments.

## Technologies Used

- C Programming
- File Handling
- String Manipulation
- Modular Programming
- GCC Compiler

## Project Structure

The project is organized into separate source files, with a shared `lexer.h` header file.

- `main.c` – Main program and token scanning flow
- `lexer.h` – Function declarations and common definitions
- `Preprocessor.c` – Preprocessor directives and header files
- `identifier.c` – Keyword and identifier detection
- `number.c` – Numeric constant recognition and validation
- `operators.c` – Operator identification
- `special.c` – Special symbol recognition
- `stringliteral.c` – String literal detection
- `character.c` – Character constant detection
- `single_line_comments.c` – Single-line comment detection
- `multiline_line_coments.c` – Multi-line comment detection
- `error_handling.c` – Lexical error reporting

## How to Compile and Run

Compile the project using GCC:

```bash
gcc main.c Preprocessor.c single_line_comments.c multiline_line_coments.c identifier.c stringliteral.c character.c operators.c number.c special.c error_handling.c -o lexer.exe
```

Run on Windows:

```powershell
.\lexer.exe
```

The program reads C source code from `input.c` and displays the identified tokens along with their classifications and detected lexical errors.

## Learning Outcomes

This project strengthened my understanding of lexical analysis, compiler fundamentals, file handling, modular programming, and error detection in C.

## Future Enhancements

- Support for additional C numeric literal formats and suffixes
- Improved validation of malformed tokens
- More comprehensive C operator recognition
- Detailed token reports and automated test cases
