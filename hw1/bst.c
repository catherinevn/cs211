#include <stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
  int data;
  struct TreeNode *right;
  struct TreeNode *left;
} TreeNode;

void freeOne(TreeNode* head) {
  free(head);
}

void freeNodes(TreeNode* head) {
  if (head == NULL) {
    return;
  }
  freeNodes(head->right);
  freeNodes(head->left);
  freeOne(head);
}

void inorder(TreeNode* head) {
  if (head == NULL) {
    return;
  }
  inorder(head->left);
  printf("%d\t", head->data);
  inorder(head->right);
}

TreeNode* insert(TreeNode* head, int n) {
  TreeNode* add = (TreeNode*) malloc(sizeof(TreeNode));
  add->data = n;
  add->right = NULL;
  add->left = NULL;
  if (head == NULL) {
    return add;
  }
  TreeNode* prev = NULL;
  TreeNode* ptr = head;
  while (ptr != NULL) {
    if (ptr->data == n) {
      freeOne(add);
      return head;
    }
    else if (ptr->data < n) {
      prev = ptr;
      ptr = ptr->right;
    }
    else {
      prev = ptr;
      ptr = ptr->left;
    }
  }
  if (prev->data < n) {
    prev->right = add;
  }
  else {
    prev->left = add;
  }
  return head;
}

int main(int argc, char* argv[])
{
  TreeNode* head = NULL;
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
    head = insert(head, n);
    ch = getc(fp);
  }
  fclose(fp);
  inorder(head);
  freeNodes(head);
}
