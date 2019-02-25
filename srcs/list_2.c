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

int ft_calcule()
{
	t_output *ptrnode;
	float x;
	int		j;
	int l_string;

	ptrnode = head_func(NULL);
	x = 0;
	x = ptrnode->llen / ptrnode->max.ws_row;
/*	fprintf(stderr, "max.ws_row %d\n", ptrnode->max.ws_row);
	fprintf(stderr, "max.ws_col %d\n", ptrnode->max.ws_col);
	fprintf(stderr, "x ==> %f\n", x);
	ft_putchar('\n');*/
	l_string = long_string();
	// fprintf(stderr, "l_string ==> %d\n", l_string);
	 j = 1;
	 if (x == (int)x)
		j = 0;
     int y = (x + j) * (l_string + (6 * (x - 1)));
  //  fprintf(stderr, "y ==> %d\n", y);
	if (y < ptrnode->max.ws_col)
	{
		fill_pos_2(l_string + 6);
		return (1);
	}
	else
		return (0);
}

int windows_size()
{
	t_output *ptrnode;
	int			l_string;

	ptrnode = head_func(NULL);
	ioctl(0, TIOCGWINSZ , &ptrnode->max);
	head_func(&ptrnode);
	l_string = long_string();
//	fprintf(stderr, "ptrnode->tail->key %d\n", ptrnode->tail->key);
//	fprintf(stderr, "ptrnode->tail->position->hpos %d\n", ptrnode->tail->position->hpos);
//	fprintf(stderr, "long string is  %d\n", l_string);
	if (ptrnode->tail->key < ptrnode->max.ws_row)
	{
	//	fprintf(stderr, "HERE first if statement\n");
		fill_pos();
		return (1);
	}
	else if (ptrnode->tail->key > ptrnode->max.ws_col)
	{
	//	fprintf(stderr, "HERE second if statement\n");
	//	fprintf(stderr, "ptrnode->tail->position->hpos + l_string is %d\n", ptrnode->tail->position->hpos + l_string);
		if (ft_calcule())
			return (1);
	}
	else if ( (l_string + ptrnode->tail->position->hpos) >= ptrnode->max.ws_col)
		return (0);
	return (0);                                                                                                                           }

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
