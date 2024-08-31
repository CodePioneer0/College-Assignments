#include<stdio.h>
#include <stdlib.h>

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
    //One node case
    if(start->next==NULL){
        if(start->data==elem){
            free(start);
            return NULL;
        }
        printf("Element value %d not found\n",elem);
        return start;
    }
    struct listNode *head = start;
    if(start->data==elem){
        head=head->next;
        free(start);
        return head;
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


int main(){
    struct listNode *head=NULL;
    head=addListNodeSorted(head,1);
    head=addListNodeSorted(head,0);
    head=addListNodeSorted(head,8);
    head=addListNodeSorted(head,4);
    head=addListNodeSorted(head,5);
    printLinkedList(head);
    if(isPresentListNodeSorted(head,8)){
        printf("Present!\n");
    }
    else{
        printf("Absent!\n");
    }
    head=deleteListNodeSorted(head,8);
    head=deleteListNodeSorted(head,4);
    printLinkedList(head);
    return 0;
}