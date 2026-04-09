#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char nont[100];
char term[100];
int nt,t;
char input[1000];
char st[100];
int top=-1;
char action[100][100][300];
char pop(){
    return st[top--];
}
void push(char c){
    st[++top]=c;
}
int getnt(char c){
    for(int i=0;i<nt;i++){
        if(c==nont[i])return i;
    }
    return -1;
}
int gett(char c){
    for(int i=0;i<t;i++){
        if(c==term[i])return i;
    }
    return -1;
}
void pristack(){
    for(int i=0;i<=top;i++){
       printf("%c",st[i]);
    }
}
void parse(){
    int ip=0;
    printf("Stack\tInput\tAction\n");
    while(1){
        pristack();
        printf("\t%s\t",input+ip);
        char tpsy=st[top];
        char curr=input[ip];
 
        if(tpsy=='$'&&curr=='$'){
            printf("Acc");
            return;
        }
        // printf("%d %c  %d",top,tpsy,getnt(tpsy));
        if(getnt(tpsy)==-1){
            if(tpsy==curr){
                printf("Match\n");
                pop();
                ip++;
            }
            else{
                printf("Error");
                return;
            }
        }
        else{
            int r=getnt(tpsy);
            int c=gett(curr);
            if(r==-1||c==-1){
                printf("err");
                return;
            }
            char prod[100];
            strcpy(prod,action[r][c]);
            printf("Apply %c ->%s\n",tpsy,prod);
            pop();

            if(strcmp(prod,"e")!=0){
                for(int i=strlen(prod)-1;i>=0;i--){
                    push(prod[i]);
                }
            }
        }
    }
}
int main(){
 scanf("%d",&nt);
 for(int i=0;i<nt;i++){
    scanf(" %c",&nont[i]);
 }
 scanf("%d",&t);
 for(int i=0;i<t;i++){
    scanf(" %c",&term[i]);
 }
 for(int i=0;i<nt;i++){
    for(int j=0;j<t;j++){
        printf("Enter M[%c,%c]",nont[i],term[j]);
        scanf("%s",action[i][j]);
    }
 }
 scanf("%s",input);
 push('$');
 push(nont[0]);
 parse();
}