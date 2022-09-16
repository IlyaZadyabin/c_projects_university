#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 26
#define SIZE 2002

int ans = 0;

typedef struct treenode
{
    struct treenode* next[N];
}treenode;

treenode* add_elem(treenode *root, char a[], int len)
{
    int i, j;
    treenode* letter;
    treenode* begin = root;

    for(i = 0; i < len; i++)
    {
        if((a[i] >= 'a') && (a[i] <= 'z'))
        {
            letter = root -> next[a[i] - 'a'];
            if (letter == NULL)
            {
                letter = (treenode*) malloc (sizeof(treenode));
                for (j = 0; j < N; j++)
                    letter -> next[j] = NULL;
            }
            root = root -> next[a[i] - 'a'] = letter;
        }
    }
    return begin;
}

int count(treenode *root)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (root -> next[i])
        {
            ans++; 
            count(root -> next[i]);
        }
    }
    return 0;
}

int main(void)
{
    int i;
    treenode* root = (treenode*) malloc (sizeof (treenode));

    for (i = 0; i < N; i++)
        root -> next[i] = NULL;

    char a[SIZE];
    scanf ("%s", a);
    int len = strlen (a);

    for (i = 0; i < len; i++)
        root = add_elem(root, &a[i], len - i);

    count(root);
    ans++;
    printf ("%d", ans);
    free(root);
    return 0;
}
