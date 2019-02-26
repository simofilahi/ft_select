/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:47:21 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/26 13:47:32 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

int		finder_cursor(void)
{
	t_output *head_ref;

	head_ref = head_func(NULL);
	while (head_ref)
	{
		if (head_ref->cursor == 1)
		{
			head_ref->cursor = 0;
			return (head_ref->key);
		}
		head_ref = head_ref->next;
	}
	return (0);
}

void	apply_new_postion_cursor_2(int key, int flag, t_output *head_ref)
{
	while (head_ref)
	{
		if (head_ref->key - 1 == key)
		{
			head_ref->cursor = 1;
			return ;
		}
		if (head_ref->key + 1 == key && flag)
		{
			head_ref->cursor = 1;
			return ;
		}
		head_ref = head_ref->next;
	}
}

void	apply_new_postion_cursor(int key, int flag)
{
	t_output	*head_ref;

	head_ref = head_func(NULL);
	if (key == 0 && flag)
	{
		head_ref->tail->cursor = 1;
		return ;
	}
	if (head_ref->tail->key == key && !flag)
	{
		head_ref->cursor = 1;
		return ;
	}
	apply_new_postion_cursor_2(key, flag, head_ref);
}

int		ft_selected(void)
{
	t_output *head_ref;

	head_ref = head_func(NULL);
	while (head_ref)
	{
		if (head_ref->cursor == 1)
		{
			if (head_ref->cursor == head_ref->selected)
			{
				head_ref->selected = 0;
				return (1);
			}
			else
			{
				head_ref->selected = 1;
				return (0);
			}
		}
		head_ref = head_ref->next;
	}
	return (0);
}
