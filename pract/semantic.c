#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char term[] = {'i','+','*','(',')','$'};
char nont[] = {'E','T','F'};

int nt=3,t=6;
char input[1000];
int st[100];
int top=-1;
int valst[100];
int vtp=-1;

int GOTO[100][100];
char ACTION[100][100][100];

void push(char c){
    st[++top]=c;
}
int pop(){
    return st[top--];
}
void vpush(int a){
    valst[++vtp]=a;
}
int vpop(){
    return valst[vtp--];
}
int getnt(char c){
    for(int i=0;i<nt;i++){
        if(nont[i]==c){return i;}

    }
    return -1;
}
int gett(char c){
    for(int i=0;i<t;i++){
        if(term[i]==c)return i;
    }
    return -1;
}
void buildtable(){
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

void parse(){
   int ip=0;
   push(0);
   while(1){
       int topsy=st[top];
       char symbol=input[ip];
       char token=symbol;
       if(isdigit(symbol))
          token='i';  
       int tid=gett(token);
       if(tid==-1){
        printf("Err1");
        return;
       }
       char action[100];
       strcpy(action,ACTION[topsy][tid]);
       if(strlen(action)==0){
        printf("Err2");
        return;
       }
       if(action[0]=='s'){
          int next=atoi(action+1);
          push(next);
          if(token=='i'){
            vpush(symbol-'0');
          }
          ip++;
       }
       else if(action[0]=='r'){
        int r=atoi(action+1);
        int val;
        switch(r){
            case 1:{
                int t=vpop();
                int e=vpop();
                val=t+e;
                pop();pop();pop();break;
            }
            case 2:{
                val=vpop();
                pop(); break;
            }
            case 3:{
            int f=vpop();
            int t=vpop();
            val=t*f;
            pop();pop();pop();
            break;
            }
            case 4:{
                val=vpop();
                pop();break;
            }
            case 5:{
                val=vpop();
                pop();pop();pop();break;
            }
            case 6:{
             val=vpop();
             pop();
             break;
            }
        }
        int state2=st[top];
        char lhs;
        if(r==1||r==2){
            lhs='E';
        }
        else if(r==3||r==4){
            lhs='T';
        }
        else{
            lhs='F';
        }
        int gid=getnt(lhs);
        push(GOTO[state2][gid]);
        vpush(val);


       }
       else if(strcmp(action,"acc")==0){
         printf("Accepted");
         printf("Value = %d",vpop());
         return;
       }
   }
}

int main(){
   buildtable();
   scanf("%s",input);
   strcat(input,"$");
   parse();
}

