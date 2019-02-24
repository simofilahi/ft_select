#include "inc/ft_select.h"

t_output *add_node(char *string, int cursor, int key)
{
	t_output *new_node;
	if (!(new_node = malloc(sizeof(t_output))))
		return (NULL);
	if (!(new_node->string = ft_strdup(string)))
		return (NULL);
	new_node->cursor = cursor;
	new_node->key = key;
	new_node->selected = 0;
	new_node->position = malloc(sizeof(struct s_coordone));
	new_node->next = NULL;
	return(new_node);
}

t_output *create_list(char **argv, int argc)
{
	t_output *node;
	t_output *ptr;
	int j;

	node = NULL;
	ptr = NULL;
	j = 0;
	while ((*++argv))
	{
		if (node == NULL)
		{
			node = add_node(*argv, 1, j++);
			ptr = node;
		}
		else
		{
			node->next =  add_node(*argv, 0,j++);
			ptr->tail = node->next;
			node = node->next;
		}
	}
	ptr->llen = argc - 2;
	return(ptr);
}

int long_string()
{
	t_output *ptrnode;
	size_t len;

	ptrnode = head_func(NULL);
	len = 0;
	while (ptrnode)
	{
		if (ft_strlen(ptrnode->string) > len)
			len = ft_strlen(ptrnode->string);
		ptrnode = ptrnode->next;
	}
	return ((int)len);
}

void fill_pos()
{
	t_output *ptrnode;
	int i;

	ptrnode = head_func(NULL);
	i = 0;
	while (ptrnode)
	{
		ptrnode->position->vpos = i++;
		ptrnode->position->hpos = 0;
		ptrnode = ptrnode->next;
	}
}
