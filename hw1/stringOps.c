#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  char vowel[100];
  int i;
  for (i = 1; i < argc; i++) {
    char* curr = argv[i];
    int j = 0;
    while (curr[j] != '\0') {
      char ch = curr[j];
      if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
        strncat(vowel, &ch, 1);
        printf("%c", ch);
      }
      j++;
    }
  }
}
