#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

int ** goal;
int N;
void allocate_mem(int ** * arr) {
  * arr = (int ** ) malloc(N * sizeof(int * ));
  int i;
  for (i = 0; i < N; i++)
    ( * arr)[i] = (int * ) malloc(N * sizeof(int));
}
void deallocate_mem(int ** * arr) {
  int i, N;
  for (i = 0; i < N; i++)
    free(( * arr)[i]);
  free( * arr);
}
void createTiles(int ** tiles, int ** arr) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      tiles[i][j] = arr[i][j];
}

void createGoal(void) {
  int i, j;
  allocate_mem( & goal);
  int filler = 1;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i == N - 1 && j == N - 1)
        goal[i][j] = 0;
      else
        goal[i][j] = filler++;
    }
  }
}
void display(int ** t) {
  int i, j;
  printf("\n%d\n", N);
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (t[i][j] == 0) printf("  ");
      else
        printf("%d ", t[i][j]);
    }
    printf("\n");
  }
}
int hamming(int ** tiles) {
  int count = 0, j, i;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      if (tiles[i][j] == 0) continue;
      if (tiles[i][j] != goal[i][j]) count++;
    }
  return count;
}

bool isGoal(int ** t) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (t[i][j] != goal[i][j]) return false;
  return true;
}

bool equals(int ** p, int ** q) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      if (p[i][j] != q[i][j]) return false;
  return true;
}
void swap(int ** surface, int x1, int y1, int x2, int y2) {
  int temp = surface[x1][y1];
  surface[x1][y1] = surface[x2][y2];
  surface[x2][y2] = temp;
}
void copy(int ** toRet, int ** origin) {
  int i, j;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      toRet[i][j] = origin[i][j];
}
//finds twin of board by exchanging any two blocks
void boardTwin(int ** toRet) {
  int i, j;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N - 1; j++) {
      if (toRet[i][j] != 0 && toRet[i][j + 1] != 0) {
        swap(toRet, i, j, i, j + 1);
      }
    }
  }
}
typedef struct board_ {
  int ** data;
  // Lower values indicate higher priority 
  int cost;
  int level;
  struct board_ * parent;

}
board;

board * newBoard(int ** arr, board * parent, int level) {
  board * temp = (board * ) malloc(sizeof(board));
  allocate_mem( & (temp -> data));
  createTiles(temp -> data, arr);
  temp -> cost = hamming(arr);
  temp -> level = level;
  temp -> parent = parent;
  return temp;
}
