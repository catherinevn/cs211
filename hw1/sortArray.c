#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int len;
  FILE *fp  = fopen(argv[1], "r");
  if (fp == NULL) {
    return 1;
  }
  fscanf(fp, "%d", &len);
  int array[len];
  int n = 0;
  int count;
  for (count = 0; count < len; count++) {
    fscanf(fp, "%d", &n);
    array[count] = n;
  }
  fclose(fp);
  int i;
  int index = 0;
  for (i = 0; i < len; i++) {
    int evenMin = array[i];
    int j;
    // evens
    for (j = i; j < len; j++) {
      if (evenMin % 2 != 0 && array[j] % 2 == 0) {
        int temp = evenMin;
        evenMin = array[j];
        array[i] = array[j];
        array[j] = temp;
      }
      if (evenMin > array[j] && array[j] % 2 == 0) {
        int temp = evenMin;
        evenMin = array[j];
        array[i] = array[j];
        array[j] = temp;
      }
    }
    if (evenMin % 2 != 0) {
      index = i;
      break;
    }
  }
  int j;
  for (j = index; j < len; j++) {
    int oddMax = array[j];
    int k;
    for (k = j; k < len; k++) {
      if (oddMax < array[k]) {
        int temp = oddMax;
        oddMax = array[k];
        array[j] = array[k];
        array[k] = temp;
      }
    }
  }
  int k;
  for (k = 0; k < len; k++) {
    printf("%d\t", array[k]);
  }
}