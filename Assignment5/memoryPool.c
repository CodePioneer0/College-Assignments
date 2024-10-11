#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct listNode{
    int data;
    struct listNode *next;
};

struct MemoryPool {
    struct listNode *head;
    int totalNodes;
    int availableNodes;
};
struct MemoryPool pool;


int releaseMemoryPoolNodes() {
    if (pool.head == NULL) {
        return 0;
    }

    struct listNode *current = pool.head;
    struct listNode *next=NULL;
    int nodesFreed = 0;

    do {
        next = current->next;
        free(current);
        current = next;
        nodesFreed++;
    } while (current != pool.head && current != NULL);

    int leaks = pool.totalNodes - nodesFreed;
    if (leaks > 0) {
        printf("Memory leak detected: %d nodes were not released.\n", leaks);
    }

    pool.head = NULL;
    pool.totalNodes = 0;
    pool.availableNodes = 0;

    return leaks;
}
int createMemoryPoolNodes(int numNodes) {
    if (numNodes <= 0) {
        return 0;
    }

    pool.totalNodes = numNodes;
    pool.availableNodes = numNodes;
    pool.head = NULL;

    struct listNode *tail = NULL;
    for (int i = 0; i < numNodes; i++) {
        struct listNode *newNode = (struct listNode *)malloc(sizeof(struct listNode));
        if (newNode == NULL) {
            releaseMemoryPoolNodes();
            return 0;
        }
        if (pool.head == NULL) {
            pool.head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        
    }
    if (tail != NULL) {
        tail->next = pool.head;
    }
    return 1;
}

struct listNode *getNode() {
    if (pool.availableNodes == 0) {
        return NULL;
    }
    struct listNode *node = pool.head;
    pool.head = node->next;
    pool.availableNodes--;

    node->next = NULL;
    return node;
}
void releaseNode(struct listNode *node) {
    if (node == NULL) {
        return;
    }

    node->next = pool.head;
    pool.head = node;
    pool.availableNodes++;
}



struct listNode *deleteListNodeSorted(struct listNode *start, int elem) {
    if (start == NULL) return NULL;
    
    struct listNode *head = start;
    if (start->data == elem) {
        start = start->next;
        releaseNode(head);
        return start;
    }
    struct listNode *prev = NULL;
    while (start && (start->data != elem)) {
        prev = start;
        start = start->next;
    }
    if (start == NULL) {
        printf("Element value %d not found\n", elem);
    } else {
        prev->next = start->next;
        releaseNode(start);
    }

    return head;
}
void printLinkedList(struct listNode *start){
    if (start == NULL) {
        printf("The list is empty\n");
        return;
    }
    printf("The list contains: ");
    struct listNode *current = start;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != start && current != NULL);
    printf("(back to start)\n\n");
}
void freeListNodeSorted(struct listNode *start) {
    struct listNode *prev = NULL;
    while (start) {
        prev = start;
        start = start->next;
        releaseNode(prev);
    }
}
struct listNode *addListNodeSorted(struct listNode *start, int elem){
    struct listNode *temp = getNode();
    if (temp == NULL) {
        printf("Memory pool is empty. Cannot add new node.\n");
        return start;
    }
    temp->data = elem;

    if (start == NULL) {
        temp->next = temp;  
        return temp;
    }

    if (start->data <= elem) {
        temp->next = start->next;
        start->next = temp;
        return start;
    }

    struct listNode *current = start;
    while (current->next != start && current->next->data > elem) {
        current = current->next;
    }
    temp->next = current->next;
    current->next = temp;
    return (temp->data < start->data) ? temp : start;
}
int main() {
     if (createMemoryPoolNodes(5)) {
        printf("MemoryPool Created!\n");
    } else {
        printf("Failed to create MemoryPool!\n");
        return 1;
    }

    struct listNode *head = NULL;
    head = addListNodeSorted(head, 3);
    head = addListNodeSorted(head, 1);
    head = addListNodeSorted(head, 4);
    head = addListNodeSorted(head, 2);
    head = addListNodeSorted(head, 5);

    printLinkedList(head);

    head = addListNodeSorted(head, 6);

    printLinkedList(head);

    freeListNodeSorted(head);
    int leaks = releaseMemoryPoolNodes();
    if (leaks > 0) {
        printf("Warning: %d nodes were not properly released\n", leaks);
    }

    

    return 0;
}