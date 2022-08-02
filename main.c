#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct	s_stack
{
	int				data;
	struct s_stack	*next;
}	t_stack;

// create linked list
t_stack	*init_stack(void)
{
	t_stack	*dest;

	// calloc is malloc but in memory is not contain any data
	dest = (t_stack*) calloc (sizeof(t_stack), 1);
	if (!dest)
		return (NULL);
	dest->next = NULL;
	return (dest);
}

// add linked list to first of stack
bool	push(int num, t_stack **stack)
{
	t_stack	*dest;

	dest = init_stack();
	if (!dest)
		return (0);
	dest->data = num;
	if (!*stack)
		dest->next = NULL;
	else
		dest->next = *stack;
	*stack = dest;
	return (1);
}

// pop first linked list of stack
bool	pop(int *top, t_stack **stack)
{
	t_stack	*temp;

	temp = NULL;
	if (*stack)
	{
		if ((*stack)->next)
			temp = (*stack)->next;
		*top = (*stack)->data;
		free (*stack);
		if (temp)
			*stack = temp;
		else
			*stack = NULL;
		return (1);
	}
	else
		return (0);
}

// check argument is an operator
bool is_operator(char *c)
{
	return (*c == '+' || *c == '-' || *c == 'x' || *c == '/');
}

// calculate n1 and n2 with operator
int	calculate(char *c, int n1, int n2)
{
	switch (*c)
	{
		case '+': return (n1 + n2); break;
		case '-': return (n1 - n2); break;
		case 'x': return (n1 * n2); break;
		case '/': return (n1 / n2); break;
	}
	return (1);
}

// argc is argument count
// argv is array of argument
int	main(int argc, char **argv)
{
	int		i, n1, n2, value;
	t_stack	*stack;

	i = 1;
	value = 0;
	stack = NULL;
	// if argc == 1 it's mean no argument entered
	if (argc == 1)
		printf("Please Enter a argument!!!\nExample:\n./a.out 3 4 5 x +\n");
	else
	{
		while (i < argc)
		{
			if (!is_operator(argv[i]))
				push(atoi(argv[i]), &stack);
			else
			{
				if (pop(&n2, &stack) && pop(&n1, &stack))
				{
					value = calculate(argv[i], n1, n2);
					push(value, &stack);
				}
			}
			i++;
		}
		pop(&value, &stack);
		printf("%d\n", value);
	}
	return (0);
}
