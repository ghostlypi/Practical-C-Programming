#ifndef llist_H
#define llist_H
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
    struct node *prev;
};

typedef struct node Node;

Node *newNode(int val);

Node *linsert(Node *prev, int val);

void ldelete(Node *n);

void lprint(Node *head);

Node *lfind(Node *head, int val);

void lfree(Node *head);

#endif