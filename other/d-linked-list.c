#include <stdio.h>
#include <stdlib.h>

struct DNode
{
    int val;
    DNode *prev;
    DNode *next;
};
typedef struct DNode DNode;

DNode *first;
DNode *last;

DNode *makeNode(int v)
{
    DNode *p = (DNode *)malloc(sizeof(DNode));
    p->val = v;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void remove(DNode *p)
{
    if (p == NULL)
    {
        return;
    }
    if (first == last && p == first)
    {
        first = NULL;
        last = NULL;
        free(p);
    }
    if (p == first)
    {
        first = p->next;
        first->prev = NULL;
        free(p);
        return;
    }
    if (p == last)
    {
        last = p->prev;
        last->next = NULL;
        free(p);
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
}

void insertLast(int x)
{
    DNode *q = makeNode(x);
    if (first == NULL && last == NULL)
    {
        first = q;
        last = q;
        return;
    }
    q->prev = last;
    last->next = q;
    last = q;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
