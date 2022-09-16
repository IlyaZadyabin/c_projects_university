#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define SIZE 30000

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void reverse(int *s, int len)
{
    int i, j, tmp;
    j = 0;

    for(i = len-1; j < i; i--)
    {
        tmp = s[j];
        s[j] = s[i];
        s[i] = tmp;
        j++;
    }
}

int *max_string(int *s1, int *s2, int l1, int l2)
{
    int i;

    if(l1 < l2)
        return s2;
    if(l1 > l2)
        return s1;

    for(i = 0; i < l1; i++)
    {
        if(s1[i] > s2[i])
            return s1;
        if(s1[i] < s2[i])
            return s2;
    }
    return s1;
}

int substraction(int *sub, int *s1, int *s2, int l1, int l2)
{
    int i, extra, result;
    extra = 0;
    int flag = 1;

    int len = max(l1, l2);

    for(i = min(l1, l2); i < len; i++)
    {
        if(l1 < l2) s1[i] = 0;
        else s2[i] = 0;
    }

    for(i = 0; i < len; i++)
    {
        s1[i] += extra;

        if (s1[i] < s2[i])
        {
            result = s1[i] - s2[i] + 10;
            extra = -1;
        }
        else
        {
            result = s1[i] - s2[i];
            extra = 0;
        }

        sub[i] = result;

        if(result != 0) flag = i+1;
    }

    /*
    if((sub[i-1] == 0) && (flag)) len--;
    //printf("LEN = %d\n", len);
    for(i = i - 1; i >=0; i--)
    {
        if(sub[i] != 0) flag = 0;
    }

    if(sub[len-1] == 0)
        return 1;
        */

    return flag;
}

int addition(int *sum, int *s1, int *s2, int l1, int l2)
{
    int i, rest, extra, result;
    extra = 0;
    rest = 0;

    int len = max(l1, l2);

    for(i = min(l1, l2); i < len; i++)
    {
        if(l1 < l2) s1[i] = 0;
        else s2[i] = 0;
    }

    for(i = 0; i < len; i++)
    {
        result = s1[i] - 0 + s2[i] - 0 + extra;
        rest = result % 10;
        extra = result / 10;
        sum[i] = rest;
    }

    if(extra != 0)
    {
        sum[i] = extra;
        len++;
    }
    return len;
}

int multiplication(int *mult, int *s1, int *s2, int l1, int l2)
{
    int i, j, t, extra;
    t = 0;
    extra = 0;

    for(i = 0; i < l1 + l2; i++) mult[i] = 0;

    for(i = 0; i < l2; i++)
    {
        t = i;

        for(j = 0; j < l1; j++)
        {
            mult[t] += s1[j] * s2[i];
            t++;
        }
    }

    for(i = 0; ; i++)
    {
        mult[i] += extra;
        extra = mult[i] / 10;
        mult[i] %= 10;

        if(i >= t)
            if(mult[i] == 0)
                break;
    }

    if(mult[i-1] == 0) return 1;

    return i;
}

void transform(char *s, int *s_new, int length)
{
    int i;

    for(i = 0; i < length; i++)
        s_new[i] = s[i] - '0';
}

int main(void)
{
    int i, flag, operation, negative, j, len;
    flag = operation = negative = j = len = 0;
    int* s1;
    int* s2, tmp_l;

    char *str1 = (char*) malloc(SIZE * sizeof(char));

    int *answer = (int*) malloc(SIZE* sizeof(int));
    answer[0] = 0;

    fgets(str1, SIZE, stdin);

    int l1 = strlen(str1) - 1;
    int big = l1;
    int l2 = 0;

    s1 = (int*) malloc(SIZE * sizeof(int));
    s2 = (int*) malloc(SIZE * sizeof(int));

    transform(str1, s1, l1);

    for(i = 0; i < big; i++)
    {
        if(flag)
        {
            s2[j] = s1[i];
            j++;
            l2++;
        }

        if(s1[i] == '+' - '0')
        {
            operation = '+';
            flag = 1;
            l1 = i;
        }

        if(s1[i] == '-' - '0')
        {
            operation = '-';
            flag = 1;
            l1 = i;
        }

        if(s1[i] == '*' - '0')
        {
            operation = '*';
            flag = 1;
            l1 = i;
        }
    }

    int *tmp_string = max_string(s1, s2, l1, l2);

    if(s1 != tmp_string)
    {
        negative = 1;
        s2 = s1;
        s1 = tmp_string;

        tmp_l = l1;
        l1 = l2;
        l2 = tmp_l;
    }

    reverse(s1, l1);
    reverse(s2, l2);

    if(operation == '+') len = addition(answer, s1, s2, l1, l2);

    if(operation == '-') len = substraction(answer, s1, s2, l1, l2);

    if(operation == '*') len = multiplication(answer, s1, s2, l1, l2);

    reverse(answer, len);

    if((operation == '-') && negative) printf("-");

    for(i = 0; i < len; i++) printf("%d", answer[i]);


    free(str1);
    free(answer);
    free(s1);
    free(s2);
}
