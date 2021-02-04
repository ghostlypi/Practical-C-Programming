#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

Node *newNode(int val){
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->next = n->prev = NULL;
    return n;
}

Node *linsert(Node *prev, int val){
    Node *n = newNode(val);
    n->prev = prev;
    n->next = prev->next;
    prev->next = n;
    if(n->next != NULL) n->next->prev = n;
    return n;
}

void ldelete(Node *n){
    if(n->prev != NULL)n->prev->next = n->next;
    if(n->next != NULL)n->next->prev = n->prev;
    free(n);
}

void lprint(Node *head){
    int i = 0;
    Node *n = head;
    while(n != NULL){
        printf("[%d] %d", i, n->val);
        i++;
        n = n->next;
    }
}

Node *lfind(Node *head, int val){
    if(head == NULL){
        return NULL;
    }else if(head->val == val){
        return head;
    }
    return lfind(head->next, val);
}

void lfree(Node *head){
    if(head == NULL){
        return;
    }
    Node *n = head->next;
    ldelete(head);
    lfree(head);
}