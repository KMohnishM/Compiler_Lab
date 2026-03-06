// S     → IF | FOR | BLOCK | E ;
// IF    → if ( E ) S
// FOR   → for ( E ; E ; E ) S
// BLOCK → { SLIST }
// SLIST → S SLIST | ε
// E     → T Ed
// Ed    → + T Ed | - T Ed | ε
// T     → F Td
// Td    → * F Td | / F Td | ε
// F     → id | ( E )

#include<stdio.h>
#include<string.h>
#include<ctype.h>

char input[100];
int i = 0;
int err = 0;

void S();
void IF();
void FOR();
void BLOCK();
void E();
void Ed();
void T();
void Td();
void F();

void F() {
    if(err) return;

    if(isalpha(input[i])) {
        while(isalnum(input[i])) i++;   // identifier
    }
    else if(input[i]=='(') {
        i++;
        E();

        if(input[i]==')')
            i++;
        else
            err=1;
    }
    else {
        err=1;
    }
}

void T() {
    if(err) return;
    F();
    Td();
}

void Td() {
    if(err) return;

    if(input[i]=='*') {
        i++;
        F();
        Td();
    }
    else if(input[i]=='/') {
        i++;
        F();
        Td();
    }
}

void Ed() {
    if(err) return;

    if(input[i]=='+') {
        i++;
        T();
        Ed();
    }
    else if(input[i]=='-') {
        i++;
        T();
        Ed();
    }
}

void E() {
    if(err) return;
    T();
    Ed();
}

void IF() {
    if(err) return;

    if(input[i]=='i' && input[i+1]=='f') {
        i += 2;

        if(input[i]=='(') {
            i++;
            E();

            if(input[i]==')') {
                i++;
                S();
            }
            else err=1;
        }
        else err=1;
    }
}

void FOR() {
    if(err) return;

    if(input[i]=='f' && input[i+1]=='o' && input[i+2]=='r') {
        i += 3;

        if(input[i]=='(') {
            i++;

            E();
            if(input[i]==';') {
                i++;

                E();
                if(input[i]==';') {
                    i++;

                    E();
                    if(input[i]==')') {
                        i++;
                        S();
                    }
                    else err=1;
                }
                else err=1;
            }
            else err=1;
        }
        else err=1;
    }
}

void BLOCK() {
    if(err) return;

    if(input[i]=='{') {
        i++;

        while(input[i] != '}' && input[i] != '\0') {
            S();
        }

        if(input[i]=='}')
            i++;
        else
            err=1;
    }
}

void S() {
    if(err) return;

    if(input[i]=='i' && input[i+1]=='f') {
        IF();
    }
    else if(input[i]=='f' && input[i+1]=='o' && input[i+2]=='r') {
        FOR();
    }
    else if(input[i]=='{') {
        BLOCK();
    }
    else {
        E();

        if(input[i]==';')
            i++;
        else
            err=1;
    }
}

int main() {

    printf("Enter input: ");
    scanf("%s", input);

    S();

    if(i==strlen(input) && err==0)
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");

    return 0;
}
