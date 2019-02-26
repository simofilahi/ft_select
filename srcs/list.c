/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:35:22 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/26 12:42:15 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

t_output	*add_node(char *string, int cursor, int key)
{
	t_output	*new_node;

	if (!(new_node = malloc(sizeof(t_output))))
		return (NULL);
	new_node->string = string;
	new_node->cursor = cursor;
	new_node->key = key;
	new_node->selected = 0;
	new_node->x = 0;
	new_node->position = malloc(sizeof(struct s_coordone));
	new_node->next = NULL;
	return (new_node);
}

t_output	*create_list(char **argv, int argc)
{
	t_output	*node;
	t_output	*ptr;
	int			j;

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
			node->next = add_node(*argv, 0, j++);
			ptr->tail = node->next;
			node = node->next;
		}
	}
	ptr->llen = argc - 2;
	ptr->ptr = malloc(sizeof(struct s_follower));
	return (ptr);
}

t_output	*head_func(t_output **ptr)
{
	static t_output	*head_ref;

	if (ptr == NULL)
		return (head_ref);
	else
		head_ref = (*ptr);
	return (head_ref);
}

int			long_string(void)
{
	t_output	*ptrnode;
	size_t		len;

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

void		fill_pos(void)
{
	t_output	*ptrnode;
	int			i;

	ptrnode = head_func(NULL);
	i = 0;
	while (ptrnode)
	{
		ptrnode->position->vpos = i++;
		ptrnode->position->hpos = 0;
		ptrnode = ptrnode->next;
	}
}
