#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int pos = 0;
int tempCount = 1;

// ================= AST NODE =================
typedef struct Node {
    char op;
    int value;
    struct Node* left;
    struct Node* right;
} Node;

// ================= CREATE NODE =================
Node* createNode(char op, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->op = op;
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

void skipSpaces() {
    while (input[pos] == ' ') pos++;
}

Node* E();
Node* T();
Node* F();

// F -> (E) | number
Node* F() {
    skipSpaces();

    if (input[pos] == '(') {
        pos++;
        Node* node = E();

        if (input[pos] == ')')
            pos++;
        else {
            printf("Error: Missing )\n");
            exit(1);
        }
        return node;
    }

    else if (isdigit(input[pos])) {
        int val = 0;
        while (isdigit(input[pos])) {
            val = val * 10 + (input[pos] - '0');
            pos++;
        }
        return createNode('n', val);
    }

    printf("Error: Invalid input\n");
    exit(1);
}

// T -> F { * / }
Node* T() {
    Node* left = F();

    while (1) {
        skipSpaces();

        if (input[pos] == '*') {
            pos++;
            Node* right = F();

            Node* node = createNode('*', 0);
            node->left = left;
            node->right = right;

            left = node;
        }
        else if (input[pos] == '/') {
            pos++;
            Node* right = F();

            Node* node = createNode('/', 0);
            node->left = left;
            node->right = right;

            left = node;
        }
        else break;
    }

    return left;
}

// E -> T { + - }
Node* E() {
    Node* left = T();

    while (1) {
        skipSpaces();

        if (input[pos] == '+') {
            pos++;
            Node* right = T();

            Node* node = createNode('+', 0);
            node->left = left;
            node->right = right;

            left = node;
        }
        else if (input[pos] == '-') {
            pos++;
            Node* right = T();

            Node* node = createNode('-', 0);
            node->left = left;
            node->right = right;

            left = node;
        }
        else break;
    }

    return left;
}

// ================= TAC GENERATION =================
int generateTAC(Node* root) {
    if (root->op == 'n') {
        return root->value;
    }

    int left = generateTAC(root->left);
    int right = generateTAC(root->right);

    int temp = tempCount++;

    printf("t%d = ", temp);

    if (root->left->op == 'n')
        printf("%d ", left);
    else
        printf("t%d ", left);

    printf("%c ", root->op);

    if (root->right->op == 'n')
        printf("%d\n", right);
    else
        printf("t%d\n", right);

    return temp;
}

// ================= MAIN FUNCTION FOR COMPILER =================
void runParserAndTAC(char* expr) {
    strcpy(input, expr);
    pos = 0;
    tempCount = 1;

    Node* root = E();

    printf("\n--- THREE ADDRESS CODE (TAC) ---\n");
    generateTAC(root);

    printf("\n[Optimization]: Common Subexpression Elimination (demo)\n");
}
