#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue{
    int qSize;
    int rear;
    int front;
    int *arr;
}queue;
queue* createIntegerQueue(int queueSize){
    queue *q = (queue *)malloc(sizeof(queue));
    q->qSize = queueSize;
    q->arr = (int *)malloc(queueSize*sizeof(int));
    if(q->arr==NULL){
        return NULL;
    }
    q->rear  = - 1;
    q->front = - 1;
    return q;
}
int isIntegerQueueFull(queue *q){
    if((q->rear+1)%q->qSize==q->front){
        return 1;
    }
    return 0;
}
int isIntegerQueueEmpty(queue *q){
    if(q->front==-1 && q->rear==-1){
        return 1;
    }
    return 0;
}
int enqueuqInteger(queue *q,int d){
    if(q->front==-1 && q->rear==-1){
        q->front=0;
        q->rear=0;
        q->arr[q->rear]=d;
        return 1;
    }else if((q->rear+1)%q->qSize==q->front){
        return 0;
    }
    q->rear=(q->rear+1)%q->qSize;
    q->arr[q->rear]=d;
    return 1;
}
int dequeueInteger(queue *q,int *d){
    if(q->front==-1 && q->rear==-1){
        return 0;
    }
    else if(q->rear==q->front){
        *d=q->arr[q->front];
        q->front=-1;
        q->rear=-1;
        return 1;
    }
    *d=q->arr[q->front];
    q->front=(q->front+1)%q->qSize;
    return 1;
}
int freeIntegerQueue(queue *q){
    if(q){
        free(q->arr);
        q->arr=NULL;
        return 1;
    }
    return 0;
}
void displayQueue(queue *q){
    if(isIntegerQueueEmpty(q)){
        printf("Queue is Empty!\n");
        return;
    }
    printf("Queue : \n");
    int i=q->front;
    while(i!=q->rear){
        printf("%d\t",q->arr[i]);
        i = (i+1)%q->qSize;
    }
    printf("%d",q->arr[q->rear]);
    printf("\n");
}
int main(){
    int mx;
    printf("Enter the Queue size : ");
    scanf("%d",&mx);
    if(createIntegerQueue(mx)==NULL){
        printf("Queue Creation Failure!\n");
        return 1;
    }
    queue q = *createIntegerQueue(mx);


    printf("Enter the following options for Queue operations!\n");
    printf("1.Enqueue\n2.Dequeue\n3.isEmpty\n4.isFull\n5.DisplayQueue\n");
    printf("Enter 6 to Exit!\n");
    int n;
    do{
        printf("Enter the appropriate option : ");
        scanf("%d",&n);
        if(n==1){
            int d;
            printf("Enter the element to enqueue :");
            scanf("%d",&d);
            if(enqueuqInteger(&q,d)){
                printf("Enqueue Successful\n");
            }
            else{
                printf("Queue Overflow!\n");
            }
        }
        else if(n==2){
            int e;
            if(dequeueInteger(&q,&e)){
                printf("Dequeue Successful\n");
                printf("Element is : %d\n",e);
            }
            else{
                printf("Queue Underflow!\n");
            }
        }
        else if(n==3){
            if(isIntegerQueueEmpty(&q)){
                printf("Queue is Empty\n");
            }
            else{
                printf("Queue is not Empty!\n");
            }
        }
        else if(n==4){
            if(isIntegerQueueFull(&q)){
                printf("Queue is Full!\n");
            }
            else{
                printf("Queue is not Full!\n");
            }
        }
        else if(n==5){
            displayQueue(&q);
        }
    }while(n!=6);
    if(freeIntegerQueue(&q)){
        printf("Released Allocated Memory!\n");
    }
    else{
        printf("Memory Release Failure!\n");
    }
    return 0;
}

