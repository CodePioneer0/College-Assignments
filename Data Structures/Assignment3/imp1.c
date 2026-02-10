#include<stdio.h>
#include<malloc.h>
typedef struct myStack{
    int maxSize;
    int count;
    int *element;
}myStack;

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

int main(){
    myStack st1;
    myStack st2;
    int n;
    int m;
    printf("Enter the stack size of Stack 1 : ");
    scanf("%d",&n);
    printf("Enter the stack size of Stack 2 : ");
    scanf("%d",&m);
    if(initIntegerStack(&st1,n)) printf("Stack1 Created!\n");
    else printf("Failed to create!\n");
    if(initIntegerStack(&st2,m)) printf("Stack2 Created!\n");
    else printf("Failed to create!\n");
    printf("1.Push to Stack\n2.Display the Stacks\n");
    int k;
    do{
        printf("Enter the appropriate option : ");
        scanf("%d",&k);
        if(k==1){
            int d;
            printf("Enter the element :");
            scanf("%d",&d);
            if(!isIntegerStackFull(&st1)){
                if(pushIntegerStack(&st1,d)){
                    printf("Push Successful!\n");
                }
                else{
                    printf("Unable to push!\n");
                }
            }
            else{
                if(pushIntegerStack(&st2,d)){
                    printf("Push Successful!\n");
                }
                else{
                    printf("Unable to push!\n");
                }
            }
        }
        else if(k==2){
            printf("Stack1 : \n");
            displayStack(&st1);
            printf("Stack2 : \n");
            displayStack(&st2);
        }
    }while(!isIntegerStackFull(&st1) || !isIntegerStackFull(&st2));
    printf("Stack1 : \n");
    displayStack(&st1);
    printf("Stack2 : \n");
    displayStack(&st2);
    printf("Both Stacks are full!\n");
    printf("Starting to Pop Elements....\n");
    while(!isIntegerStackEmpty(&st2)){
        int d;
        popIntegerStack(&st2,&d);
        printf("Element : %d\n",d);
    }
    while(!isIntegerStackEmpty(&st1)){
        int d;
        popIntegerStack(&st1,&d);
        printf("Element : %d\n",d);
    }
    if(freeIntegerStack(&st1)){
        printf("Released Allocated Memory for Stack1!\n");
    }
    else{
        printf("Memory Release Failure for Stack1!\n");
    }
    if(freeIntegerStack(&st2)){
        printf("Released Allocated Memory for Stack2!\n");
    }
    else{
        printf("Memory Release Failure for Stack2!\n");
    }
    return 0;
}