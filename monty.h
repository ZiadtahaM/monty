#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct stack_s
{
    int n;
    struct stack_s *prev;
    struct stack_s *next;
} stack_t;

extern void push(stack_t **stack, unsigned int line_number, int value);
extern void pall(stack_t *stack, unsigned int line_number);

#endif /* MONTY_H */

