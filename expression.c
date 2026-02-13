//Parsing Grammar - Only Arithmetic Expression
//EXPR  → TERM EXPR'
//EXPR' → + TERM EXPR' | - TERM EXPR' | ε
//TERM  → FACTOR TERM'
//TERM' → * FACTOR TERM' | / FACTOR TERM' | ε
//FACTOR→ id | num | ( EXPR )
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
char input[100];
int i=0;
int err=0;
void F();
void T();
void Td();
void Ed();
void E();
void Td() {
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
	return;
}
void F() {
	if(input[i]=='(') {
		i++;
		E();
		if(input[i]==')') {
			i++;
		}
		else {
			err=1;
		}
		return;
	}
	else if(isalpha(input[i])) {
		i++;
		return;
	}
	else if(isalnum(input[i])) {
		i++;
		return;
	}
	else {
		err=1;
	}
	return;
}
void Ed() {
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

	return;
}
void T() {
	F();
	Td();

}
void E() {
	T();
	Ed();
}
int main() {
	scanf("%s",input);
	E();
	int l=strlen(input);
	if(i==l&&err==0) {
		printf("Parsing Sucessful");
	}
	else {
		printf("Parsing Failed");
	}
}