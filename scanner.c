//Scanner 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char keyword[7][10]= {"if","else","void","int","float","include","stdio.h"};
int keywords=7;

int iskeyword(char* word) {
	for(int i=0; i<keywords; i++) {
		if(strcmp(keyword[i],word)==0) {
			return 1;
		}
	}
	return 0;
}

char identifiers[100][100];
int l=0;
int uniqueid=0;

int isuniqueiden(char* word) {
	for(int i=0; i<l; i++) {
		if (strcmp(identifiers[i],word)==0) {
			return 1;
		}
	}
	return 0;
}

int isSingleOp(char c) {
	char ops[] = "+-*/%=<>!";
	for(int i=0; ops[i] != '\0'; i++) {
		if(c == ops[i]) return 1;
	}
	return 0;
}

int main() {
	char input[100];
	FILE *fptr;
	fptr = fopen("code.c","r");

	int k=0;
	char ch;

	while((ch=getc(fptr)) != EOF) {
		input[k] = ch;
		k++;
	}
	input[k] = '\0';

	char word[100];
	int i = 0;
	char uniqueiden[100][100];

	while(input[i] != '\0') {

		if(isspace(input[i])) {
			i++;
			continue;
		}

		
		if(isalpha(input[i]) || input[i]=='_') {

			int j = 0;
			while(isalnum(input[i]) || input[i]=='.' || input[i]=='_') {
				word[j++] = input[i++];
			}
			word[j] = '\0';

			if(!iskeyword(word)) {
				strcpy(identifiers[l], word);
				printf("%s is identifier.\n", identifiers[l]);

				if(!isuniqueiden(word)) {
					strcpy(uniqueiden[uniqueid], word);
					uniqueid++;
				}

				l++;
			}
			continue;
		}

		
		if(isdigit(input[i])) {
			int j = 0;
			while(isdigit(input[i])) {
				word[j++] = input[i++];
			}
			word[j] = '\0';
			printf("%s is number.\n", word);
			continue;
		}

		
		if ((input[i] == '>' && input[i+1] == '=') ||
		        (input[i] == '<' && input[i+1] == '=') ||
		        (input[i] == '=' && input[i+1] == '=') ||
		        (input[i] == '!' && input[i+1] == '=') ||
		        (input[i] == '&' && input[i+1] == '&') ||
		        (input[i] == '|' && input[i+1] == '|')) {

			printf("%c%c is operator.\n", input[i], input[i+1]);
			i += 2;
			continue;
		}

		if (isSingleOp(input[i])) {
			printf("%c is operator.\n", input[i]);
			i++;
			continue;
		}

		i++;
	}

	printf("Number of unique identifiers: %d\n", uniqueid);
	for(int i=0; i<uniqueid; i++) {
		printf("%s is unique identifier.\n", uniqueiden[i]);
	}

	return 0;
}
