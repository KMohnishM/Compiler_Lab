//Parsing FOR Block  
//FOR   → for ( EXPR ; EXPR ; EXPR ) BLOCK
//BLOCK → { }
//EXPR  → TERM EXPR'
//EXPR' → + TERM EXPR' | - TERM EXPR' | ε
//TERM  → FACTOR TERM'
//TERM' → * FACTOR TERM' | / FACTOR TERM' | ε
//FACTOR→ id | num | ( EXPR )

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char input[100];
int i=0;
int err=0;
void E();
void Ed();
void T();
void Td();
void F();
void F() {
	if(isalpha(input[i])) {
		i++;
	}
	else if(isalnum(input[i])) {
		i++;
	}
	else if(input[i]=='(') {
		i++;
		E();
		if(input[i]==')') {
			i++;
		}

	}
	else {
		err=1;
	}
}
void T() {
	F();
	Td();
}
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
	else {
		return;
	}
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
	else {
		return;
	}
}
void E() {
	T();
	Ed();
}
void BLOCK() {
	if(input[i]=='{') {
		i++;
		if(input[i]=='}') {
			i++;
		}
	}
}
void FOR() {
	if(input[i]=='f') {
		i++;
		if(input[i]=='o') {
			i++;
			if(input[i]=='r') {
				i++;
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
								BLOCK();
							}
						}
					}
				}
			}
		}
	}
};

int main() {
	scanf("%s",input);
	FOR();
	if(i==strlen(input)&&err==0) {
		printf("Valid for-loop syntax");
	}
	else {
		printf("Invalid for-loop syntax");
	}
}