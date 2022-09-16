#include <stdio.h>
#include <string.h>

#define MAX_N 10

int visited[MAX_N];
int graph[MAX_N][MAX_N];
int level;
int max_len = 0;
int local_max_len = 0;
int lens[MAX_N];
/*
void print_lens(){
  int i;
  printf("lens: ");
  for(i=0;i<MAX_N;i++)
    printf("%d",lens[i]);
  printf("\n");
}
*/

void clear_graph(void)
{
  int i, j;
  for(i=0; i<MAX_N; i++)
    for(j=0; j<MAX_N; j++)
      graph[i][j] = -1;
}
/*
void print_graph()
{
  int i, j;
  for(i=0; i<MAX_N; i++) {
    for(j=0; j<MAX_N; j++)
      printf("%d ", graph[i][j]);
    printf("\n");
  }
}
*/


void search(int v) 
{
  int i;
  int local_cnt;

  //printf("=== %d (level=%d)\n",v,level);
  visited[v] = 1;
  i = 0;
  local_cnt = 0; // how many times we went deeper from v
  while (graph[v][i] != -1){
    if (!visited[graph[v][i]]){
      local_cnt++;
      level++; // go down
      search(graph[v][i]);
    }
    i++;
  }

  if(local_cnt==0){ // It's a leaf
    if(level >= local_max_len){
      local_max_len = level;
      //printf("MaxLen = %d\n",local_max_len);
    }

  }
  level--; // go up
}

//////////////////////////////////////////////////////

int main(void)
{
  int i,j,k;
  int N;
  char cities[MAX_N][21];
  char s[22];
  size_t L;
  int is_printed;

  clear_graph();

  scanf("%d", &N);

  // Read the cities
  for(i = 0; i < N; i++)
  {
      scanf("%s", s);
      strcpy(cities[i], s);
  }

  k=0;
  for(i = 0; i < N; i++)
  {
      L = strlen(cities[i]);
      for(j = 0; j < N; j++)
      {
          if((cities[i][L-1] == cities[j][0]) && (i != j))
          {
              graph[i][k] = j;
              k++;
          }
      }
      k = 0;
  }

  // print_graph();

  // Main cycle
  for(i=0;i<N;i++){

      for(j=0; j<MAX_N; j++)
          visited[j] = 0;

      level = 1;
      local_max_len = 0;
      search(i);

      lens[i] = local_max_len;
      if(local_max_len >= max_len){
          max_len = local_max_len;
      }
  }

   // printf("GlobalMaxLen = %d\n",max_len);
  // print_lens();

  printf("%d\n",max_len);

  // Search for cities having max length
  for(i=0; i<N; i++){
      if(lens[i] == max_len) {

          // Check if printed before
          is_printed = 0;
          for(j=0; j<i; j++){
              if(lens[j] == max_len && strcmp(cities[i], cities[j]) == 0) {
                  //printf("+++ %s-%s\n",cities[i], cities[j]);
                  is_printed = 1;
              }
          }

          if(!is_printed)
              printf("%s\n",cities[i]);

      }
  }
}
