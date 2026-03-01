// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>
// #include <stdlib.h>

// #define MAX_PROD 50
// #define MAX_SYMBOLS 50
// #define MAX_ITEMS 200
// #define MAX_STATES 100

// typedef struct {
//     char lhs;
//     char rhs[20];
// } Production;

// typedef struct {
//     int prod_no;
//     int dot_pos;
// } Item;

// typedef struct {
//     Item items[MAX_ITEMS];
//     int count;
// } State;

// Production prod[MAX_PROD];
// State states[MAX_STATES];

// int prod_count = 0;
// int state_count = 0;

// char terminals[MAX_SYMBOLS];
// char nonterminals[MAX_SYMBOLS];
// int t_count = 0, nt_count = 0;

// char FOLLOW[256][MAX_SYMBOLS];
// char ACTION[MAX_STATES][256][20];
// int GOTO_TABLE[MAX_STATES][256];



// void init_tables() {
//     memset(FOLLOW, 0, sizeof(FOLLOW));
//     memset(ACTION, 0, sizeof(ACTION));
//     for(int i=0;i<MAX_STATES;i++)
//         for(int j=0;j<256;j++)
//             GOTO_TABLE[i][j] = -1;
// }

// void add_symbol(char *arr, int *count, char sym) {
//     for(int i=0;i<*count;i++)
//         if(arr[i]==sym) return;
//     arr[(*count)++] = sym;
// }



// void read_grammar() {

//     FILE *fp = fopen("grammar.txt", "r");
//     if(fp == NULL) {
//         printf("Error opening grammar.txt\n");
//         exit(1);
//     }

//     printf("\n--- Reading Grammar From File ---\n");

//     char line[100];

    
//     do {
//         if(!fgets(line, sizeof(line), fp)) {
//             printf("Invalid file format\n");
//             exit(1);
//         }
//         line[strcspn(line,"\n")] = 0;
//     } while(strlen(line) == 0);

//     prod_count = atoi(line);
//     printf("Number of productions: %d\n", prod_count);

//     for(int i=0;i<prod_count;i++) {

//         // Skip blank lines
//         do {
//             if(!fgets(line, sizeof(line), fp)) {
//                 printf("Unexpected end of file\n");
//                 exit(1);
//             }
//             line[strcspn(line,"\n")] = 0;
//         } while(strlen(line) == 0);

//         printf("Production read: %s\n", line);

//         char lhs;
//         char rhs[20];

//         if(sscanf(line, " %c -> %s", &lhs, rhs) != 2 &&
//            sscanf(line, " %c->%s", &lhs, rhs) != 2) {
//             printf("Invalid format: %s\n", line);
//             exit(1);
//         }

//         prod[i].lhs = lhs;
//         strcpy(prod[i].rhs, rhs);

//         add_symbol(nonterminals, &nt_count, lhs);

//         for(int j=0; rhs[j]; j++) {
//             if(isupper(rhs[j]))
//                 add_symbol(nonterminals, &nt_count, rhs[j]);
//             else
//                 add_symbol(terminals, &t_count, rhs[j]);
//         }
//     }

//     add_symbol(terminals, &t_count, '$');

//     fclose(fp);

//     printf("--- Grammar Loaded Successfully ---\n\n");
// }



// void augment_grammar() {

//     for(int i=prod_count;i>0;i--)
//         prod[i] = prod[i-1];

//     prod[0].lhs = 'Z';
//     prod[0].rhs[0] = prod[1].lhs;
//     prod[0].rhs[1] = '\0';

//     add_symbol(nonterminals, &nt_count, 'Z');
//     prod_count++;
// }



// void compute_FOLLOW() {

//     FOLLOW[prod[0].rhs[0]][0] = '$';
//     FOLLOW[prod[0].rhs[0]][1] = '\0';

//     int changed = 1;

//     while(changed) {
//         changed = 0;

//         for(int i=0;i<prod_count;i++) {

