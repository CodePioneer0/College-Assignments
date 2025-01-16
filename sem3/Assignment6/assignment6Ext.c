#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    struct node *parent;
} treenode;
treenode *createNode(int data, treenode *parent){
    treenode *newNode = (treenode *)malloc(sizeof(treenode));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->parent = parent;
    return newNode;
}
treenode *insertNode(treenode *t, int val){
    if (t == NULL){
        return createNode(val, t);
    }
    treenode *temp = t;
    while (1){
        if (temp->data <= val){
            if (temp->rchild != NULL) temp = temp->rchild;
            else{
                temp->rchild = createNode(val, temp);
                break;
            }
        }
        else{
            if (temp->lchild != NULL) temp = temp->lchild;
            else{
                temp->lchild = createNode(val, temp);
                break;
            }
        }
    }
    return t;
}


int mx(int a, int b){
    if (a >= b)
        return a;
    return b;
}
int height(treenode *t){
    if (t == NULL)
        return -1;

    int lt = height(t->lchild);
    int rt = height(t->rchild);

    return 1 + mx(lt, rt);
}
int max(treenode *t){
    while (t->rchild != NULL){
        t = t->rchild;
    }
    return t->data;
}
int min(treenode *t){
    while (t->lchild != NULL){
        t = t->lchild;
    }
    return t->data;
}

int equal(treenode *p, treenode *q){
    if (p == NULL || q == NULL){
        return p == q;
    }
    return (p->data == q->data) && equal(p->lchild, q->lchild) && equal(p->rchild, q->rchild);
}
treenode *insucc(treenode *t, int key)
{
    if (t == NULL)
        return NULL;
    treenode *curr = t;
    treenode *succ = NULL;

    while (curr){
        if (key < curr->data){
            succ = curr;
            curr = curr->lchild;
        }
        else if (key > curr->data){
            curr = curr->rchild;
        }
        else{
            if (curr->rchild != NULL){
                curr = curr->rchild;
                while (curr->lchild != NULL){
                    curr = curr->lchild;
                }
                succ = curr;
            }
            break;
        }
    }
    return succ;
}
treenode *rearrangeTree(treenode *root)
{
    if (root->lchild == NULL) return root->rchild;
    if (root->rchild == NULL) return root->lchild;
    treenode *rightChild = root->rchild;
    treenode *lastRight = root->lchild;
    while (lastRight->rchild != NULL) lastRight = lastRight->rchild;
    lastRight->rchild = rightChild;
    return root->lchild;
}


treenode *deleteNode(treenode *t, int val){
    if (t == NULL) return t;
    if (t->data == val) return rearrangeTree(t);
    treenode *root = t;
    while (t != NULL){
        if (t->data < val){
            if (t->rchild != NULL && t->rchild->data == val){
                t->rchild = rearrangeTree(t->rchild);
                break;
            }
            else{
                t = t->rchild;
            }
        }
        else{
            if (t->lchild != NULL && t->lchild->data == val){
                t->lchild = rearrangeTree(t->lchild);
                break;
            }
            else{
                t = t->lchild;
            }
        }
    }
    return root;
}
int main(){
    
    treenode *root = NULL;
    root = insertNode(root,6);
    root = insertNode(root,5);
    root = insertNode(root,7);
    root = insertNode(root,8);
    root = insertNode(root,4);
    treenode *root1 = NULL;
    root1 = insertNode(root1,6);
    root1 = insertNode(root1,5);
    root1 = insertNode(root1,7);
    root1 = insertNode(root1,8);
    root1 = insertNode(root1,4);
    printf("Height : %d\n",height(root));
    printf("Max Element : %d\n",max(root));
    printf("Min Element : %d\n",min(root));
    if(equal(root,root1)) printf("Yes Equal\n");
    else printf("Not Equal\n");
    printf("Inorder Successor : %d",insucc(root,6)->data);
    root = deleteNode(root,6);
}