#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
largeIntNode *representLargeInt(largeIntNode *head, char c)
{
    largeIntNode *temp = CreateSingleNode(c);
    largeIntNode *start = head;
    if (head == NULL){
        return temp;
    }
    while (start->next != NULL)
    {
        start = start->next;
    }
    start->next = temp;
    return head;
}
void printLinkedList(largeIntNode *start)
{
    printf("The list contains :");
    while (start)
    {
        printf("%c", start->digit);
        start = start->next;
    }
    printf("\n\n");
}
unsigned long long toDecimal(largeIntNode* head) {
    largeIntNode* current = head;
    unsigned long long result = 0;
    while (current) {
        result = result * 10 + (current->digit - '0');
        current = current->next;
    }
    return result;
}

void printHexadecimal(largeIntNode* head) {
    unsigned long long ValueInDecimal = toDecimal(head);
    printf("Hexadecimal Form is: %llX\n", ValueInDecimal);
}


largeIntNode *addLargeInts(largeIntNode *head1, largeIntNode *head2){
    if (head1 == NULL || head2 == NULL)
        return NULL;
    int c = 0;
    largeIntNode *head = NULL;
    largeIntNode *tail = NULL;

    while (head2 || head1 || c){
        int s = c;
        if(head1){
            s+=(head1->digit - '0');
            head1=head1->next;
        }
        if(head2){
            s+=(head2->digit-'0');
            head2 = head2->next;
        }
        int res = s%10;
        c = c/10;
        largeIntNode *temp = CreateSingleNode(res + '0');
        if(head==NULL){
           head = temp;
           tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }
    return head;
}
largeIntNode *substractLargeInts(largeIntNode *head1,largeIntNode *head2){
    int b = 0;
    largeIntNode *head = NULL;
    largeIntNode *tail = NULL;
    while(head1 || head2 || b){
        int x;
        int y;
        int dif;
        if(head1) x = head1->digit-'0';
        else x= 0;
        if(head2) y=head2->digit-'0';
        else y=0;
        dif = x-y-b;
        if(dif<0){
            dif+=10;
            b=1;
        }
        else{
            b = 0;
        }
        largeIntNode *temp = CreateSingleNode(dif + '0');
        if(head==NULL){
            head = temp;
            tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
        if(head1) head1 = head1->next;
        if(head2) head2 = head2->next;
    }
    return head;
}
largeIntNode *reverseListNodeSorted(largeIntNode *start){
    largeIntNode *prev=NULL;
    largeIntNode *temp = start;
    largeIntNode *front=NULL;
    while(temp){
        front = temp->next;
        temp->next=prev;
        prev = temp;
        temp = front;
    }
    return prev;
}

int main(){
    char a[100];
    printf("Enter the number 1:\n");
    largeIntNode *head1 = NULL;
    scanf("%s", a);
    int n = strlen(a);
    for (int i = n - 1; i >= 0; i--){
        head1 = representLargeInt(head1, a[i]);
    }
    0
    printLinkedList(head1);
    printHexadecimal(head1);
    return 0;
}