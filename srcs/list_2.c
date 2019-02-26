/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:52:21 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/25 20:15:34 by mfilahi          ###   ########.fr       */
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
		i = long_string() + 12 + i;
		ptr = ptr->next;
	}
	return (i);
}

int is_enough()
{
	t_output *ptrnode;
//	int	l_string;
//	float		x;
	//int 		j;
	//int 		y;
	int		resolution;
	
//	x = 0;
//	y = 0;
	//j = 0;
	resolution = 0;
	ptrnode = head_func(NULL);
//	l_string = long_string();
//	fprintf(stderr, "ptrnode->tail->key %d\n", ptrnode->tail->key);
//	fprintf(stderr, "ptrnode->max.ws_row %d\n", ptrnode->max.ws_row);
//	fprintf(stderr, "ptrnode->max.ws_col %d\n", ptrnode->max.ws_col);
//	x = ptrnode->tail->key / ptrnode->max.ws_row;
//	if (x != (int)x)
//		j = 1;
//	fprintf(stderr, "result of x =====>  %f\n", x);
	resolution = ptrnode->max.ws_row * ptrnode->max.ws_col;
//	fprintf(stderr, "value of resolution  =====>  %d\n", resolution);
//	fprintf(stderr, "value of l_string  =====>  %d\n", l_string);
	//fprintf(stderr, "value of y  =====>  %d\n", j);
//	int b = 6 * ptrnode->max.ws_row * (x + 1);
//	y = (x + 1) * l_string  * ptrnode->max.ws_row + b;
	int size = all_size();
//	fprintf(stderr, "value of size  =====>  %d\n", size);
	if (ptrnode->tail->key > ptrnode->max.ws_row && size < resolution)
	{
		return (2);
	}
	else if (ptrnode->tail->key < ptrnode->max.ws_row)
		return (1);
	return (0);
}

int windows_size()
{

	t_output *head_ref;
	int	l_string;

	head_ref = head_func(NULL);
	ioctl(0, TIOCGWINSZ, &head_ref->max);
	head_func(&head_ref);
	l_string = long_string();
	if (is_enough() == 1)
	{
//		fprintf(stderr, "here first\n");
		fill_pos();
		return (1);
	}
	else if (is_enough() == 2)
	{
//		fprintf(stderr, "here second\n");
	/*	if (temp->tail->position->hpos + l_string >= temp->max.ws_col)
			return (0);*/
		fill_pos_2(l_string + 6);
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
