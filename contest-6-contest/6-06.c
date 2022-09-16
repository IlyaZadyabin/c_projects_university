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

int elem_found(list *head, int n)
{
    list *tmp = head;

    while(tmp)
    {
        if(tmp->elem == n) return 1;
        tmp = tmp->next;
    }
    return 0;
}

list* list_format(list *head1, list *head2)
{
    list *tmp_head = head1;
    list *tmp;
    list *before = tmp_head;
    //list* del;

    while(tmp_head)
    {
        if(elem_found(head2, tmp_head->elem))
        {
            if(tmp_head == head1)
            {
                head1 = head1->next;
                tmp_head = tmp_head->next;
                before = tmp_head;
                continue;
            }

            tmp = tmp_head->next;
            free(tmp_head);
            before->next = tmp;
            tmp_head = tmp;

        }
        else
        {
            before = tmp_head;
            tmp_head = tmp_head->next;
        }
    }
    return head1;
}

int main(void)
{
    FILE *f1;
    FILE *f2;

    int n;
    list *head1;
    list *head2;

    list *newnode1 = NULL;
    list *newnode2 = NULL;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    while (fscanf (f1, "%d", &n) && (n != -1))
        list_add(&newnode1, n);

    while (fscanf (f1, "%d", &n) && (n != -1))
        list_add(&newnode2, n);

    head1 = newnode1;
    head2 = newnode2;

    head1 = list_format(head1, head2);
    list_print(head1, f2);

    list *q = newnode1;
    while(newnode1)
    {
        newnode1 = newnode1->next;
        free(q);
        q = newnode1;
    }

    q = newnode2;
    while(newnode2)
    {
        newnode2 = newnode2->next;
        free(q);
        q = newnode2;
    }

    fclose (f1);
    fclose (f2);

    return 0;
}
