#include <stdio.h>
#include <stdlib.h>

struct Pair
{
    int key;
    int value;
};

int
comparator(const void * a, const void * b) {
    struct Pair *first = (struct Pair *) a;
    struct Pair *second = (struct Pair *) b;

    return first->key == second->key ? (first->value > second->value ? 1 : -1) : 
            (first->key > second->key ? 1 : -1);
}

void
process(struct Pair *data, size_t size)
{
    int i;
    int *backup_value = calloc(size, sizeof(*backup_value));
    if(backup_value == NULL) {
        return;
    }

    for(i = 0; i < size; i++) {
        backup_value[i] = data[i].value;
        data[i].value = i;
    }

    qsort(data, size, sizeof(struct Pair), comparator);

    for(i = 0; i < size; i++) {
        data[i].value = backup_value[data[i].value];
    }

    free(backup_value);
}
