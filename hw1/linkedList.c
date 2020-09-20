#include <stdio.h>
#include<stdlib.h>

typedef struct Node
{
  int data;
  struct Node *next;
} Node;

void print(Node* head) {
  Node* ptr = head;
  while (ptr != NULL) {
    printf("%d\t", ptr->data);
    ptr = ptr->next;
  }
}

void freeOne(Node* head) {
  free(head);
}

Node* insert(Node* head, int n) {
  Node* add = (Node*) malloc(sizeof(Node));
  add -> data = n;
  add -> next = NULL;
  if (head == NULL) {
    return add;
  }
  Node* prev = NULL;
  Node* ptr = head;
  if (add->data < ptr->data) {
    add->next = head;
    return add;
  }
  while (ptr != NULL) {
    if (ptr->data <= add-> data) {
      prev = ptr;
    }
    else {
      prev->next = add;
      add->next = ptr;
      break;
    }
    ptr = ptr->next;
  }
  if (ptr == NULL) {
    prev->next = add;
  }
  return head;
}

Node* delete(Node* head, int data) {
  if (head == NULL) {
    return NULL;
  }
  if (head->data == data) {
    Node* temp = head;
    head = head->next;
    freeOne(temp);
    return head;
  }
  Node* prev = NULL;
  Node* ptr = head;
  while (ptr != NULL) {
    if (ptr->data == data) {
      Node* temp = ptr;
      ptr = ptr->next;
      prev->next = ptr;
      freeOne(temp);
      break;
    }
    else {
      prev = ptr;
      ptr = ptr->next;
    }
  }
  return head;
}

void freeNodes(Node* head) {
  Node* ptr = NULL;
  while (head != NULL) {
    ptr = head;
    head = head->next;
    free(ptr);
  }
}

int count(Node* head) {
  int count = 0;
  Node* ptr = head;
  while (ptr != NULL) {
    count++;
    ptr = ptr->next;
  }
  return count;
}

int main(int argc, char* argv[])
{
  Node* head = NULL;
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
      head = insert(head, n);
    }
    // if op == 'd', delete
    if (op == 'd') {
      head = delete(head, n);
    }
    ch = getc(fp);
  }
  fclose(fp);
  if (head == NULL) {
    printf("%d", 0);
  }
  else {
    printf("%d\n", count(head));
  }
  // printing 
  print(head);
  // freeing everything
  freeNodes(head);
}
