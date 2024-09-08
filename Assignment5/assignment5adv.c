#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct largeIntNode
{
    unsigned char digit;
    struct largeIntNode *next;
} largeIntNode;
largeIntNode *CreateSingleNode(char val)
{
    largeIntNode *temp = NULL;
    temp = (largeIntNode *)malloc(sizeof(largeIntNode));
    if (temp == NULL){
        printf("Memory is full\n");
        exit(1);
    }
    temp->digit = val;
    temp->next = NULL;
    return temp;
}
largeIntNode *representLargeInt(largeIntNode *head,char c)
{
    largeIntNode *temp = CreateSingleNode(c);
    largeIntNode *start = head;
    if(head==NULL){
        return temp;
    }
    while(start->next!=NULL){
        start=start->next;
    }
    start->next = temp;
    return head;
}
void printLinkedList(largeIntNode *start){
    printf("The list contains :");
    while(start){
        printf("%c -> ",start->digit);
        start=start->next;
    }
    printf("NULL\n\n");
}

largeIntNode *addLargeInts(largeIntNode *head1, largeIntNode *head2){
    if(head1==NULL || head2==NULL) return NULL;
    largeIntNode *head=NULL;
    head = CreateSingleNode('0');
    largeIntNode *temp = head;
    while(head1 && head2){
        int a = head1->digit-'0';
        int b = head2->digit-'0';
        int s = (a+b)%10;
        int c = (a+b)/10;
        int res = (temp->digit-'0') + s;
        temp->digit = (res+'0');
        temp->next = CreateSingleNode(c+'0');
        temp = temp->next;
        head1 = head1->next;
        head2 = head2->next;
    }
    while(head1){
        int a = head1->digit-'0';
        int b = temp->digit - '0';
        
    }
    return head;

}
int main()
{
    largeIntNode *head= NULL;
    char a[100];
    char b[100];
    printf("Enter the number 1:\n");
    largeIntNode *head1=NULL;
    scanf("%s",a);
    printf("Enter the number 2:\n");
    largeIntNode *head2=NULL;
    scanf("%s",b);
    int n = strlen(a);
    int m = strlen(b);
    for(int i=n-1;i>=0;i--){
        head1=representLargeInt(head1,a[i]);
    }
    for(int i=m-1;i>=0;i--){
        head2 = representLargeInt(head2,b[i]);
    }
    head = addLargeInts(head1,head2);
    printLinkedList(head);
    return 0;
}