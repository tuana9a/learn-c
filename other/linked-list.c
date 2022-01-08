#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};
typedef struct Node Node;

Node *head;

void printList(Node *h)
{
    Node *p = h;
    while (p != NULL)
    {
        printf("%d ", p->value);
        p = p->next;
    }
}

Node *findLast(Node *h)
{
    Node *p = h;
    while (p != NULL)
    {
        if (p->next == NULL)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

Node *makeNode(int x)
{
    Node *q = (Node *)malloc(sizeof(Node));
    q->value = x;
    q->next = NULL;
    return q;
}

Node *insertAfter(Node *h, Node *p, int x)
{
    if (p == NULL)
    {
        return h;
    }
    Node *q = makeNode(x);
    if (h == NULL)
    {
        return q;
    }
    q->next = p->next;
    p->next = q;
    return h;
}

Node *insertLast(Node *h, int x)
{
    Node *q = makeNode(x);
    if (h == NULL)
    {
        return q;
    }
    Node *p = h;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = q;
    return h;
}

Node *locate(Node *h, int x)
{
    Node *p = h;
    while (p != NULL)
    {
        if (p->value == x)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// tìm node trước node p
Node *prev(Node *h, Node *p)
{
    Node *q = h;
    while (q != NULL)
    {
        if (q->next == p)
        {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

Node *insertAt(Node *h, Node *p, int x)
{
    Node *pp = prev(h, p);
    if (pp == NULL && p != NULL)
    {
        return h;
    }
    Node *q = makeNode(x);
    if (pp == NULL)
    {
        if (h == NULL)
        {
            return q;
        }
        q->next = h;
        return q;
    }
    q->next = p;
    pp->next = q;
    return h;
}

Node *insertAt_Recursive(Node *h, Node *p, int x)
{
    if (p == NULL)
    {
        return h;
    }
    if (h == NULL || p == h)
    {
        return makeNode(x);
    }
    else
    {
        h->next = insertAt_Recursive(h->next, p, x);
        return h;
    }
}

Node *removeNode(Node *h, Node *p)
{
    if (h == NULL || p == NULL)
    {
        return h;
    }
    if (h == p)
    {
        h = h->next;
        free(p);
        return h;
    }
    else
    {
        h->next = removeNode(h->next, p);
        return h;
    }
}

int sum(Node *h)
{
    Node *p = h;
    int S = 0;
    while (p != NULL)
    {
        S = S + p->value;
        p = p->next;
    }
    return S;
}

int sum_Recursive(Node *h)
{
    if (h == NULL)
    {
        return 0;
    }
    return h->value + sum_Recursive(h->next);
}

int main(int argc, char const *argv[])
{
    // test();
    head = makeNode(1);
    insertLast(head, 2);
    insertLast(head, 3);
    insertLast(head, 4);
    insertLast(head, 5);
    insertLast(head, 6);
    printList(head);

    return 0;
}
