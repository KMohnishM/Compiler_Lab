#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int ip = 0;

/* 🔹 FORWARD DECLARATIONS */
int E();
int Eprime(int inherited);
int T();
int Tprime(int inherited);
int F();

/* 🔥 E → T E' */
int E() {
    int t = T();
    return Eprime(t);
}

/* 🔥 E' → + T E' | ε */
int Eprime(int inherited) {

    if (input[ip] == '+') {
        ip++;
        int t = T();
        return Eprime(inherited + t);
    }

    return inherited;
}

/* 🔥 T → F T' */
int T() {
    int f = F();
    return Tprime(f);
}

/* 🔥 T' → * F T' | ε */
int Tprime(int inherited) {

    if (input[ip] == '*') {
        ip++;
        int f = F();
        return Tprime(inherited * f);
    }

    return inherited;
}

/* 🔥 F → (E) | id */
int F() {

    if (input[ip] == '(') {
        ip++;
        int val = E();

        if (input[ip] == ')') {
            ip++;
            return val;
        } else {
            printf("Error: Missing )\n");
            exit(1);
        }
    }

    else if (isdigit(input[ip])) {
        int val = input[ip] - '0';
        ip++;
        return val;
    }

    printf("Error at position %d\n", ip);
    exit(1);
}

/* 🔹 MAIN */
int main() {

    printf("Enter expression: ");
    scanf("%s", input);

    int result = E();

    if (input[ip] == '\0') {
        printf("Accepted\n");
        printf("Value = %d\n", result);
    } else {
        printf("Syntax Error\n");
    }

    return 0;
}