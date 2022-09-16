#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE 102
#define BIG unsigned long long int
#define MAX 100000

int idx_hash(BIG key)
{
    return key % MAX;
}

struct htype
{
    unsigned long long int key;
    unsigned int val;
    struct htype *next;
    struct htype *prvs;
};
struct htype *idx[MAX];

BIG power[SIZE + 1];

BIG get_hash(char *s)
{
    BIG hs[102];
    hs[0] = s[0];

    int i;
    int n = strlen(s);
    for (i = 1; i < n; i++)
        hs[i] = (hs[i - 1] + power[i] * s[i]);
    return hs[i - 1];
}

void init(void)
{
    int i;
    for (i = 0; i < MAX; i++)
        idx[i] = NULL;
}

struct htype *search(BIG k)
{
    int h = idx_hash(k);
    if (idx[h])
    {
        struct htype *p = idx[h];
        while (p)
        {
            if (p->key == k)
                return p;
            else
                p = p->next;
        } 
    }
    return NULL;
}

struct htype *empty (void)
{
    struct htype *p;
    p = (struct htype*)malloc(sizeof(struct htype));

    p->key = -1;
    p->val = 0;
    p->next = NULL;
    p->prvs = NULL;
    return p;
}

int search_internal(BIG k, struct htype **r)
{
    struct htype *p, *q;
    p = idx[idx_hash(k)];

    if (p != NULL)
    {
        while (p)
        {
            if (p->key == k)
            {
                *r = p;
                return 1;
            }
            else
            {
                q = p;
                p = p->next;
            }
        } 
        *r = q;
    }
    else
        *r = NULL;
    return 0;
}

void insert(BIG k, unsigned int v)
{
    struct htype *p, *q;

    if (search_internal(k, &p))
        p->val = v;
    else
    {
        q = empty();
        q->key = k;
        q->val = v;
   
        if(p)
        {
            p->next = q;
            q->prvs = p;
        }
        else
            idx[idx_hash(k)] = q;
    }
}

void delete_memory(void)
{
    int i;
    for(i = 0; i < MAX; i++)
    {
        struct htype *p = idx[i];
        if(p)
        {
            while(p->next)
            {
                p = p->next;
                free(p->prvs);
            }
            free(p);
        }
    }
}

int main(void)
{
    BIG p = 701;
    power[0] = 1;
    int i;
    for (i = 1; i <= SIZE; i++)
        power[i] = power[i - 1] * p;

    FILE *f1;
    FILE *f2;
    char s[SIZE];
    BIG hash;
    struct htype *idx_search;

    int N, M;
    unsigned int IP;

    f1 = fopen("input.txt", "r");
    f2 = fopen("output.txt", "w");

    fscanf(f1, "%d", &N);
    for (i = 0; i < N; i++)
    {
        fscanf(f1, "%s %u", s, &IP);
        hash = get_hash(s);
        insert(hash, IP);
    }

    fscanf(f1, "%d", &M);
    for (i = 0; i < M; i++)
    {
        fscanf(f1, "%s", s);
        hash = get_hash(s);
        idx_search = search(hash);
        
        if (idx_search)
            fprintf(f2, "%u\n", idx_search->val);
        else
            fprintf(f2, "%d\n", -1);
    }
    
    delete_memory();
    fclose(f1);
    fclose(f2);
    return 0;
}
