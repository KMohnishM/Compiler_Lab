#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct{
char res[10],op1[10],op2[10],op;
int isBinary,isFolded;
} TAC;

TAC arr[100];
int n=0;

int isnum(char *s){
    for(int i=0;s[i];i++){
        if(!isdigit(s[i]))return 0;
    }
    return 1;
}
int val(char* s){
    return atoi(s);
}

