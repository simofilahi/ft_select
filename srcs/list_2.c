/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:46:51 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/26 13:47:09 by mfilahi          ###   ########.fr       */
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
		ptrnode->x = j;
		ptrnode = ptrnode->next;
		if (i == var->max.ws_row - 1)
		{
			i = 0;
			j++;
		}
	}
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
