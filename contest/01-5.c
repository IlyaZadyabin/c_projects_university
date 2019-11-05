#include <stdio.h> 

void
GCD_extended (int a, int b, int *final_x, int *final_y)
{
    int x = 0, y = 1, frac = 0, tmp = 0;
    *final_x = 1, *final_y = 0;

    while (b != 0) {
        frac = a / b;
        tmp = b, b = a % b, a = tmp;

        tmp = *final_x - frac * x;
        *final_x = x, x = tmp;

        tmp = *final_y - frac * y;
        *final_y = y, y = tmp;
    }
}
 
int
mod_inversion (int b, int m) 
{ 
    int x, y;
    GCD_extended (b, m, &x, &y);  

    return (x % m + m) % m; 
} 

int
mod_division (int a, int b, int m) 
{ 
    a %= m; 
    int inv = mod_inversion (b, m); 
	
    return (inv * a) % m; 
}  

int
main(void) 
{ 
    int i, j, N;
    scanf("%d", &N);

    for (i = 0; i < N; i++){
        for (j = 1; j < N; j++) {
            printf("%d ", mod_division(i, j, N));
        }
        printf("\n");
    }
    return 0;
}
