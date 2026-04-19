#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// External functions
void runLexerWrapper(char* input);
void runParserAndTAC(char* expr);

int main() {
    char input[100];

    printf("Enter expression : ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = 0;

    // MODULE 1 → LEXER
    runLexerWrapper(input);

    // MODULE 2–5 → PARSER + TAC + OPTIMIZATION
    runParserAndTAC(input);

    printf("\n--- MINI COMPILER COMPLETE ---\n");

    return 0;
}
