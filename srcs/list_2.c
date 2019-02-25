/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:52:21 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/25 16:14:12 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

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

int		ft_calcule(void)
{
	t_output	*ptrnode;
	float		x;
	int			y;
	int			l_string;

	ptrnode = head_func(NULL);
	x = ptrnode->tail->key / ptrnode->max.ws_row;
	l_string = long_string();
	y = ((x + 2) * l_string) + (6 * (x + 1));
	if (y < ptrnode->max.ws_col)
	{
		if ((ptrnode->tail->position->hpos + l_string) >= ptrnode->max.ws_col)
			return (0);
		fill_pos_2(l_string + 6);
		return (1);
	}
	else
		return (0);
}

int		windows_size(void)
{
	t_output	*ptrnode;
	int			l_string;

	ptrnode = head_func(NULL);
	l_string = long_string();
	ioctl(0, TIOCGWINSZ, &ptrnode->max);
	head_func(&ptrnode);
	if (ptrnode->tail->key < ptrnode->max.ws_row)
	{
		if ((l_string + 6) >= ptrnode->max.ws_col)
			return (0);
		fill_pos();
		return (1);
	}
	else
	{
		if (ft_calcule())
			return (1);
	}
	return (0);
}

void	print_list2(t_output *head_ref)
{
	if (head_ref->cursor && !(head_ref->selected))
	{
		tputs(US_STRING, 1, my_putchar);
		tputs(tgoto(GOTOSTR, head_ref->position->hpos,
					head_ref->position->vpos), 1, my_putchar);
		ft_putendl_fd(head_ref->string, 2);
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
			if (ptr->selected)
			{
				tputs(US_STRING, 1, my_putchar);
				tputs(MR_STRING, 1, my_putchar);
				tputs(tgoto(GOTOSTR, ptr->position->hpos, ptr->position->vpos),
						1, my_putchar);
				ft_putendl_fd(ptr->string, 2);
				tputs(ME_STRING, 1, my_putchar);
				tputs(UE_STRING, 1, my_putchar);
			}
			else
				print_list2(ptr);
			ptr = ptr->next;
		}
	}
	else
		ft_putendl_fd("windows so small !!!", 2);
}
