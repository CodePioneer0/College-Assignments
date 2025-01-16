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
    myStack st;
    int maxSize;
    printf("Enter the max length of stack : ");
    scanf("%d",&maxSize);
    if(initIntegerStack(&st,maxSize)){
        printf("Stack Creation Successful!\n");
    }
    else{
        printf("Stack Creation Failed!\n");
    }
    printf("Enter the following options for Stack operations!\n");
    printf("1.Push\n2.Pop\n3.isEmpty\n4.isFull\n5.DisplayStack\n");
    printf("Enter 6 to Exit!\n");
    int n;
    do{
        printf("Enter the appropriate option : ");
        scanf("%d",&n);
        if(n==1){
            int d;
            printf("Enter the element to be pushed :");
            scanf("%d",&d);
            if(pushIntegerStack(&st,d)){
                printf("Push Successful!\n");
            }
            else{
                printf("Stack is full!\n");
            }
        }
        else if(n==2){
            int e;
            if(popIntegerStack(&st,&e)){
                printf("Pop Successful!\n");
                printf("Element is : %d\n",e);
            }
            else{
                printf("Stack is Empty!\n");
            }
        }
        else if(n==3){
            if(isIntegerStackEmpty(&st)){
                printf("Stack is Empty!\n");
            }
            else{
                printf("Stack is not Empty!\n");
            }
        }
        else if(n==4){
            if(isIntegerStackFull(&st)){
                printf("Stack is Full!\n");
            }
            else{
                printf("Stack is not Full!\n");
            }
        }
        else if(n==5){
            displayStack(&st);
        }
    }while(n!=6);
    if(freeIntegerStack(&st)){
        printf("Released Allocated Memory!\n");
    }
    else{
        printf("Memory Release Failure!\n");
    }
    return 0;
}



