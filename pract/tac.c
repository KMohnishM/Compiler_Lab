// 1. E → E + T
// 2. E → E - T
// 3. E → T
// 4. T → T * F
// 5. T → T / F
// 6. T → F
// 7. F → i


#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int st[100];
int tp=-1;
char nont[]={'E','T','F'};
char term[]={'i','+','*','(',')','$'};
int getnt(char c){
    for(int i=0;i<3;i++){
        if(nont[i]==c){
            return i;
        }
    }
    return -1;
}
int gett(char c){
    for(int i=0;i<6;i++){
        if(term[i]==c){
            return i;
        }
    }
    return -1;
}
void push(char c){
  st[++tp]=c;
}
char pop(){
    return st[tp--];
}
int newt=0;
char* newtemp(){
    static char temp[100];
    sprintf(temp,"t%d",newt++);
    return temp; 
}

char placestack[100][100];
int ptop=-1;
void ppush(char* w){
    strcpy(placestack[++ptop],w);
}
char* ppop(){
    return placestack[ptop--];
}

char ACTION[12][6][10];
int GOTO[12][3];
void initTable(){

    strcpy(ACTION[0][0],"s5");
    strcpy(ACTION[0][3],"s4");

    strcpy(ACTION[1][1],"s6"); 
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



char input[100];
void parse(){
 int ip=0;
 while(1){
    int state=st[tp];
    char sym=input[ip];
    char token=sym;
    if(isalpha(token)){
        token='i';
    }
    int getid=gett(token);
    if(getid==-1){
        printf("err");
    }
    char action[10];
    strcpy(action,ACTION[state][getid]);
    if(strlen(action)==0){
        printf("Err");
        return;
    }
    if(action[0]=='s'){
        int next=atoi(action+1);
        push(next);
        if(token=='i'){
            char temp[100];
            temp[0]=sym;
            temp[1]='\0';
            ppush(temp);
        }
        ip++;
    }
    else if(action[0]=='r'){
        int r=atoi(action+1);
        switch(r){
            case 1:{
                char t[100];
                char e[100];
                char temp[100];
                strcpy(temp,newtemp());
                strcpy(t,ppop());
                strcpy(e,ppop());
                printf("%s = %s+%s\n",temp,e,t);
                pop();pop();pop();
                ppush(temp);
                break;
            }
            case 2:{
               char t[100];
               char e[100];
                char temp[100];
                strcpy(temp,newtemp());
               strcpy(t,ppop());
               strcpy(e,ppop());
               printf("%s=%s-%s\n",temp,e,t);
               ppush(temp);
               pop();pop();pop();break;
            }
            case 3:{
                pop();break;
            }
            case 4:{
                char t[100];
                char f[100];
                char temp[100];
                strcpy(temp,newtemp());
                strcpy(f,ppop());
                strcpy(t,ppop());
                printf("%s=%s*%s\n",temp,t,f);
                ppush(temp);
                pop();pop();pop();
                break;
            }
            case 5:{
                char t[100];
                char f[100];
                char temp[100];
                strcpy(temp,newtemp());
                strcpy(f,ppop());
                strcpy(t,ppop());
                printf("%s=%s/%s\n",temp,t,f);
                pop();pop();pop();
                ppush(temp);
                break;
            }
            case 6:{
                pop();break;
            }
            case 7:{
                pop();
                break;
            }
        }
        int state2=st[tp];
        char lhs;
        if(r==1||r==2||r==3){
            lhs='E';
        }
        else if(r==4||r==5||r==6){
            lhs='T';
        }
        else{
            lhs='F';
        }
        int getid=getnt(lhs);
        push(GOTO[state2][getid]);

    }
    else if(strcmp(action,"acc")==0){
        printf("Accepted\n");
        printf("Result = %s",placestack[ptop]);
        return;
    }
    else{
        printf("eRR");
    }

 }
}

int main(){
    initTable();
    scanf("%s",input);
    strcat(input,"$");
    push(0);
    parse();
}