//             char A = prod[i].lhs;
//             char *rhs = prod[i].rhs;

//             for(int j=0; rhs[j]; j++) {

//                 if(isupper(rhs[j])) {

//                     if(rhs[j+1]) {

//                         char next = rhs[j+1];

//                         if(!isupper(next)) {
//                             if(!strchr(FOLLOW[rhs[j]], next)) {
//                                 int l = strlen(FOLLOW[rhs[j]]);
//                                 FOLLOW[rhs[j]][l] = next;
//                                 FOLLOW[rhs[j]][l+1] = '\0';
//                                 changed = 1;
//                             }
//                         }
//                     }
//                     else {
//                         for(int k=0; FOLLOW[A][k]; k++) {
//                             if(!strchr(FOLLOW[rhs[j]], FOLLOW[A][k])) {
//                                 int l = strlen(FOLLOW[rhs[j]]);
//                                 FOLLOW[rhs[j]][l] = FOLLOW[A][k];
//                                 FOLLOW[rhs[j]][l+1] = '\0';
//                                 changed = 1;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }



// int item_exists(State *s, int p, int d) {
//     for(int i=0;i<s->count;i++)
//         if(s->items[i].prod_no==p && s->items[i].dot_pos==d)
//             return 1;
//     return 0;
// }

// void closure(State *s) {

//     int changed = 1;

//     while(changed) {
//         changed = 0;

//         for(int i=0;i<s->count;i++) {

//             int p = s->items[i].prod_no;
//             int d = s->items[i].dot_pos;

//             if(d < strlen(prod[p].rhs)) {

//                 char sym = prod[p].rhs[d];

//                 if(isupper(sym)) {

//                     for(int j=0;j<prod_count;j++) {
//                         if(prod[j].lhs == sym) {

//                             if(!item_exists(s,j,0)) {
//                                 s->items[s->count].prod_no = j;
//                                 s->items[s->count].dot_pos = 0;
//                                 s->count++;
//                                 changed = 1;
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }


// void goto_state(State *from, State *to, char sym) {

//     to->count = 0;

//     for(int i=0;i<from->count;i++) {

//         int p = from->items[i].prod_no;
//         int d = from->items[i].dot_pos;

//         if(d < strlen(prod[p].rhs) &&
//            prod[p].rhs[d] == sym) {

//             to->items[to->count].prod_no = p;
//             to->items[to->count].dot_pos = d+1;
//             to->count++;
//         }
//     }

//     closure(to);
// }



// int same_state(State *a, State *b) {

//     if(a->count != b->count) return 0;

//     for(int i=0;i<a->count;i++) {

//         int found = 0;

//         for(int j=0;j<b->count;j++)
//             if(a->items[i].prod_no == b->items[j].prod_no &&
//                a->items[i].dot_pos == b->items[j].dot_pos)
//                 found = 1;

//         if(!found) return 0;
//     }

//     return 1;
// }



// void construct_states() {

//     states[0].count = 1;
//     states[0].items[0].prod_no = 0;
//     states[0].items[0].dot_pos = 0;

//     closure(&states[0]);
//     state_count = 1;

//     int i = 0;

//     while(i < state_count) {

//         for(int s=0; s<t_count + nt_count; s++) {

//             char sym = (s < t_count) ?
//                         terminals[s] :
//                         nonterminals[s - t_count];

//             State temp;
//             goto_state(&states[i], &temp, sym);

//             if(temp.count == 0) continue;

//             int exists = -1;

//             for(int j=0;j<state_count;j++)
//                 if(same_state(&states[j], &temp)) {
//                     exists = j;
//                     break;
//                 }

//             if(exists == -1)
//                 states[state_count++] = temp;
//         }

//         i++;
//     }
// }

// void print_states() {

//     printf("\nCanonical LR(0) Item Sets:\n\n");

//     for(int i = 0; i < state_count; i++) {

