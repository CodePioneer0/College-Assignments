#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct poly_node
{
    int coef;
    int expon;
    struct poly_node *next;
} poly_node;
poly_node *CreateSingleNode(int e, int c)
{
    poly_node *temp = NULL;
    temp = (poly_node *)malloc(sizeof(poly_node));
    if (temp == NULL)
    {
        printf("Memory is full\n");
        exit(1);
    }
    temp->coef = c;
    temp->expon = e;
    temp->next = NULL;
    return temp;
}

poly_node *addListNodeSorted(poly_node *start, int e, int c)
{
    poly_node *temp = CreateSingleNode(e, c);
    // No element
    if (start == NULL)
        return temp;

    // Single Element
    if (start->next == NULL)
    {
        if (start->expon > e)
        {
            start->next = temp;
            return start;
        }
        else
        {
            temp->next = start;
            return temp;
        }
    }
    // general case
    if (start->expon < e)
    {
        temp->next = start;
        return temp;
    }
    poly_node *head = start;
    poly_node *prev = NULL;
    while (start && start->expon > e)
    {
        prev = start;
        start = start->next;
    }
    temp->next = prev->next;
    prev->next = temp;
    return head;
}
poly_node *createthelist(poly_node *head, int n)
{
    int c;
    int e;
    for (int i = 0; i < n; i++)
    {
        printf("Enter the Exponent of %dth variable:\n", i + 1);
        scanf("%d", &e);
        printf("Enter the coefficient of %dth variable:\n", i + 1);
        scanf("%d", &c);
        head = addListNodeSorted(head, e, c);
    }
    return head;
}
void printLinkedList(poly_node *start)
{
    printf("The list contains :");
    while (start)
    {
        printf("%dx^%d", start->coef, start->expon);
        start = start->next;
        if (start != NULL)
        {
            printf(" + ");
        }
    }
    printf("\n\n");
}

poly_node *addPolynomial(poly_node *head1,poly_node *head2){
    poly_node *ptr1 = head1;
    poly_node *ptr2 = head2;
    poly_node *head = NULL;
    while(ptr1 && ptr2){
        if(ptr1->expon == ptr2->expon){
            head = addListNodeSorted(head,ptr1->expon,ptr1->coef+ptr2->coef);
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
        else if(ptr1->expon>ptr2->expon){
            head = addListNodeSorted(head,ptr1->expon,ptr1->coef);
            ptr1=ptr1->next;
        }
        else if(ptr1->expon<ptr2->expon){
            head = addListNodeSorted(head,ptr2->expon,ptr2->coef);
            ptr2=ptr2->next;
        }
    }
    while(ptr1){
        head = addListNodeSorted(head,ptr1->expon,ptr1->coef);
        ptr1 = ptr1->next;
    }
    while(ptr2){
        head = addListNodeSorted(head,ptr2->expon,ptr2->coef);
        ptr2 = ptr2->next;
    }
    return head;
}
poly_node *substractPoly(poly_node *head1,poly_node *head2){
    poly_node *ptr1 = head1;
    poly_node *ptr2 = head2;
    poly_node *head = NULL;
    while(ptr1 && ptr2){
        if(ptr1->expon == ptr2->expon){
            head = addListNodeSorted(head,ptr1->expon,ptr1->coef-ptr2->coef);
            ptr1=ptr1->next;
            ptr2=ptr2->next;
        }
        else if(ptr1->expon>ptr2->expon){
            head = addListNodeSorted(head,ptr1->expon,ptr1->coef);
            ptr1=ptr1->next;
        }
        else if(ptr1->expon<ptr2->expon){
            head = addListNodeSorted(head,ptr2->expon,ptr2->coef);
            ptr2=ptr2->next;
        }
    }
    while(ptr1){
        head = addListNodeSorted(head,ptr1->expon,ptr1->coef);
        ptr1 = ptr1->next;
    }
    while(ptr2){
        head = addListNodeSorted(head,ptr2->expon,ptr2->coef);
        ptr2 = ptr2->next;
    }
    return head;
}
int main()
{
    int n;
    printf("Enter the number of terms : \n");
    scanf("%d", &n);
    poly_node *head1 = NULL;
    poly_node *head2 = NULL;
    head1 = createthelist(head1, n);
    head2 = createthelist(head2,n);
    poly_node *head = addPolynomial(head1,head2);
    printLinkedList(head);
}