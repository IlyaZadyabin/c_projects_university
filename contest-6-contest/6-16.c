#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define SIZE 100000

typedef struct list
{
    int elem;
    struct list *next;
} list;

typedef struct stack
{
    int level;
    list* item;
}stack;

stack Stack[32];

void list_print(list* head, FILE *f2)
{
    list *tmp = head;

    while(tmp != NULL)
    {
        fprintf (f2, "%d ", tmp->elem);
        tmp = tmp->next;
    }
}

list* Unification(list* list1, list* list2)
{
    list* p1 = list1;
    list* p2 = list2;
    list* cur_pointer;

    if (p1->elem > p2->elem)
    {
        cur_pointer = p2;
        p2 = p2->next;
    }
    else
    {
        cur_pointer = p1;
        p1 = p1->next;
    }

    list* begin = cur_pointer;

    while(p1 && p2)
    {
        if (p1->elem > p2->elem)
        {
            cur_pointer->next = p2;
            cur_pointer = p2;
            p2 = p2->next;
        }
        else
        {
            cur_pointer->next = p1;
            cur_pointer = p1;
            p1 = p1->next;
        }
    }

    if(p1)
        cur_pointer->next = p1;
    else
        cur_pointer->next = p2;

    return begin;
}

list *final_sort(list* sorted_list)
{
    int stack_pos = 0;
    list* p = sorted_list;
    while (p)
    {
        Stack[stack_pos].level = 1;
        Stack[stack_pos].item = p;
        p = p->next;
        Stack[stack_pos].item->next = NULL;
        stack_pos++;

        while ((stack_pos > 1) && (Stack[stack_pos - 1].level == Stack[stack_pos - 2].level))
        {
            Stack[stack_pos - 2].item = Unification(Stack[stack_pos - 1].item, Stack[stack_pos - 2].item);
            Stack[stack_pos - 2].level++;
            stack_pos--;
        }
    }

    while (stack_pos > 1)
    {
        Stack[stack_pos - 2].item = Unification(Stack[stack_pos - 1].item, Stack[stack_pos - 2].item);
        Stack[stack_pos - 2].level++;
        stack_pos--;
    }

    if(stack_pos) sorted_list = Stack[0].item;

    return sorted_list;
}

int main(void)
{
    FILE *fin;
    FILE *fout;

    int n;

    list *sortednode;
    list *newnode = (list*) malloc(SIZE * sizeof(list));

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");

    list* tmp = newnode;

    fscanf (fin, "%d", &n);
    tmp->next = NULL;
    tmp->elem = n;

    while (fscanf (fin, "%d", &n) == 1)
    {
        tmp->next = tmp+1;
        tmp++;
        tmp->elem = n;
        tmp->next = NULL;
    }
    
    sortednode = final_sort(newnode);

    list_print(sortednode, fout);

    free(newnode);
    fclose (fin);
    fclose (fout);

    return 0;
}
