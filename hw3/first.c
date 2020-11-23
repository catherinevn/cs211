#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int get(unsigned short x, int n) {
  return (x >> n) & 1;
} 

unsigned short set(unsigned short x, int n, int v) {
  return (x & (~(1 << n))) | (v << n);
}

unsigned short comp(unsigned short x, int n) {
  return x ^ 1 << n;
}

int main(int argc, char* argv[])
{
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("error");
    return 0;
  }
  unsigned short x;
  fscanf(fp, "%hu", &x);
  int ch;
  char op[5];
  int first;
  int second;
  while (ch != EOF) {
    fscanf(fp, "%s", op);
    if (strcmp(op, "get") == 0) {
      fscanf(fp, "%d %d", &first, &second);
      int bit = get(x, first);
      printf("%d \t", bit);
    }
    if (strcmp(op, "set") == 0) {
      fscanf(fp, "%d %d", &first, &second);
      x = set(x, first, second);
      printf("%hu", x);
    }
    if (strcmp(op, "comp") == 0) {
      fscanf(fp, "%d %d", &first, &second);
      x = comp(x, first);
      printf("%hu", x);
    }
    printf("\n");
    op[0] = " ";
    ch = getc(fp);
  }
  fclose(fp);
}