/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:52:40 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/26 13:45:11 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

int		all_size(void)
{
	t_output	*ptr;
	int			i;

	i = 0;
	ptr = head_func(NULL);
	while (ptr)
	{
		i = ft_strlen(ptr->string) + i;
		ptr = ptr->next;
	}
	return (i);
}

int		is_enough(void)
{
	t_output	*ptrnode;
	int			l_string;
	int			resolution;
	int			size;

	resolution = 0;
	size = 0;
	ptrnode = head_func(NULL);
	l_string = long_string();
	resolution = ptrnode->max.ws_row * ptrnode->max.ws_col;
	size = all_size();
	if (ptrnode->tail->key < ptrnode->max.ws_row)
	{
		if (l_string + 2 >= ptrnode->max.ws_col)
			return (0);
		return (1);
	}
	else if (size < resolution)
		return (2);
	return (0);
}

int		element_key(void)
{
	int			key;
	int			j;
	t_output	*head_ref;

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

int		ft_coulmn(void)
{
	t_output	*head_ref;
	int			l_string;
	int			key;

	l_string = 0;
	head_ref = head_func(NULL);
	key = element_key();
	while (head_ref)
	{
		if (head_ref->key == key)
			break ;
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

int		windows_size(void)
{
	t_output	*head_ref;
	t_output	*temp;
	int			l_string;
	int			l_str_in_col;

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
		l_str_in_col = ft_coulmn();
		if (temp->tail->position->hpos + l_str_in_col >= temp->max.ws_col)
			return (0);
		return (1);
	}
	return (0);
}
