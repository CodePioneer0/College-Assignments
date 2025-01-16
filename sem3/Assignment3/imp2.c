#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct myStack {
    int maxSize;
    int count;
    int *element;
} myStack;
int initIntegerStack(myStack *st,int stackSize){
    st->maxSize=stackSize;
    st->count=-1;
    st->element = (int *)malloc(stackSize*sizeof(int));
    if(st->element){
        return 1;
    }
    else{
        return 0;
    }
}
int freeIntegerStack(myStack *st){
    if(st){
        free(st->element);
        st->element=NULL;
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
    st->element[++st->count]=d;
    return 1;
}
int popIntegerStack(myStack *st,int *d){
    if(isIntegerStackEmpty(st)){
        return 0;
    }
    *d = st->element[st->count];
    st->count--;
    return 1;
}
void displayStack(myStack *st){
    for(int i=st->count;i>=0;i--){
        printf("%d\n",st->element[i]);
    }
}


int main() {
    myStack st;


    char s[100];
    printf("Enter the string : ");
    scanf("%s",s);
    int maxSize = strlen(s);
    initIntegerStack(&st,maxSize);
    int ok = 1;
    for(int i=0;s[i]!='\0';i++){
        if(s[i]=='(' || s[i]=='{' || s[i]=='['){
            pushIntegerStack(&st,(int)s[i]);
        }
        if(s[i]==')' || s[i]=='}' || s[i]==']'){
            if(isIntegerStackEmpty(&st)){
                ok = 0;
                break;
            }
            else{
                int ch;
                popIntegerStack(&st,&ch);
                if(s[i]==')' && (char)ch!='('){
                    ok = 0;
                    break;
                }
                if(s[i]=='}' && (char)ch!='{'){
                    ok = 0;
                    break;
                }
                if(s[i]==']' && (char)ch!='['){
                    ok = 0;
                    break;
                }
            }
        }
    }
    if(ok && !isIntegerStackEmpty(&st)){
        ok = 0;
    }
    if(ok){
        printf("Valid Parenthesis!\n");
    }
    else{
        printf("Invalid Parenthesis!\n");
    }


    if (freeIntegerStack(&st)) {
        printf("Released Allocated Memory!\n");
    } else {
        printf("Memory Release Failure!\n");
    }
    return 0;
}