//         printf("I%d:\n", i);

//         for(int j = 0; j < states[i].count; j++) {

//             int p = states[i].items[j].prod_no;
//             int d = states[i].items[j].dot_pos;

//             printf("  %c -> ", prod[p].lhs);

//             for(int k = 0; k < strlen(prod[p].rhs); k++) {

//                 if(k == d)
//                     printf(".");

//                 printf("%c", prod[p].rhs[k]);
//             }

//             if(d == strlen(prod[p].rhs))
//                 printf(".");

//             printf("\n");
//         }

//         printf("\n");
//     }
// }



// void build_SLR_table() {

//     for(int i=0;i<state_count;i++) {

//         for(int j=0;j<states[i].count;j++) {

//             int p = states[i].items[j].prod_no;
//             int d = states[i].items[j].dot_pos;

//             if(d < strlen(prod[p].rhs)) {

//                 char sym = prod[p].rhs[d];

//                 State temp;
//                 goto_state(&states[i], &temp, sym);

//                 int next = -1;
//                 for(int k=0;k<state_count;k++)
//                     if(same_state(&states[k], &temp))
//                         next = k;

//                 if(!isupper(sym))
//                     sprintf(ACTION[i][sym], "s%d", next);
//                 else
//                     GOTO_TABLE[i][sym] = next;
//             }
//             else {

//                 if(p == 0)
//                     strcpy(ACTION[i]['$'], "acc");
//                 else {
//                     for(int f=0; FOLLOW[prod[p].lhs][f]; f++) {
//                         char a = FOLLOW[prod[p].lhs][f];
//                         sprintf(ACTION[i][a], "r%d", p);
//                     }
//                 }
//             }
//         }
//     }
// }



// void display_table() {

//     printf("\nSLR Parsing Table:\n\n");

//     printf("State\t");

//     for(int t=0;t<t_count;t++)
//         printf("%c\t", terminals[t]);

//     for(int nt=0;nt<nt_count;nt++)
//         if(nonterminals[nt] != 'Z')
//             printf("%c\t", nonterminals[nt]);

//     printf("\n");

//     for(int i=0;i<state_count;i++) {

//         printf("%d\t", i);

//         for(int t=0;t<t_count;t++)
//             printf("%s\t", ACTION[i][terminals[t]]);

//         for(int nt=0;nt<nt_count;nt++) {
//             if(nonterminals[nt]=='Z') continue;
//             int g = GOTO_TABLE[i][nonterminals[nt]];
//             if(g==-1) printf("\t");
//             else printf("%d\t", g);
//         }

//         printf("\n");
//     }
// }



// int main() {

//     init_tables();
//     read_grammar();
//     augment_grammar();
//     compute_FOLLOW();
//     construct_states();
//     print_states();
//     build_SLR_table();
//     display_table();

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 50
#define MAX_ITEMS 200
#define MAX_STATES 100
#define MAX_SYMBOLS 50



typedef struct {
    char head;
    char body[20];
} GrammarRule;

typedef struct {
    int ruleNo;
    int dotPos;
} LRItem;

typedef struct {
    LRItem items[MAX_ITEMS];
    int count;
} State;



GrammarRule rules[MAX_RULES];
State states[MAX_STATES];

int ruleCount = 0;
int stateCount = 0;

char terminals[MAX_SYMBOLS];
char nonTerminals[MAX_SYMBOLS];
int tCount = 0, ntCount = 0;

char FOLLOW[256][MAX_SYMBOLS];
char ACTION[MAX_STATES][256][20];
int GOTO_TABLE[MAX_STATES][256];



void initialize() {
    memset(FOLLOW, 0, sizeof(FOLLOW));
    memset(ACTION, 0, sizeof(ACTION));

    for(int i=0;i<MAX_STATES;i++)
        for(int j=0;j<256;j++)
            GOTO_TABLE[i][j] = -1;
}

