#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int Registers[4]; 
char Instructions[100][30]; 

int registerRead(char string[30]) {
  if (strcmp(string, "ax") == 0) {
    return 0;
  }
  else if (strcmp(string, "bx") == 0) {
    return 1;
  }
  else if (strcmp(string, "cx") == 0) {
    return 2;
  }
  else if (strcmp(string, "dx") == 0) {
    return 3;
  }
  else {
    return 4;
  }
}

void read(char reg[30]) {
  int x;
  scanf("%d", &x);
  Registers[registerRead(reg)] = x;
  return;
}

void mov(char source[30], char dest[30]) {
  int src;
  if (registerRead(source) < 4) {
    src = Registers[registerRead(source)];
  }
  else {
    src = atoi(source);
  }
  Registers[registerRead(dest)] = src;
  return;
}

void operation(char operator[30], char operand[30], char dest[30]) {
  int first;
  if (registerRead(operand) < 4) {
    first = Registers[registerRead(operand)];
  }
  else {
    first = atoi(operand);
  }
  int reg = registerRead(dest);
  if (strcmp(operator, "add") == 0) {
    Registers[reg] += first;
  }
  else if (strcmp(operator, "sub") == 0) {
    Registers[reg] = Registers[reg] - first;
  }
  else if (strcmp(operator, "mul") == 0) {
    Registers[reg] = Registers[reg]*first;
  }
  else {
    Registers[reg] = first/Registers[reg];
  }
  return;
}

int jump(char instruction[30], char x[30], char y[30]) {
  int first;
  if (registerRead(x) < 4) {
    first = Registers[registerRead(x)];
  }
  else {
    first = atoi(x);
  }
  int second;
  if (registerRead(y) < 4) {
    second = Registers[registerRead(y)];
  }
  else {
    second = atoi(y);
  }
  if (strcmp(instruction, "je") == 0) {
    if (first == second) {
      return 1;
    }
  }
  if (strcmp(instruction, "jne") == 0) {
    if (first != second) {
      return 1;
    }
  }
  if (strcmp(instruction, "jg") == 0) {
    if (first > second) {
      return 1;
    }
  }
  if (strcmp(instruction, "jge") == 0) {
    if (first >= second) {
      return 1;
    }
  }
  if (strcmp(instruction, "jl") == 0) {
    if (first < second) {
      return 1;
    }
  }
  if (strcmp(instruction, "jle") == 0) {
    if (first <= second) {
      return 1;
    }
  }
  return 0;
}

void print(char reg[30]) {
  if (registerRead(reg) < 4) {
    printf("%d", Registers[registerRead(reg)]);
  }
  else {
    int num = atoi(reg);
    printf("%d", num);
  }
  return;
}

int main(int argc, char* argv[])
{
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("error");
    return 0;
  }
  int count = 0;
  char line[30];
  while (fgets(line, sizeof(line), fp)) {
    strcpy(Instructions[count], line);
    count++;
  }
  fclose(fp);
  int i = 0;
  while (i < count) {
    char instruction[30];
    sscanf(Instructions[i], "%s", instruction);
    if (instruction[0] == '\0') {
      i++;
      continue;
    }
    if (strcmp(instruction, "read") == 0) {
      char garbage[30];
      char reg[30];
      sscanf(Instructions[i], "%s %s", garbage, reg);
      read(reg);
      i++;
    }
    if (strcmp(instruction, "mov") == 0) {
      char garbage[30];
      char source[30];
      char dest[30];
      sscanf(Instructions[i], "%s %s %s", garbage, source, dest);
      mov(source, dest);
      i++;
      instruction[0] = '\0';
      continue;
    }
    if (instruction[0] == 'a' || instruction[0] == 's' || instruction[0] == 'm' || instruction[0] == 'd') {
      char op[30];
      char operand[30];
      char dest[30];
      sscanf(Instructions[i], "%s %s %s", op, operand, dest);
      operation(op, operand, dest);
      i++;   
    }
    if (strcmp(instruction, "jmp") == 0) {
      char garbage[30];
      int line;
      sscanf(Instructions[i], "%s %d", garbage, &line);
      i = line;
      instruction[0] = '\0';
      continue;
    }
    if (instruction[0] == 'j') {
      char jumpOp[30];
      int line;
      char first[30];
      char second[30];
      sscanf(Instructions[i], "%s %d %s %s", jumpOp, &line, first, second);
      if (jump(jumpOp, first, second) == 1) {
        i = line;
      }
      else {
        i++;
      } 
    }
    if (strcmp(instruction, "print") == 0) {
      char garbage[30];
      char toprint[30];
      sscanf(Instructions[i], "%s %s", garbage, toprint);
      print(toprint);
      i++;
    }
    instruction[0] = '\0';
  }
}