#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE 100000

typedef struct list
{
    int elem; 
    struct list *next; 
    struct list *prvs;
}list;

list** pointers;

void make_list(list *q, int N) 
{
    int i;
    list* tmp = NULL;

    for(i = 1; i < N; i++)
    {
        q->elem = i;
        q->next = q+1;
        q->prvs = tmp;
        tmp = q;
        q++;
    }
    q->elem = N;
    q->next = NULL;
    q->prvs = tmp;
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

list *list_shift(list *head, int a, int b)
{
    list* tmp = head;
    list* first = NULL;
    list* second = NULL;
    list* end = NULL;
    list* previous = tmp;
 
    first = pointers[a];
    second = pointers[b];

    if(second->next)
    {
        end = second->next;
        end->prvs = second;
    }
    else
        end = NULL;
    
    previous = first->prvs;

    if(head != first)
    {
        previous->next = end;
        if(end) end->prvs = previous;

        second->next = head;
        head->prvs = second;
        head = first;
    }

    return head;
}

int main(void)
{
    FILE *f1;
    FILE *f2;

    int N, M, a, b;

    list *newnode = (list*) malloc(SIZE * sizeof(list));

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    fscanf (f1, "%d %d", &N, &M); 

    make_list(newnode, N);

    pointers = (list**) malloc((SIZE+1) * sizeof(list*));

    list *tmp = newnode;

    int i;
    for(i = 1; tmp; i++)
    {
        pointers[i] = tmp;
        tmp = tmp->next;
    }

    tmp = newnode;

    while (fscanf (f1, "%d %d", &a, &b) != EOF)
        tmp = list_shift(tmp, a, b);
    
    list_print(tmp, f2);
 
    free(newnode);
    free(pointers);
    fclose (f1);
    fclose (f2);

    return 0;
}
