#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// ================= TOKEN TYPES =================
typedef enum {
    T_IDENTIFIER,
    T_INT_LITERAL,
    T_FLOAT_LITERAL,
    T_PLUS,
    T_MINUS,
    T_MULT,
    T_DIV,
    T_UNKNOWN
} TokenType;

// ================= TOKEN STRUCT =================
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

// ================= TOKEN NAME FUNCTION =================
const char* getTokenName(TokenType type) {
    switch (type) {
    case T_IDENTIFIER: return "IDENTIFIER";
    case T_INT_LITERAL: return "INT_LITERAL";
    case T_FLOAT_LITERAL: return "FLOAT_LITERAL";
    case T_PLUS: return "PLUS";
    case T_MINUS: return "MINUS";
    case T_MULT: return "MULTIPLY";
    case T_DIV: return "DIVIDE";
    default: return "UNKNOWN";
    }
}

// ================= PRINT TOKEN =================
void printToken(Token token) {
    printf("Token: %-10s Type: %s\n",
        token.value,
        getTokenName(token.type));
}

// ================= LEXER =================
void runLexer(const char* input) {
    int i = 0;

    while (input[i] != '\0') {

        if (isspace(input[i])) { i++; continue; }

        Token token;
        int j = 0;

        // IDENTIFIER
        if (isalpha(input[i])) {
            while (isalnum(input[i]))
                token.value[j++] = input[i++];
            token.value[j] = '\0';

            token.type = T_IDENTIFIER;
        }

        // NUMBER
        else if (isdigit(input[i])) {
            int isFloat = 0;

            while (isdigit(input[i]) || input[i] == '.') {
                if (input[i] == '.') isFloat = 1;
                token.value[j++] = input[i++];
            }

            token.value[j] = '\0';
            token.type = isFloat ? T_FLOAT_LITERAL : T_INT_LITERAL;
        }

        // OPERATORS
        else {
            char ch = input[i++];
            token.value[0] = ch;
            token.value[1] = '\0';

            switch (ch) {
            case '+': token.type = T_PLUS; break;
            case '-': token.type = T_MINUS; break;
            case '*': token.type = T_MULT; break;
            case '/': token.type = T_DIV; break;
            default: token.type = T_UNKNOWN;
            }
        }

        printToken(token);
    }
}

// ================= WRAPPER =================
void runLexerWrapper(char* input) {
    printf("\n--- LEXER OUTPUT ---\n");
    runLexer(input);
}
