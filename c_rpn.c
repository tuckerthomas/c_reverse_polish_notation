#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rpnCalc(char*);

struct Stack {
	int data;
	struct Stack *next;
} typedef Stack;

Stack *newStack(int data) {
	Stack *stackNode = (Stack*) malloc(sizeof(Stack));
	if (stackNode == NULL) {
		exit(1);
	}
	stackNode->data = data;
	stackNode->next = NULL;
	return stackNode;
}

void push(Stack **root, int data) {
	Stack *newStackNode = newStack(data);
	newStackNode->next = *root;
	*root = newStackNode;
}

int pop(Stack **root) {
	if (*root == NULL) {
		printf("Root is empty\n");
		exit(1);
	}
	Stack* n = *root;
	*root = (*root)->next;
	int data = n->data;
	free(n);
	n = NULL;

	return data;
}

int main() {
	char input[1000];

	printf("Reverse Polish Notation Calculator\n");
	printf("Enter calculation: ");

	scanf("%[^\n]", input);

	printf("Input: '%s'\n", input);

	printf("Result: %d", rpnCalc(input));

	return 0;
}

int rpnCalc(char* s) {
	Stack *numbers = NULL;
	char *ptr = strtok(s, " ");

	while (ptr != NULL) {
		printf("Checking: %s\n", ptr);
		if ((int) ptr[0] >= 48 && (int) ptr[0] <= 57) {
			int num;

			sscanf(ptr, "%d", &num);

			push(&numbers, num);
			printf("Number pushed: %d\n", numbers->data);
		} else if (ptr[0] == '+') {
			if (numbers == NULL) {
				printf("Invalid Sequence\n");
				exit(1);
			}

			int num1 = pop(&numbers);
			int num2 = pop(&numbers);

			printf("Adding numbers %d and %d\n", num1, num2);
			push(&numbers, num1 + num2);
		} else if (ptr[0] == '-') {
			if (numbers == NULL) {
				printf("Invalid Sequence\n");
				exit(1);
			}

			int num1 = pop(&numbers);
			int num2 = pop(&numbers);

			printf("Subtracting numbers %d and %d\n", num1, num2);
			push(&numbers, num1 - num2);
		} else if (ptr[0] == '*' || ptr[0] == 'x') {
			if (numbers == NULL) {
				printf("Invalid Sequence\n");
				exit(1);
			}

			int num1 = pop(&numbers);
			int num2 = pop(&numbers);

			printf("Multiplying numbers %d and %d\n", num1, num2);
			push(&numbers, num1 * num2);
		} else if (ptr[0] == '/') {
			if (numbers == NULL) {
				printf("Invalid Sequence\n");
				exit(1);
			}

			int num1 = pop(&numbers);
			int num2 = pop(&numbers);

			printf("Dividing numbers %d and %d\n", num1, num2);
			push(&numbers, num1 / num2);
		}

		ptr = strtok(NULL, " ");
	}

	printf("Sequence ended, returning\n");
	// Sequence ended
	int answer = pop(&numbers);
	free(numbers);
	numbers = NULL;
	return answer;
}
