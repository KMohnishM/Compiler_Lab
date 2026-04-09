// // #include <stdio.h>
// // #include <string.h>
// // #include <ctype.h>

// // #define MAX_ITEMS 10
// // #define MAX_STATES 10

// // typedef struct {
// //     char head;
// //     char body[10];
// // } Rule;

// // typedef struct {
// //     int rule;
// //     int dot;
// // } Item;

// // typedef struct {
// //     Item items[MAX_ITEMS];
// //     int count;
// // } State;

// // Rule rules[] = {
// //     {'Z',"S"},
// //     {'S',"CC"},
// //     {'C',"cC"},
// //     {'C',"d"}
// // };

// // int ruleCount = 4;

// // /* FOLLOW sets */
// // char FOLLOW[256][10];

// // /* Hardcoded LR(0) states */
// // State states[MAX_STATES] = {
// //     {{{0,0},{1,0},{2,0},{3,0}},4},     // I0
// //     {{{0,1}},1},                       // I1
// //     {{{1,1},{2,0},{3,0}},3},           // I2
// //     {{{2,1},{2,0},{3,0}},3},           // I3
// //     {{{3,1}},1},                       // I4
// //     {{{1,2}},1},                       // I5
// //     {{{2,2}},1}                        // I6
// // };

// // int stateCount = 7;

// // /* transitions */
// // int transitions[MAX_STATES][256];

// // char ACTION[MAX_STATES][256][10];
// // int GOTO_TABLE[MAX_STATES][256];
// // int GOTO[MAX_STATES][256];
// // void initTransitions() {

// //     memset(transitions,-1,sizeof(transitions));

// //     transitions[0]['S']=1;
// //     transitions[0]['C']=2;
// //     transitions[0]['c']=3;
// //     transitions[0]['d']=4;

// //     transitions[2]['C']=5;
// //     transitions[2]['c']=3;
// //     transitions[2]['d']=4;

// //     transitions[3]['C']=6;
// //     transitions[3]['c']=3;
// //     transitions[3]['d']=4;
// // }

// // void initFOLLOW(){

// //     strcpy(FOLLOW['S'],"$");
// //     strcpy(FOLLOW['C'],"cd$");
// // }

// // void buildTable(){

// //     for(int i=0;i<stateCount;i++){

// //         for(int j=0;j<states[i].count;j++){

// //             int r = states[i].items[j].rule;
// //             int d = states[i].items[j].dot;
// //             int len = strlen(rules[r].body);

// //             if(d < len){

// //                 char sym = rules[r].body[d];
// //                 int next = transitions[i][sym];

// //                 if(next != -1){

// //                     if(!isupper(sym))
// //                         sprintf(ACTION[i][sym],"s%d",next);
// //                     else
// //                         GOTO_TABLE[i][sym] = next;
// //                 }
// //             }

// //             else{

// //                 if(r == 0){
// //                     strcpy(ACTION[i]['$'],"acc");
// //                 }

// //                 else{

// //                     for(int k=0; FOLLOW[rules[r].head][k]; k++){

// //                         char a = FOLLOW[rules[r].head][k];
// //                         sprintf(ACTION[i][a],"r%d",r);
// //                     }
// //                 }
// //             }
// //         }
// //     }
// // }

// // void printTable(){

// //     printf("\nSLR Parsing Table\n\n");

// //     printf("State\tc\td\t$\tS\tC\n");

// //     for(int i=0;i<stateCount;i++){

// //         printf("%d\t",i);

// //         printf("%s\t",ACTION[i]['c']);
// //         printf("%s\t",ACTION[i]['d']);
// //         printf("%s\t",ACTION[i]['$']);

// //         if(GOTO_TABLE[i]['S'])
// //             printf("%d\t",GOTO_TABLE[i]['S']);
// //         else
// //             printf("\t");

// //         if(GOTO_TABLE[i]['C'])
// //             printf("%d",GOTO_TABLE[i]['C']);

// //         printf("\n");
// //     }
// // }
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

char ACTION[12][6][10];
int GOTO[12][3];

char terminals[] = {'i','+','*','(',')','$'};
char nonterminals[] = {'E','T','F'};


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

int getTerminalIndex(char c){
    for(int i=0;i<6;i++)
        if(terminals[i]==c)
            return i;
    return -1;
}

int getnt(char c){
    for(int i=0;i<3;i++)
        if(nonterminals[i]==c)
            return i;
    return -1;
}

char input[100];
int top=-1;
int stack[100];
void parse(){
   stack[++top]=0;
   int ip=0;
   while(1){
     int topsym=stack[top];
     int curr=input[ip];

     char action[100];
     int pr=getTerminalIndex(curr);
     strcpy(action,ACTION[topsym][pr]);
     printf("State:%d  Symbol:%c Action:%s\n",topsym,curr,action);

     if(action[0]=='s'){
        int next=atoi(action+1);
        stack[++top]=curr;
        stack[++top]=next;
        ip++;
     }
     else if(action[0]=='r'){
        int r=atoi(action+1);
        int len;
        if(r==1||r==3||r==5){
            len=3;
        }
        else{
            len=1;
        }
        top-=2*len;
        int state2=stack[top];
        char lhs;
        if(r==1||r==2)lhs='E';
        else if(r==3||r==4)lhs='T';
        else lhs='F';
        int getid=getnt(lhs);
        stack[++top]=lhs;
        stack[++top]=GOTO[state2][getid];

     }
     else if(strcmp(action,"acc")==0){
        printf("Accepted");
        return;
     }
     else{
        printf("err");
        return;
     }

    }

}

int main(){
    initTable();
    scanf("%s",input);
    strcat(input,"$");
    parse();
}
