#include <stdio.h>
#include<stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

struct Node* hTable[10000];

void freeTable(Node* first) {
  Node* ptr = NULL;
  while (first != NULL) {
    ptr = first;
    first = first->next;
    free(ptr);
  }
}

int insert(int n, int hashcode) {
  int collisions = 0;
  if (hTable[hashcode] != NULL) {
    collisions += 1;
  }
  Node* item = (Node*) malloc(sizeof(Node));
  item->data = n;
  item->next = hTable[hashcode];
  hTable[hashcode] = item;
  return collisions;
}

int search(int n, int hashcode) {
  Node* ptr = hTable[hashcode];
  while (ptr != NULL) {
    if (ptr->data == n) {
      return 1;
    }
    ptr = ptr->next;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  int searchCount = 0;
  int collisionCount = 0;
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("error");
    return 0;
  }
  int ch = 0;
  char op;
  int n = 0;
  while (ch != EOF) {
    fscanf(fp, "%c %d", &op, &n);

    // if op == 'i', insert
    if (op == 'i') {
      int hashcode = n % 10000;
      if (hashcode < 0) {
        hashcode += 10000;
      }
      collisionCount += insert(n, hashcode);
    }
    // if op == 's', search
    if (op == 's') {
      int hashcode = n % 10000;
      if (hashcode < 0) {
        hashcode += 10000;
      }
      searchCount += search(n, hashcode);
    }
    ch = getc(fp);
  }
  fclose(fp);
  printf("%d\n", collisionCount);
  printf("%d\n", searchCount);
  for (int i = 0; i < 10000; i++) {
    freeTable(hTable[i]);
  }
}
