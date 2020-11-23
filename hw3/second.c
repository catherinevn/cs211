#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
  int num = atoi(argv[1]);
  unsigned short x = (unsigned short) num;
  int pairs = 0;
  int ones = 0;
  while (x) {
    if (x & 1) {
      ones++;
      x >>= 1;
      if (x & 1) {
        ones++;
        pairs++;
      }
      x >>= 1;
    }
    else {
      x >>= 1;
    }
  }
  if (ones % 2 == 0) {
    printf("Even-Parity\t");
  }
  else {
    printf("Odd-Parity\t");
  }
  printf("%d \n", pairs);
}