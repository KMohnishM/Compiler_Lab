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

/* 🔹 PLACE STACK */
char placestack[100][10];
int ptop = -1;

/* 🔹 TEMP GENERATOR */
int tempCount = 1;

char* newtemp(){
    static char temp[10];
    sprintf(temp, "t%d", tempCount++);
    return temp;
}

void ppush(char *s){
    strcpy(placestack[++ptop], s);
}

char* ppop(){
    return placestack[ptop--];
}

/* 🔹 STACK FUNCTIONS */
void push(int x){ stack[++top]=x; }
int pop(){ return stack[top--]; }

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

/* 🔹 INIT SLR TABLE (same structure, extended for - and /) */
void initTable(){

    strcpy(ACTION[0][0],"s5");
    strcpy(ACTION[0][3],"s4");

    strcpy(ACTION[1][1],"s6"); // +
    strcpy(ACTION[1][5],"acc");

    strcpy(ACTION[2][1],"r3");
    strcpy(ACTION[2][2],"s7");
    strcpy(ACTION[2][4],"r3");
    strcpy(ACTION[2][5],"r3");

    strcpy(ACTION[3][1],"r6");
    strcpy(ACTION[3][2],"r6");
    strcpy(ACTION[3][4],"r6");
    strcpy(ACTION[3][5],"r6");

    strcpy(ACTION[4][0],"s5");
    strcpy(ACTION[4][3],"s4");

    strcpy(ACTION[5][1],"r7");
    strcpy(ACTION[5][2],"r7");
    strcpy(ACTION[5][4],"r7");
    strcpy(ACTION[5][5],"r7");

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

    strcpy(ACTION[10][1],"r4");
    strcpy(ACTION[10][2],"r4");
    strcpy(ACTION[10][4],"r4");
    strcpy(ACTION[10][5],"r4");

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

/* 🔥 PARSER + TAC */
void parse(char input[]){

    int ip = 0;
    push(0);

    while(1){

        int state = stack[top];
        char symbol = input[ip];

        char token = symbol;

        if(isalpha(symbol))
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

        /* 🔹 SHIFT */
        if(action[0]=='s'){

            int next = atoi(action+1);
            push(next);

            if(token=='i'){
                char temp[10];
                temp[0] = symbol;
                temp[1] = '\0';
                ppush(temp);
            }

            ip++;
        }

        /* 🔹 REDUCE */
        else if(action[0]=='r'){

            int r = atoi(action+1);
            char temp[10];

            switch(r){

                /* E → E + T */
                case 1: {
                    char t[10], e[10];
                    strcpy(t, ppop());
                    strcpy(e, ppop());

                    strcpy(temp, newtemp());
                    printf("%s = %s + %s\n", temp, e, t);

                    pop(); pop(); pop();
                    ppush(temp);
                    break;
                }

                /* E → E - T */
                case 2: {
                    char t[10], e[10];
                    strcpy(t, ppop());
                    strcpy(e, ppop());

                    strcpy(temp, newtemp());
                    printf("%s = %s - %s\n", temp, e, t);

                    pop(); pop(); pop();
                    ppush(temp);
                    break;
                }

                /* E → T */
                case 3: {
                    char t[10];
                    strcpy(t, ppop());
                    pop();
                    ppush(t);
                    break;
                }

                /* T → T * F */
                case 4: {
                    char f[10], t1[10];
                    strcpy(f, ppop());
                    strcpy(t1, ppop());

                    strcpy(temp, newtemp());
                    printf("%s = %s * %s\n", temp, t1, f);

                    pop(); pop(); pop();
                    ppush(temp);
                    break;
                }

                /* T → T / F */
                case 5: {
                    char f[10], t1[10];
                    strcpy(f, ppop());
                    strcpy(t1, ppop());

                    strcpy(temp, newtemp());
                    printf("%s = %s / %s\n", temp, t1, f);

                    pop(); pop(); pop();
                    ppush(temp);
                    break;
                }

                /* T → F */
                case 6: {
                    char f[10];
                    strcpy(f, ppop());
                    pop();
                    ppush(f);
                    break;
                }

                /* F → id */
                case 7: {
                    char id[10];
                    strcpy(id, ppop());
                    pop();
                    ppush(id);
                    break;
                }
            }

            int state2 = stack[top];
            char lhs;

            if(r<=3) lhs='E';
            else if(r<=6) lhs='T';
            else lhs='F';

            int gid=getNonTerminalIndex(lhs);

            push(GOTO[state2][gid]);
        }

        /* 🔹 ACCEPT */
        else if(strcmp(action,"acc")==0){

            printf("Accepted\n");
            printf("Final Result in: %s\n", placestack[ptop]);
            return;
        }
    }
}

/* 🔹 MAIN */
int main(){

    initTable();

    char input[100];

    printf("Enter expression: ");
    scanf("%s",input);

    strcat(input,"$");

    parse(input);

    return 0;
}