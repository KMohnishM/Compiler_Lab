// E → E1 + T E.val = E1.val + T.val
// E → T E.val = T.val
// T → T1 * F T.val = T1.val * F.val
// T → F T.val = F.val
// F → ( E ) F.val = E.val
// F → id

F.val = id.lexval
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char ACTION[12][6][10];
int GOTO[12][3];

char terminals[] = {'i','+','*','(',')','$'};
char nonterminals[] = {'E','T','F'};

int stack[100], top=-1;
int valstack[100], vtop=-1;

int getTerminalIndex(char c){
    for(int i=0;i<6;i++)
        if(terminals[i]==c)
            return i;
    return -1;
}

int getNonTerminalIndex(char c){
    for(int i=0;i<3;i++)
        if(nonterminals[i]==c)
            return i;
    return -1;
}

void push(int x){ stack[++top]=x; }
int pop(){ return stack[top--]; }

void vpush(int x){ valstack[++vtop]=x; }
int vpop(){ return valstack[vtop--]; }

void initTable(){

    strcpy(ACTION[0][0],"s5");
    strcpy(ACTION[0][3],"s4");

    strcpy(ACTION[1][1],"s6");
    strcpy(ACTION[1][5],"acc");

    strcpy(ACTION[2][1],"r2");
    strcpy(ACTION[2][2],"s7");
    strcpy(ACTION[2][4],"r2");
    strcpy(ACTION[2][5],"r2");

    strcpy(ACTION[3][1],"r4");
    strcpy(ACTION[3][2],"r4");
    strcpy(ACTION[3][4],"r4");
    strcpy(ACTION[3][5],"r4");

    strcpy(ACTION[4][0],"s5");
    strcpy(ACTION[4][3],"s4");

    strcpy(ACTION[5][1],"r6");
    strcpy(ACTION[5][2],"r6");
    strcpy(ACTION[5][4],"r6");
    strcpy(ACTION[5][5],"r6");

    strcpy(ACTION[6][0],"s5");
    strcpy(ACTION[6][3],"s4");

    strcpy(ACTION[7][0],"s5");
    strcpy(ACTION[7][3],"s4");

    strcpy(ACTION[8][1],"s6");
    strcpy(ACTION[8][4],"s11");

    strcpy(ACTION[9][1],"r1");
    strcpy(ACTION[9][2],"s7");
    strcpy(ACTION[9][4],"r1");
    strcpy(ACTION[9][5],"r1");

    strcpy(ACTION[10][1],"r3");
    strcpy(ACTION[10][2],"r3");
    strcpy(ACTION[10][4],"r3");
    strcpy(ACTION[10][5],"r3");

    strcpy(ACTION[11][1],"r5");
    strcpy(ACTION[11][2],"r5");
    strcpy(ACTION[11][4],"r5");
    strcpy(ACTION[11][5],"r5");


    GOTO[0][0]=1;
    GOTO[0][1]=2;
    GOTO[0][2]=3;

    GOTO[4][0]=8;
    GOTO[4][1]=2;
    GOTO[4][2]=3;

    GOTO[6][1]=9;
    GOTO[6][2]=3;

    GOTO[7][2]=10;
}

void parse(char input[]){

    int ip = 0;
    push(0);

    while(1){

        int state = stack[top];
        char symbol = input[ip];

        char token = symbol;

        if(isdigit(symbol))
            token='i';

        int tid = getTerminalIndex(token);

        if(tid==-1){
            printf("Syntax Error\n");
            return;
        }

        char action[10];
        strcpy(action,ACTION[state][tid]);

        if(strlen(action)==0){
            printf("Syntax Error\n");
            return;
        }

        if(action[0]=='s'){

            int next = atoi(action+1);
            push(next);

            if(token=='i')
                vpush(symbol-'0');

            ip++;
        }

        else if(action[0]=='r'){

            int r = atoi(action+1);
            int val;

            switch(r){

                case 1: {
                    int t=vpop();
                    int e=vpop();
                    val=e+t;
                    pop();pop();pop();
                    break;
                }

                case 2: {
                    val=vpop();
                    pop();
                    break;
                }

                case 3: {
                    int f=vpop();
                    int t=vpop();
                    val=t*f;
                    pop();pop();pop();
                    break;
                }

                case 4: {
                    val=vpop();
                    pop();
                    break;
                }

                case 5: {
                    val=vpop();
                    pop();pop();pop();
                    break;
                }

                case 6: {
                    val=vpop();
                    pop();
                    break;
                }
            }

            int state2 = stack[top];
            char lhs;

            if(r==1||r==2) lhs='E';
            else if(r==3||r==4) lhs='T';
            else lhs='F';

            int gid=getNonTerminalIndex(lhs);

            push(GOTO[state2][gid]);
            vpush(val);
        }

        else if(strcmp(action,"acc")==0){

            printf("Accepted\n");
            printf("Value = %d\n",valstack[vtop]);
            return;
        }
    }
}

int main(){

    initTable();

    char input[100];

    printf("Enter expression: ");
    scanf("%s",input);

    strcat(input,"$");

    parse(input);

    return 0;
}   