void addSymbol(char arr[], int *size, char ch) {
    for(int i=0;i<*size;i++)
        if(arr[i]==ch) return;
    arr[(*size)++] = ch;
}



void readGrammar() {

    FILE *fp = fopen("grammar.txt","r");
    if(!fp){
        printf("Error opening grammar.txt\n");
        exit(1);
    }

    char line[100];

    do{
        fgets(line,sizeof(line),fp);
        line[strcspn(line,"\n")] = 0;
    }while(strlen(line)==0);

    ruleCount = atoi(line);

    for(int i=0;i<ruleCount;i++){

        do{
            fgets(line,sizeof(line),fp);
            line[strcspn(line,"\n")] = 0;
        }while(strlen(line)==0);

        char L;
        char R[20];

        sscanf(line," %c -> %s",&L,R);

        rules[i].head = L;
        strcpy(rules[i].body,R);

        addSymbol(nonTerminals,&ntCount,L);

        for(int j=0;R[j];j++){
            if(isupper(R[j]))
                addSymbol(nonTerminals,&ntCount,R[j]);
            else
                addSymbol(terminals,&tCount,R[j]);
        }
    }

    addSymbol(terminals,&tCount,'$');
    fclose(fp);
}



void augmentGrammar() {

    for(int i=ruleCount;i>0;i--)
        rules[i] = rules[i-1];

    rules[0].head = 'Z';
    rules[0].body[0] = rules[1].head;
    rules[0].body[1] = '\0';

    addSymbol(nonTerminals,&ntCount,'Z');
    ruleCount++;
}



void computeFOLLOW() {

    FOLLOW[rules[0].body[0]][0] = '$';
    FOLLOW[rules[0].body[0]][1] = '\0';

    int changed;

    do{
        changed = 0;

        for(int i=0;i<ruleCount;i++){

            char A = rules[i].head;
            char *rhs = rules[i].body;

            for(int j=0;rhs[j];j++){

                if(isupper(rhs[j])){

                    if(rhs[j+1]){
                        char next = rhs[j+1];

                        if(!isupper(next)){
                            if(!strchr(FOLLOW[rhs[j]],next)){
                                int len=strlen(FOLLOW[rhs[j]]);
                                FOLLOW[rhs[j]][len]=next;
                                FOLLOW[rhs[j]][len+1]='\0';
                                changed=1;
                            }
                        }
                    }
                    else{
                        for(int k=0;FOLLOW[A][k];k++){
                            if(!strchr(FOLLOW[rhs[j]],FOLLOW[A][k])){
                                int len=strlen(FOLLOW[rhs[j]]);
                                FOLLOW[rhs[j]][len]=FOLLOW[A][k];
                                FOLLOW[rhs[j]][len+1]='\0';
                                changed=1;
                            }
                        }
                    }
                }
            }
        }

    }while(changed);
}



int exists(State *s,int r,int d){
    for(int i=0;i<s->count;i++)
        if(s->items[i].ruleNo==r &&
           s->items[i].dotPos==d)
            return 1;
    return 0;
}

void closure(State *s){

    int change=1;

    while(change){
        change=0;

        for(int i=0;i<s->count;i++){

            int r=s->items[i].ruleNo;
            int d=s->items[i].dotPos;

            if(d<strlen(rules[r].body)){

                char sym=rules[r].body[d];

                if(isupper(sym)){
                    for(int j=0;j<ruleCount;j++){
                        if(rules[j].head==sym &&
                           !exists(s,j,0)){

                            s->items[s->count].ruleNo=j;
                            s->items[s->count].dotPos=0;
                            s->count++;
                            change=1;
                        }
                    }
                }
            }
        }
    }
}

void gotoState(State *from,State *to,char sym){

    to->count=0;

    for(int i=0;i<from->count;i++){

        int r=from->items[i].ruleNo;
        int d=from->items[i].dotPos;

        if(d<strlen(rules[r].body) &&
           rules[r].body[d]==sym){

            to->items[to->count].ruleNo=r;
            to->items[to->count].dotPos=d+1;
            to->count++;
        }
    }

    closure(to);
}

