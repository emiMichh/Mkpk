#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
    "Gramatica para una fbf" serie de reglas para construir un lenguaje

    <expr>   ::= <variable> | "~" "("  <expr> ")" | "(" <expr> <op> <expr> ")"
    <op>     ::= "+" | "*" | "-"
    <variable> ::= [a-zA-Z]
*/

#define MAX_LEN 100

char input[MAX_LEN];
int indx = 0;

// Prototipos de funciones
int expr();
int variable();
int op();

// Avanza en la entrada
void advance() 
{
    indx++;
}

// Verifica el carácter actual sin avanzar
char peek() {
    return input[indx];
}

// Comprueba si el carácter actual coincide con lo esperado y avanza
int match(char expected) {
    if (peek() == expected) {
        advance();
        return 1;
    }
    return 0;
}

// Regla: <variable> ::= [a-zA-Z]
int variable() {
    if (isalpha(peek())) {
        advance();
        return 1;
    }
    return 0;
}

// Regla: <op> ::= '+' | '*' | '-'
int op() {
    if (match('+') || match('*') || match('-')) {
        return 1;
    }
    return 0;
}

// Regla: <expr> ::= <variable> | "~" "(" <expr> ")" | "(" <expr> <op> <expr> ")"
int expr() {
    if (variable()) {
        return 1;
    }
    if(match('~')){
        if (!match('(')) return 0;
        if (!expr()) return 0;
        if (!match(')')) return 0;
        return 1;
    } 
    if (match('(')) {
        if (!expr()) return 0;
        if (!op()) return 0;
        if (!expr()) return 0;
        if (!match(')')) return 0;
        return 1;
    }
    return 0;
}

int parse(const char *str) {
    strncpy(input, str, MAX_LEN - 1);
    input[MAX_LEN - 1] = '\0';
    indx = 0;
    if (expr() && input[indx] == '\0') { // revisa que sea una fbf y no salga del tam del array
        return 1;
    }
    return 0;
}

int main() {
    const char *tests[] = { //apunta a varias cosas que no cambian
        "a",
        "~a",
        "(a+b)",
        "(x*y)",
        "(~a*b)",
        "(a-(b*c))",
        "(a+b",
        "a+",
        "(a+)",
        "(((a+b)*(c-d))+~(x*y))",
        "(((a+b)*(c-d)+~(x*y)",
        "(p-(q-r))",
        "(((~p)-q)-r)",
        "~(p)"
    };
 
     for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
         printf("Testing '%s': %s \n", tests[i], parse(tests[i]) ? "Valid" : "Invalid");
     }
    
    return 0;
}
