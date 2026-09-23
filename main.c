#include "monty.h"

int global_value;

void push(stack_t **stack, unsigned int line_number) {
    stack_t *new_node = malloc(sizeof(stack_t));
    if (!new_node) {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = global_value;
    new_node->prev = NULL;
    new_node->next = *stack;
    if (*stack) (*stack)->prev = new_node;
    *stack = new_node;
}

void pall(stack_t **stack, unsigned int line_number) {
    stack_t *temp = *stack;
    (void)line_number;
    while (temp) {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}

void free_stack(stack_t *stack) {
    stack_t *temp;
    while (stack) {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    stack_t *stack = NULL;
    char line[256];
    unsigned int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char *opcode = strtok(line, " \t\n");
        if (!opcode || opcode[0] == '#') continue;

        if (strcmp(opcode, "push") == 0) {
            char *arg = strtok(NULL, " \t\n");
            if (!arg) {
                fprintf(stderr, "L%d: usage: push integer\n", line_number);
                free_stack(stack);
                fclose(file);
                return EXIT_FAILURE;
            }
            global_value = atoi(arg);
            push(&stack, line_number);
        } else if (strcmp(opcode, "pall") == 0) {
            pall(&stack, line_number);
        } else {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
            free_stack(stack);
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    free_stack(stack);
    fclose(file);
    return EXIT_SUCCESS;
}