int same(State *a,State *b){

    if(a->count!=b->count) return 0;

    for(int i=0;i<a->count;i++){
        int found=0;
        for(int j=0;j<b->count;j++)
            if(a->items[i].ruleNo==b->items[j].ruleNo &&
               a->items[i].dotPos==b->items[j].dotPos)
                found=1;

        if(!found) return 0;
    }

    return 1;
}

void constructStates(){

    states[0].count=1;
    states[0].items[0].ruleNo=0;
    states[0].items[0].dotPos=0;

    closure(&states[0]);
    stateCount=1;

    for(int i=0;i<stateCount;i++){

        for(int s=0;s<tCount+ntCount;s++){

            char sym=(s<tCount)?terminals[s]
                               :nonTerminals[s-tCount];

            State temp;
            gotoState(&states[i],&temp,sym);

            if(temp.count==0) continue;

            int found=-1;

            for(int j=0;j<stateCount;j++)
                if(same(&states[j],&temp)){
                    found=j;
                    break;
                }

            if(found==-1)
                states[stateCount++]=temp;
        }
    }
}

void printStates(){

    printf("\nCanonical LR(0) Item Sets:\n\n");

    for(int i=0;i<stateCount;i++){

        printf("I%d:\n",i);

        for(int j=0;j<states[i].count;j++){

            int r=states[i].items[j].ruleNo;
            int d=states[i].items[j].dotPos;

            printf("  %c -> ",rules[r].head);

            int len=strlen(rules[r].body);

            for(int k=0;k<len;k++){
                if(k==d) printf(".");
                printf("%c",rules[r].body[k]);
            }

            if(d==len) printf(".");
            printf("\n");
        }
        printf("\n");
    }
}


void buildSLRTable(){

    for(int i=0;i<stateCount;i++){

        for(int j=0;j<states[i].count;j++){

            int r=states[i].items[j].ruleNo;
            int d=states[i].items[j].dotPos;

            if(d<strlen(rules[r].body)){

                char sym=rules[r].body[d];

                State temp;
                gotoState(&states[i],&temp,sym);

                int next=-1;

                for(int k=0;k<stateCount;k++)
                    if(same(&states[k],&temp))
                        next=k;

                if(!isupper(sym))
                    sprintf(ACTION[i][sym],"s%d",next);
                else
                    GOTO_TABLE[i][sym]=next;
            }
            else{
                if(r==0)
                    strcpy(ACTION[i]['$'],"acc");
                else{
                    for(int f=0;FOLLOW[rules[r].head][f];f++){
                        char a=FOLLOW[rules[r].head][f];
                        sprintf(ACTION[i][a],"r%d",r);
                    }
                }
            }
        }
    }
}

void printTable(){

    printf("\nSLR Parsing Table:\n\n");

    printf("State\t");

    for(int i=0;i<tCount;i++)
        printf("%c\t",terminals[i]);

    for(int i=0;i<ntCount;i++)
        if(nonTerminals[i]!='Z')
            printf("%c\t",nonTerminals[i]);

    printf("\n");

    for(int i=0;i<stateCount;i++){

        printf("%d\t",i);

        for(int t=0;t<tCount;t++)
            printf("%s\t",ACTION[i][terminals[t]]);

        for(int nt=0;nt<ntCount;nt++){
            if(nonTerminals[nt]=='Z') continue;
            int g=GOTO_TABLE[i][nonTerminals[nt]];
            if(g==-1) printf("\t");
            else printf("%d\t",g);
        }

        printf("\n");
    }
}


int main(){

    initialize();
    readGrammar();
    augmentGrammar();
    computeFOLLOW();
    constructStates();
    printStates();
    buildSLRTable();
    printTable();

    return 0;
}