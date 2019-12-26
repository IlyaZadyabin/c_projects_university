#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum { OCTAL_BASE = 8 };

int 
main(int argc, char **argv)
{   
    const char example[] = "rwxrwxrwx";
    char *end;
    long x;
    char ans[sizeof(example)];
    int i, j;

    for(i = 1; i < argc; i++) {
        x = strtol(argv[i], &end, OCTAL_BASE);
        snprintf(ans, sizeof(example), "%s", example);

        for(j = OCTAL_BASE; j >= 0; j--) 
        {
            if((x & 1) == 0) {
                ans[j] = '-';
            }
            x >>= 1;
        }
        printf("%s\n", ans);
    }
}
