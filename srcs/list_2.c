/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:52:21 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/26 12:46:23 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"


//comment
#include <stdio.h>

void	fill_pos_2(int y)
{
	t_output	*ptrnode;
	t_output	*var;
	int			i;
	int			j;

	ptrnode = head_func(NULL);
	var = ptrnode;
	i = 0;
	j = 0;
	while (ptrnode)
	{
		ptrnode->position->vpos = i++;
		ptrnode->position->hpos = y * j;
		ptrnode->x = j;
		ptrnode = ptrnode->next;
		if (i == var->max.ws_row - 1)
		{
			i = 0;
			j++;
		}
	}
}

int all_size()
{
	t_output *ptr;
	int	    i;
	
	i = 0;
	ptr = head_func(NULL);
	while (ptr)
	{
		i = ft_strlen(ptr->string) + i;
		ptr = ptr->next;
	}
	return (i);
}

int is_enough()
{
	t_output *ptrnode;
	int	l_string;
	int		resolution;
	
	resolution = 0;
	ptrnode = head_func(NULL);
	l_string = long_string();
	resolution = ptrnode->max.ws_row * ptrnode->max.ws_col;
	int size = all_size();
	if (ptrnode->tail->key < ptrnode->max.ws_row)
	{
		if (l_string + 2 >= ptrnode->max.ws_col)
			return (0);
		return (1);
	}
	else if (size < resolution)
	{
		return (2);
	}
	return (0);
}

int element_key()
{
	int key;
	int j;
	t_output *head_ref;

	head_ref = head_func(NULL);
	key = 0;
	j = 0;
	j = head_ref->x;
	key = head_ref->key;
	while (head_ref)
	{
		if (j != head_ref->x)
		{
			j = head_ref->x;
			key = head_ref->key;
		}	
		head_ref = head_ref->next;
	}
	return (key);
}

int ft_coulmn()
{
	t_output *head_ref;
	int		l_string;
	
	l_string = 0;
	head_ref = head_func(NULL);
	int key = element_key();
	while (head_ref)
	{
		if (head_ref->key == key)
			break;
		head_ref = head_ref->next;
	}
	while (head_ref)
	{
		if (l_string < (int)ft_strlen(head_ref->string))
			l_string = ft_strlen(head_ref->string);
		head_ref = head_ref->next;
	}
	return (l_string);
}

int windows_size()
{

	t_output *head_ref;
	t_output *temp;
	int	l_string;

	head_ref = head_func(NULL);
	ioctl(0, TIOCGWINSZ, &head_ref->max);
	head_func(&head_ref);
	l_string = long_string();
	temp = head_func(NULL);
	if (is_enough() == 1)
	{
		fill_pos();
		return (1);
	}
	else if (is_enough() == 2)
	{
		fill_pos_2(l_string + 6);
		int l_str_in_col = ft_coulmn();
		if (temp->tail->position->hpos + l_str_in_col >= temp->max.ws_col)
			return (0);
		return (1);
	}
	return (0);                                                                                               
}

void	print_list2(t_output *head_ref)
{
	if (!head_ref->selected && head_ref->cursor)
	{
		tputs(US_STRING, 1, my_putchar);
		tputs(tgoto(GOTOSTR, head_ref->position->hpos,
					head_ref->position->vpos), 1, my_putchar);
		ft_putendl_fd(head_ref->string, 2);
		tputs(UE_STRING, 1, my_putchar);
	}
	else if (head_ref->selected)
	{
		tputs(MR_STRING, 1, my_putchar);
		tputs(US_STRING, 1, my_putchar);
		tputs(tgoto(GOTOSTR, head_ref->position->hpos,
					head_ref->position->vpos), 1, my_putchar);
		ft_putendl_fd(head_ref->string, 2);
		tputs(ME_STRING, 1, my_putchar);
		tputs(UE_STRING, 1, my_putchar);
	}
	else
	{
		tputs(tgoto(GOTOSTR, head_ref->position->hpos,
					head_ref->position->vpos), 1, my_putchar);
		ft_putendl_fd(head_ref->string, 2);
	}
}

void	print_list(void)
{
	t_output *ptr;

	ptr = head_func(NULL);
	if (windows_size())
	{
		tputs(VI_STRING, 1, my_putchar);
		while (ptr)
		{
			if (!ptr->cursor && ptr->selected)
			{
				tputs(MR_STRING, 1, my_putchar);
				tputs(tgoto(GOTOSTR, ptr->position->hpos, ptr->position->vpos),
						1, my_putchar);
				ft_putendl_fd(ptr->string, 2);
				tputs(ME_STRING, 1, my_putchar);
			}
			else
				print_list2(ptr);
			ptr = ptr->next;
		}
	}
	else
		ft_putendl_fd("windows so small !!!", 2);
}
