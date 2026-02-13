//Parsing For and If 
//S     → IF | FOR | BLOCK | E ;
//IF    → if ( E ) S
//FOR   → for IF ( E ; E ; E ) S
//BLOCK → { SLIST }
//SLIST → S SLIST | ε
//E     → T Ed
//Ed    → + T Ed | - T Ed | ε
//T     → F Td
//Td    → * F Td | / F Td | ε
//F     → id | ( E )

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
void IF();
void FOR();
void BLOCK();
void S();


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
		printf("%d\n",i);
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
void IF() {
	if(input[i]=='i') {
		i++;
		if(input[i]=='f') {
			i++;
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

}

void FOR() {

	if(input[i]=='f') {
		i++;
		if(input[i]=='o') {
			i++;
			if(input[i]=='r') {
				i++;
				IF();
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
						}
					}
				}
			}
		}
	}
};

void BLOCK() {
	if(input[i]=='{') {
		i++;
		while(input[i]!='}'&&input[i]!='\0') {
			S();
		}

		if(input[i]=='}') {
			i++;
		}
	}
}
void S() {
	if(input[i]=='i'&&input[i+1]=='f') {
		IF();
	}
	else if(input[i]=='f'&&input[i+1]=='o'&&input[i+2]=='r') {
		FOR();
	}
	else if(input[i]=='{') {
		BLOCK();
	}
	else {
		E();
		if(input[i]==';') {
			i++;
		}
	}
}
int main() {
	scanf("%s",input);
	S();
	if(i==strlen(input)&&err==0) {
		printf("Valid Expression");
	}
	else {
		printf("Invalid Expression");
	}
}