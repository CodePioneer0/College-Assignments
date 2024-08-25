#include<stdio.h>
#include<stdlib.h>

typedef struct queue{
    int *items;
    int front, rear, size;
}queue;

queue* createQueue(int queueSize){
    queue *q;
    q=(queue*)malloc(sizeof(queue));
    if(q==NULL){
        return NULL;
    }

    q->items = (int *)malloc(sizeof(int)*queueSize);
    q->front=0;
    q->rear=0;
    q->size=queueSize;
    return q;
}

int isFull(queue *q){
    return (q->front-q->rear==1); //f-r=1
}

int isEmpty(queue *q){
    return (q->front==q->rear);
}

int enqueue(queue *q, int d){
    if(isFull(q)) return 0;

    if(q->rear == q->size-1) q->rear=0;
    else q->rear++;

    if(q->rear==q->front) return 0;

    q->items[q->rear]=d;
    return 1;
}

int dequeue(queue* q, int *dp){
    if(isEmpty(q)) return 0;

    if(q->front==q->size-1) q->front=0;
    else q->front++;

    *dp=q->items[q->front];
    return 1;
}

int freeQueue(queue *q){
    if(q->items==NULL){
        return 0;
    }
    free(q->items);
    return 1;
}

void printQueue(queue *q){
    if(isEmpty(q)){
        printf("Queue is empty!\n");
    }
    int s = (q->front+1)%q->size;
    int e = (q->rear)%q->size;
    printf("Queue : ");
    for(int i=s;;i=(i+1)%q->size){
        printf("%d\t",q->items[i]);
        if(i==e) break;
    }
    printf("\n");
}

int main(){
    queue Qyu;
    int Qyu_size, option, element;
    printf("Enter size of queue ");
    scanf("%d", &Qyu_size);
    Qyu=*createQueue(Qyu_size+1);

    while(1){
        printf("1 Enqueue \n2 dequeue \n3 to print queue \n4 to exit\n");
        scanf("%d", &option);
        switch(option){
            case 1: {
                printf("enter an element to enqueue ");
                scanf("%d", &element);
                
                if(enqueue(&Qyu, element)) printf("Successful enqueue!\n");
                else printf("Overflow!");
                break;
            }
            case 2: {
                
                if(dequeue(&Qyu, &element)) printf("Element : %d\n",element);
                else printf("underflow");
                break;
            }
            case 3: {
                printQueue(&Qyu);
                break;
            }
            case 4:{
                freeQueue(&Qyu);
                return 1;
            }
        }
    }
    return 0;
}