#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct list
{
    int elem;
    struct list *next;
}list;

void list_add(list **q, int num)
{
    list *tmp;

    tmp = *q;

    if(*q == NULL)
    {
        *q = (list*) malloc(sizeof(list));
        tmp = *q;
    }
    else
    {
        while(tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = (list*) malloc(sizeof(list));
        tmp = tmp->next;
    }

    tmp->elem = num;
    tmp->next = NULL;
}

void list_print(list* head, FILE *f2)
{
    list *tmp = head;

    while(tmp != NULL)
    {
        fprintf (f2, "%d ", tmp->elem);
        tmp = tmp->next;
    }
}

list* list_sort(list *head)
{
    list *a = NULL;
    list *b = NULL;
    list *tmp = NULL;
    list *before = NULL;
    list *end = NULL;

    while(end != head->next)
    {
        before = a = head;
        b = a->next;

        while(a != end)
        {
            if(a->elem > b->elem)
            {
                tmp = b -> next;
                b->next = a;
                a->next = tmp;

                if(a == head)
                {
                    head = b;
                    before = b;
                }
                else
                {
                    before->next = b;
                    before = b;
                }
            }
            else
            {
                before = a;
                a = a->next;
            }

            b = a->next;
            if(b == end) end = a;
        }
    }
    return head;
}

int main(void)
{
    FILE *f1;
    FILE *f2;

    int n;
    list *head;

    list *newnode = NULL;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    while (fscanf (f1, "%d", &n) == 1)
        list_add(&newnode, n);

    head = newnode;
    head = list_sort(head);
    list_print(head, f2);


    list *q = newnode;
    while(newnode)
    {
        newnode = newnode->next;
        free(q);
        q = newnode;
    }

    fclose (f1);
    fclose (f2);
    return 0;
}
