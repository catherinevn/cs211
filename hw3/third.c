#include<stdio.h>
#include<stdlib.h>

int get(unsigned short x, int n) {
  return (x >> n) & 1;
} 

int main(int argc, char* argv[])
{
  int num = atoi(argv[1]);
  unsigned short x = (unsigned short) num;
  int i;
  for (i = 0; i < 8; i++) {
    int front = get(x, i);
    int back = get(x, 15 - i);
    if (front != back) {
      printf("Not-Palindrome\n");
      return 0;
    }
  }
  printf("Is-Palindrome\n");
}