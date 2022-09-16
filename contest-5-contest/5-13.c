#include <stdio.h>
#include <stdlib.h>


/* int N = 2; */
/* int M = 2; */
/* int n0 = 0; */
/* int m0 = 0; */
/* int n1 = 1; */
/* int m1 = 1; */
/* int a[2][2] = {0,10, 30, 20}; */
/* int b[1000][1000]; */


/* int N = 2; */
/* int M = 3; */
/* int n0 = 1; */
/* int m0 = 0; */
/* int n1 = 0; */
/* int m1 = 2; */
/* int a[2][3] = {10,15,9, 8,12,14}; */
/* int b[1000][1000]; */

/* int N = 2; */
/* int M = 1; */
/* int n0 = 1; */
/* int m0 = 0; */
/* int n1 = 1; */
/* int m1 = 0; */
/* int a[2][1] = {10,20}; */


int n0;
int m0;
int n1;
int m1;
int N;
int M;




int MAX_NUM = 100000;

int min(int a, int b, int c, int d) {
  int minimum;
  printf("cp_min: %d, %d, %d, %d\n", a, b, c, d);

  minimum = MAX_NUM;
  if(a < minimum)
    minimum = a;
  if(b < minimum)
    minimum = b;
  if(c < minimum)
    minimum = c;
  if(d < minimum)
    minimum = d;

  return minimum;
}

int depth = 0;

enum Dirs {
  NONE,
  TOP,
  BOT,
  LEFT,
  RIGHT
};



typedef struct point_t {
  int n;
  int m;
}Point;

//typedef struct point_t Point;

int *stack;
int *ptr;

void push(Point p, int **b){
  // // printf("push %d,%d\n",p.n, p.m);
  b[p.n][p.m] = -2;
  *ptr = p.n;
  ptr++;
  *ptr = p.m;
  ptr++;
}


Point pop(void){
  Point p;

  if(ptr == 0){
    printf("Error: Stack underflow!\n");
    exit(1);
  }else{
    ptr--;
    p.m = *ptr--;
    p.n = *ptr;
    // printf("pop %d,%d\n",p.n, p.m);
    return p;
  }
}

Point get(void){
  Point p;

  if(ptr == 0){
    printf("Error: Stack underflow!\n");
    exit(1);
  }else{
    ptr--;
    p.m = *ptr--;
    p.n = *ptr;
    ptr++;
    ptr++;
    // printf("get %d,%d\n",p.n, p.m);
    return p;
  }
}


void min_path(int **a, int **b) {
  Point c_p;
  Point n_p;
  int n, m;
  int min;
  int val;

  while (ptr != stack){
    c_p = get();
    n = c_p.n;
    m = c_p.m;
    // printf("\n(0): %d,%d\n",n,m);
    if(b[n][m] > -1){
        pop();
    }else{

        if (n == n0 && m == m0){
          b[n][m] = 0;
          continue;
        }else{
          if((abs(n - n0) == 1 && m == m0) ||
             (abs(m - m0) == 1 && n == n0)){
                b[n][m] = abs(a[n0][m0] - a[n][m]);
                pop();
                // printf("(1): %d,%d - %d\n",n,m,b[n][m]);
          }else{
              min = MAX_NUM;

              // printf("(2): %d,%d\n",n,m);

              if((n-1) >= 0){
                  if(b[n-1][m] == -1){
                      n_p.n = n-1;
                      n_p.m = m;
                      push(n_p, b);
                      continue;
                  }else if(b[n-1][m] != -2){
                      val = b[n-1][m] + abs(a[n-1][m] - a[n][m]);
                      if(val < min){
                          min = val;
                          // printf("cp0: min=%d\n", min);
                      }
                  }
              }

              if((n+1) < N){
                  if(b[n+1][m] == -1){
                      n_p.n = n+1;
                      n_p.m = m;
                      push(n_p, b);
                      continue;
                  }else if(b[n+1][m] != -2){
                      val = b[n+1][m] + abs(a[n+1][m] - a[n][m]);
                      if(val < min){
                          min = val;
                          // printf("cp1: min=%d\n", min);
                      }
                  }
              }

              if((m-1) >= 0){
                  if(b[n][m-1] == -1){
                      n_p.n = n;
                      n_p.m = m-1;
                      push(n_p, b);
                      continue;
                  }else if(b[n][m-1] != -2){
                      val = b[n][m-1] + abs(a[n][m-1] - a[n][m]);
                      if(val < min){
                          min = val;
                          // printf("cp2: min=%d\n", min);
                      }
                  }
              }

              if((m+1) < M){
                  if(b[n][m+1] == -1){
                      n_p.n = n;
                      n_p.m = m+1;
                      push(n_p, b);
                      continue;
                  }else if(b[n][m+1] != -2){
                      val = b[n][m+1] + abs(a[n][m+1] - a[n][m]);
                      if(val < min){
                          min = val;
                          // printf("cp3: min=%d\n", min);
                      }
                  }
              }
              b[n][m] = min;
              pop();
              // printf("(3): %d,%d - %d\n",n,m,b[n][m]);
          }
        }
    }
  }
}


int main(void){
  int i, j;
  Point p;
  int N;
  int M;

  stack = (int*) malloc(3000000 * sizeof(Point));
  ptr = stack;

  scanf("%d %d %d %d %d %d", &N, &M, &n0, &m0, &n1, &m1);

  int **a = (int**) malloc(N * sizeof(int*));
  int **b = (int**) malloc(N * sizeof(int*));

  for(i = 0; i < N; i++){
    a[i] = (int*) malloc(M * sizeof(int));
    b[i] = (int*) malloc(M * sizeof(int));
  }
    


  for(i=0; i<N; i++)
    for(j=0; j<M; j++){
      scanf("%d", &a[i][j]);
      b[i][j] = -1;
    }

  p.n = n1;
  p.m = m1;
  push(p, b);

  min_path(a, b);

  printf("%d\n",b[n1][m1]);
}
