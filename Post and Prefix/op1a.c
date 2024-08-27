#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
typedef struct myStack {
    int maxSize;
    int count;
    int *arr;
} myStack;
int initIntegerStack(myStack *st,int stackSize){
    st->maxSize=stackSize;
    st->count=-1;
    st->arr = (int *)malloc(stackSize*sizeof(int));
    if(st->arr){
        return 1;
    }
    else{
        return 0;
    }
}
int freeIntegerStack(myStack *st){
    if(st){
        free(st->arr);
        st->arr=NULL;
        return 1;
    }
    return 0;
}
int isIntegerStackFull(myStack *st){
    if(st->count+1==st->maxSize){
        return 1;
    }
    return 0;
}
int isIntegerStackEmpty(myStack *st){
    if(st->count==-1){
        return 1;
    }
    return 0;
}
int pushIntegerStack(myStack *st,int d){
    if(isIntegerStackFull(st)){
        return 0;
    }
    st->arr[++st->count]=d;
    return 1;
}
int popIntegerStack(myStack *st,int *d){
    if(isIntegerStackEmpty(st)){
        return 0;
    }
    *d = st->arr[st->count];
    st->count--;
    return 1;
}
void displayStack(myStack *st){
    for(int i=st->count;i>=0;i--){
        printf("%d\n",st->arr[i]);
    }
}
int isOp(char a){
    if(a=='*' || a=='+' || a=='/' || a=='-' || a=='^'){
        return 1;
    }
    return 0;
}
int Op(int a,int b,char o){
    if(o=='+'){
        return a+b;
    }
    else if(o=='-'){
        return a-b;
    }
    else if(o=='*'){
        return a*b;
    }
    else if(o=='/'){
        return a/b;
    }
    else{
        return (int)pow(a,b);
    }
}


int main() {
    myStack st;
    char s[100];
    printf("Enter the string : ");
    scanf("%s",s);
    int maxSize = strlen(s);
    initIntegerStack(&st,maxSize);
    int i=0;
    while(s[i]!='\0'){
        char a = s[i];
        if(!isOp(a)){
            pushIntegerStack(&st,a-'0');
        }
        else{
            int opnd2;
            int opnd1;
            popIntegerStack(&st,&opnd2);
            popIntegerStack(&st,&opnd1);
            int value = Op(opnd1,opnd2,a);
            pushIntegerStack(&st,value);
        }
        i++;
    }
    int res;
    popIntegerStack(&st,&res);
    printf("The Result is : %d\n",res);
    if (freeIntegerStack(&st)) {
        printf("Released Allocated Memory!\n");
    } else {
        printf("Memory Release Failure!\n");
    }
    return 0;
}