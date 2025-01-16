#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct queue{
    int qSize;
    int rear;
    int front;
    int *arr;
    int count;
}queue;
queue* createIntegerQueue(int queueSize){
    queue *q = (queue *)malloc(sizeof(queue));
    q->qSize = queueSize;
    q->arr = (int *)malloc(queueSize*sizeof(int));
    if(q->arr==NULL){
        return NULL;
    }
    q->rear = queueSize - 1;
    q->front = queueSize - 1;
    q->count=0;
    return q;
}
int isIntegerQueueFull(queue *q){
    if(q->count==q->qSize-1){
        return 1;
    }
    return 0;
}
int isIntegerQueueEmpty(queue *q){
    if(q->count==0){
        return 1;
    }
    return 0;
}
int enqueuqInteger(queue *q,int d){
    q->rear = (q->rear+1)%q->qSize;
    if(q->rear==q->front){
        return 0;
    }
    q->arr[q->rear]=d;
    q->count++;
    return 1;
}
int dequeueInteger(queue *q,int *d){
    if(isIntegerQueueEmpty(q)){
        return 0;
    }
    q->front = (q->front+1)%q->qSize;
    *d = q->arr[q->front];
    q->count--;
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


int main(){
    int mx;
    printf("Enter the Queue size : ");
    scanf("%d",&mx);
    if(createIntegerQueue(mx+1)==NULL){
        printf("Queue Creation Failure!\n");
        return 1;
    }
    queue q = *createIntegerQueue(mx+1);
    printf("Enter %d numbers to enqueue : \n",mx);
    while(mx--){
        printf("Enter the number : ");
        int n;
        scanf("%d",&n);
        enqueuqInteger(&q,n);
    }
    printf("Queue is Full now!\n");
    printf("Starting Dequeue Process!\n");
    while(!isIntegerQueueEmpty(&q)){
        int d;
        dequeueInteger(&q,&d);
        printf("Dequeue element : %d\n",d);
        if(d>0){
            int random = (rand()%9)+1;
            d-=random;
            enqueuqInteger(&q,d);
        }
        else{
            continue;
        }
    }
    if(freeIntegerQueue(&q)){
        printf("Released Allocated Memory!\n");
    }
    else{
        printf("Memory Release Failure!\n");
    }
    return 0;
}

