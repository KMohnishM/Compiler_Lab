#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int ip = 0;

/* 🔹 TEMP GENERATOR */
int tempCount = 1;

char* newtemp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", tempCount++);
    return temp;
}

/* 🔹 FORWARD DECLARATIONS */
char* E();
char* Eprime(char* inherited);
char* T();
char* Tprime(char* inherited);
char* F();

/* 🔥 E → T E' */
char* E() {
    char* t = T();
    return Eprime(t);
}

/* 🔥 E' → + T E' | - T E' | ε */
char* Eprime(char* inherited) {

    if (input[ip] == '+') {
        ip++;
        char* t = T();

        char* temp = newtemp();
        printf("%s = %s + %s\n", temp, inherited, t);

        return Eprime(temp);
    }

    else if (input[ip] == '-') {
        ip++;
        char* t = T();

        char* temp = newtemp();
        printf("%s = %s - %s\n", temp, inherited, t);

        return Eprime(temp);
    }

    return inherited; // ε
}

/* 🔥 T → F T' */
char* T() {
    char* f = F();
    return Tprime(f);
}

/* 🔥 T' → * F T' | / F T' | ε */
char* Tprime(char* inherited) {

    if (input[ip] == '*') {
        ip++;
        char* f = F();

        char* temp = newtemp();
        printf("%s = %s * %s\n", temp, inherited, f);

        return Tprime(temp);
    }

    else if (input[ip] == '/') {
        ip++;
        char* f = F();

        char* temp = newtemp();
        printf("%s = %s / %s\n", temp, inherited, f);

        return Tprime(temp);
    }

    return inherited; // ε
}

/* 🔥 F → (E) | id */
char* F() {

    if (input[ip] == '(') {
        ip++;
        char* e = E();

        if (input[ip] == ')') {
            ip++;
            return e;
        } else {
            printf("Error: Missing )\n");
            exit(1);
        }
    }

    else if (isalpha(input[ip])) {
        char* temp = (char*)malloc(10);
        temp[0] = input[ip];
        temp[1] = '\0';
        ip++;
        return temp;
    }

    printf("Error: Invalid token at position %d\n", ip);
    exit(1);
}

/* 🔹 MAIN */
int main() {

    printf("Enter expression: ");
    scanf("%s", input);

    char* result = E();

    if (input[ip] == '\0') {
        printf("Accepted\n");
        printf("Final Result in: %s\n", result);
    } else {
        printf("Syntax Error\n");
    }

    return 0;
}