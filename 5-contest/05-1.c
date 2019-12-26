#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/limits.h>

enum { FIRST_APPEAR = 1, SECOND_APPEAR = 2, NAME_SIZE = 16 };

struct Product 
{
    char name[NAME_SIZE];
    int price;
};

int 
main(int argc, char *argv[])
{
    int i, pre_max = 0, max = 0, tmp = 0, flag = 0;
    struct Product smurf;

    for(i = 1; i < argc; i++) 
    {
        char *file_path = argv[i]; 
        int f = open(file_path, O_RDONLY);
        if(f < 0) {
            continue;
        }

        while(read(f, &smurf, sizeof(smurf)) > 0) {
            if(flag != FIRST_APPEAR && flag != SECOND_APPEAR) {
                pre_max = smurf.price;   
                flag = FIRST_APPEAR; 
            } else if(flag != SECOND_APPEAR) {
                if(smurf.price > pre_max) {
                    max = smurf.price;
                    flag = SECOND_APPEAR;
                } else if(smurf.price < pre_max) {
                    max = pre_max;
                    pre_max = smurf.price;
                    flag = SECOND_APPEAR;
                }
            } else if(flag == SECOND_APPEAR) {
                if(smurf.price > pre_max && smurf.price != max) {
                    pre_max = smurf.price;
                }

                if(pre_max > max)
                {
                    tmp = max;
                    max = pre_max;
                    pre_max = tmp;
                }
            }
        }
        close(f);
    }
    
    double answer = pre_max;
    answer /= 100;

    if(flag == SECOND_APPEAR) {
        printf("%.2lf\n", answer);
    }
    return 0;
}
