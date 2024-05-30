#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int top;
  uint32_t capacity;
  uint32_t* data;
} Stack;

void init_stack(Stack* s){
  s->top = 0;
  s->capacity = 0;
  s->data = NULL;
}

void* reallocate(void* pointer, size_t capacity){
  if(capacity == 0){
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, capacity);

  if(result == NULL && capacity != 0){
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  return result;
}

void push_stack(Stack* s, int value){
  if(s->capacity < s->top + 1){
    int old_capacity = s->capacity;
    s->capacity = ((old_capacity) < 8 ? 8 : old_capacity * 2);
    s->data = (uint32_t*) reallocate(s->data, sizeof(uint32_t) * s->capacity);
  }
  s->data[s->top] = value;
  s->top++;
  printf("%d added to the stack\nStack pointer now %d\n", value, s->top);
}

static int is_empty(Stack* s){
  return s->top == 0; 
}

int pop_stack(Stack* s){
  if(is_empty(s)){
    return 0;
  }
  s->top--;
  int result = s->data[s->top];
  printf("%d popped from the stack\nStack pointer now %d\n", result, s->top);
  return result;
}

void free_memory(Stack* s){
  if(s->data != NULL){
    free(s->data);
    s->data = NULL;
  }
  init_stack(s);
}

int main(){

  Stack s;
  init_stack(&s);
  push_stack(&s, 10);
  push_stack(&s, 20);
  push_stack(&s, 30);
  int pop = pop_stack(&s);
  free_memory(&s);

}

