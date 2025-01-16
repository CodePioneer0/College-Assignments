#include<stdio.h>
#include <stdlib.h>
#include<time.h>
struct listNode{
    int data;
    struct listNode *next; 
};
struct listNode *CreateSingleNode(int val){
    struct listNode *temp = NULL;
    temp = (struct listNode *)malloc(sizeof(struct listNode));
    if(temp==NULL){
        printf("Memory is full\n");
        exit(1);
    }
    temp->data = val;
    temp->next = NULL;
    return temp;
}

struct listNode *addListNodeSorted(struct listNode *start,int elem){
    struct listNode *temp=CreateSingleNode(elem);
    //No element
    if(start==NULL) return temp;
    
    //Single Element
    if(start->next==NULL){
        if(start->data>elem){
            start->next=temp;
            return start;
        }
        else{
            temp->next = start;
            return temp;
        }
    }
    //general case
    if(start->data<elem){
        temp->next=start;
        return temp;
    }
    struct listNode *head = start;
    struct listNode *prev = NULL;
    while(start && start->data>elem){
        prev = start;
        start=start->next;
    }
    temp->next = prev->next;
    prev->next = temp;
    return head;
}

int isPresentListNodeSorted(struct listNode *start,int elem){
    if(start==NULL) return 0;
    int count = 0;
    while(start){
        count++;
        if(start->data==elem){
            return count;
        }
        start=start->next;
    }
    return 0;
}

struct listNode *deleteListNodeSorted(struct listNode *start,int elem){
    if(start==NULL) return NULL;
    
    struct listNode *head = start;
    if(start->data==elem){
        start=start->next;
        free(head);
        return start;
    }
    struct listNode *prev=NULL;
    while(start && (start->data!=elem)){
        prev = start;
        start=start->next;
    }
    if(start==NULL){
        printf("Element value %d not found\n",elem);
    }
    else{
        prev->next = start->next;
        free(start);
    }

    return head;
}
void printLinkedList(struct listNode *start){
    printf("The list contains :");
    while(start){
        printf("%d -> ",start->data);
        start=start->next;
    }
    printf("NULL\n\n");
}

void freeListNodeSorted(struct listNode *start){
    struct listNode *prev = NULL;
    while(start){
        prev = start;
        start=start->next;
        free(prev);
    }
}
struct listNode *reverseListNodeSorted(struct listNode *start){
    struct listNode *prev=NULL;
    struct listNode *temp = start;
    struct listNode *front=NULL;
    while(temp){
        front = temp->next;
        temp->next=prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

void updateListNode(struct listNode *start){
    srand(time(NULL));
    struct listNode *head = start;
    while(head){
        int d=(rand()%9)+1;
        head->data=head->data+d;
        head=head->next;
    }   
}

struct listNode *mergeListNodeSorted(struct listNode *start1,struct listNode *start2){
    if(!start1) return start2;
    if(!start2) return start1;
    struct listNode *head = NULL;
    struct listNode *temp = NULL; 
    if(start1->data>=start2->data){
        head = start1;
        temp =start1;
        start1=start1->next;
    }
    else{
        head = start2;
        temp = start2;
        start2 = start2->next;
    }

    while(start1 && start2){
        if(start1->data>=start2->data){
            temp->next=start1;
            start1=start1->next;
        }
        else{
            temp->next = start2;
            start2=start2->next;
        }
        temp = temp->next;
    }
    if(start1){
        temp->next = start1;
    }
    else{
        temp->next = start2;
    }
    return head;
}

struct listNode *sortListNode(struct listNode *start){
    if(start == NULL || start->next==NULL){
        return start;
    }
    struct listNode *dummyNode=CreateSingleNode(-1);
    while(start){
        struct listNode *temp = dummyNode;
        struct listNode *next = start->next;
        while(temp->next && temp->next->data>start->data){
            temp=temp->next;
        }
        start->next = temp->next;
        temp->next = start;
        start = next;
    }
    return dummyNode->next;
}



int main(){
    struct listNode *head1=NULL;
    struct listNode *head2=NULL;
    int n=5;
    printf("Write five elements for two linked list !\n");
    printf("First Linked list : \n");
    for(int i=0;i<n;i++){
        int x;
        printf("Enter the %dth number :",i+1);
        scanf("%d",&x);
        head1=addListNodeSorted(head1,x);
    }
    printf("Second Linked list : \n");
    for(int i=0;i<n;i++){
        int x;
        printf("Enter the %dth number :",i+1);
        scanf("%d",&x);
        head2=addListNodeSorted(head2,x);
    }
    printLinkedList(head1);
    printLinkedList(head2);
    struct listNode *head = mergeListNodeSorted(head1,head2);
    printf("This is the new merged list : \n");
    printLinkedList(head);
    printf("Write a number to delete : ");
    scanf("%d",&n);
    head=deleteListNodeSorted(head,n);
    printLinkedList(head);
    printf("The number %d got deleted \n",n);
    printf("Write a number to be found in the list : " );
    scanf("%d",&n);
    if(isPresentListNodeSorted(head,n)){
        printf("The number %d is present\n",n);
    }
    else{
        printf("The number is absent in the list\n");
    }
    printf("The reversed linked list :\n");
    head = reverseListNodeSorted(head);
    printLinkedList(head);
    updateListNode(head);
    printf("This is the updated linked list :\n");
    printLinkedList(head);
    printf("Resorting the linked in descending order :\n");
    head=sortListNode(head);
    printLinkedList(head);
    return 0;
}