#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

unsigned short reverse16(unsigned short d)
{
    return (d<<8) | (d>>8);
}

int reverse32(int d)
{
    int i;
    int res;

    res = 0;
    for(i = 0; i < 3; i++)
    {
        res = res | (d & 0xff);
        d = d >> 8;
        res = res << 8;
    }
    res = res | (d & 0xff);
    return res;
}

long long int reverse64(long long int d)
{
    int i;
    long long int res;

    res = 0;
    for(i = 0; i < 7; i++)
    {
        res = res | (d & 0xff);
        d = d >> 8;
        res = res << 8;
    }
    res = res | (d & 0xff);
    return res;
}


int main(void)
{
    FILE *fin;
    FILE *fout;

    short size;
    int *buf;
    long long int answer;
    int i;
    int idx;

    fin = fopen("matrix.in", "rb");
    fout = fopen("trace.out", "wb");

    fread(&size, 2 * sizeof(char), 1, fin);
    size = reverse16(size);

    buf = (int*) malloc(size * size * sizeof(int));
    fread(buf, size * size * sizeof(int), 1, fin);

    answer = 0;
    for(i = 0; i < size; i++)
    {
        idx = i * (size + 1);
        answer += reverse32(buf[idx]);
    }

    answer = reverse64(answer);
    fwrite(&answer, 8 * sizeof(char), 1, fout);

    fclose(fin);
    fclose(fout);
    free(buf);
    return 0;
}
