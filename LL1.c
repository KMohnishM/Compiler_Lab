#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char nonterminals[100];
char terminals[100];
char table[100][100][100];
char stack[100];
char inp[100];

int tp=-1;
int nonc,tc;

void push(char c) {
	stack[++tp]=c;
}
char pop() {
	return stack[tp--];
}
int getnt(char c) {
	for(int i=0; i<nonc; i++) {
		if(nonterminals[i]==c) {
			return i;
		}
	}
	return -1;
}
int gett(char c) {
	for(int i=0;i<tc;i++){
	          if(terminals[i]==c) return i;
	}
return -1;
}
void pristack() {
	for(int i=0; i<=tp; i++) {
		printf("%c",stack[i]);
	}
}
void parse() {
	int i=0;
	printf("\nStack\t\tInput\t\tAction\n");
	printf("\n");

	while(1) {
		pristack();
		printf("\t\t%s\t\t",inp+i);

		char topsy=stack[tp];
		char currentinput=inp[i];

		if(topsy=='$'&&currentinput=='$') {
			printf("Match and Accepted");
			return ;
		}
		if(getnt(topsy)==-1) {
			if(topsy==currentinput) {
				printf("Match");
				pop();
				i++;
			}
			else {
				printf("Error");
				return;
			}
		}
		else {
			int r=getnt(topsy);
			int c=gett(currentinput);

			if(r==-1||c==-1) {
				printf("Error");
				return;
			}
			if(strcmp(table[r][c],"-")==0) {
				printf("Error");
				return;
			}

			char production[100];
			strcpy(production,table[r][c]);
			printf("Apply %c -> %s \n",topsy,production);

			pop();

			if(strcmp(production,"e")!=0) {
				for(int i=strlen(production)-1; i>=0; i--) {
					push(production[i]);
				}
			}
		}
	}

}

int main() {
	scanf("%d",&nonc);
	for(int i=0; i<nonc; i++) {
		scanf(" %c",&nonterminals[i]);
	}
	scanf("%d",&tc);
	for(int i=0; i<tc; i++) {
		scanf(" %c",&terminals[i]);
	}
	for(int i=0; i<nonc; i++) {
		for(int j=0; j<tc; j++) {
		    printf("M[%c,%c]= ",nonterminals[i],terminals[j]);
			scanf("%s",table[i][j]);
		}
	}
	scanf("%s",inp);
	push('$');
	push(nonterminals[0]);
	parse();
	return 0;
}