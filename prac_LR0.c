#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 10
#define MAX_STATES 10

typedef struct {
    char head;
    char body[10];
} Rule;

typedef struct {
    int rule;
    int dot;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int count;
} State;

Rule rules[] = {
    {'Z',"S"},
    {'S',"CC"},
    {'C',"cC"},
    {'C',"d"}
};

int ruleCount = 4;

/* FOLLOW sets */
char FOLLOW[256][10];

/* Hardcoded LR(0) states */
State states[MAX_STATES] = {
    {{{0,0},{1,0},{2,0},{3,0}},4},     // I0
    {{{0,1}},1},                       // I1
    {{{1,1},{2,0},{3,0}},3},           // I2
    {{{2,1},{2,0},{3,0}},3},           // I3
    {{{3,1}},1},                       // I4
    {{{1,2}},1},                       // I5
    {{{2,2}},1}                        // I6
};

int stateCount = 7;

/* transitions */
int transitions[MAX_STATES][256];

char ACTION[MAX_STATES][256][10];
int GOTO_TABLE[MAX_STATES][256];

void initTransitions() {

    memset(transitions,-1,sizeof(transitions));

    transitions[0]['S']=1;
    transitions[0]['C']=2;
    transitions[0]['c']=3;
    transitions[0]['d']=4;

    transitions[2]['C']=5;
    transitions[2]['c']=3;
    transitions[2]['d']=4;

    transitions[3]['C']=6;
    transitions[3]['c']=3;
    transitions[3]['d']=4;
}

void initFOLLOW(){

    strcpy(FOLLOW['S'],"$");
    strcpy(FOLLOW['C'],"cd$");
}

void buildTable(){

    for(int i=0;i<stateCount;i++){

        for(int j=0;j<states[i].count;j++){

            int r = states[i].items[j].rule;
            int d = states[i].items[j].dot;
            int len = strlen(rules[r].body);

            if(d < len){

                char sym = rules[r].body[d];
                int next = transitions[i][sym];

                if(next != -1){

                    if(!isupper(sym))
                        sprintf(ACTION[i][sym],"s%d",next);
                    else
                        GOTO_TABLE[i][sym] = next;
                }
            }

            else{

                if(r == 0){
                    strcpy(ACTION[i]['$'],"acc");
                }

                else{

                    for(int k=0; FOLLOW[rules[r].head][k]; k++){

                        char a = FOLLOW[rules[r].head][k];
                        sprintf(ACTION[i][a],"r%d",r);
                    }
                }
            }
        }
    }
}

void printTable(){

    printf("\nSLR Parsing Table\n\n");

    printf("State\tc\td\t$\tS\tC\n");

    for(int i=0;i<stateCount;i++){

        printf("%d\t",i);

        printf("%s\t",ACTION[i]['c']);
        printf("%s\t",ACTION[i]['d']);
        printf("%s\t",ACTION[i]['$']);

        if(GOTO_TABLE[i]['S'])
            printf("%d\t",GOTO_TABLE[i]['S']);
        else
            printf("\t");

        if(GOTO_TABLE[i]['C'])
            printf("%d",GOTO_TABLE[i]['C']);

        printf("\n");
    }
}

void parse(char input[]){

    int stack[100];
    int top = 0;

    stack[top] = 0;

    int ip = 0;

    printf("\nParsing Steps\n\n");

    while(1){

        int state = stack[top];
        char sym = input[ip];

        char action[10];
        strcpy(action, ACTION[state][sym]);

        printf("State:%d  Symbol:%c  Action:%s\n",state,sym,action);

        if(action[0]=='s'){

            int next = action[1]-'0';

            stack[++top] = sym;
            stack[++top] = next;

            ip++;
        }

        else if(action[0]=='r'){

            int r = action[1]-'0';
            int len = strlen(rules[r].body);

            top -= 2*len;

            int state2 = stack[top];

            stack[++top] = rules[r].head;
            stack[++top] = GOTO_TABLE[state2][rules[r].head];
        }

        else if(strcmp(action,"acc")==0){

            printf("\nString Accepted\n");
            return;
        }

        else{

            printf("\nParsing Error\n");
            return;
        }
    }
}

int main(){

    initFOLLOW();
    initTransitions();
    buildTable();
    printTable();

    char input[100];

    printf("\nEnter input string (end with $): ");
    scanf("%s",input);

    parse(input);

    return 0;
}