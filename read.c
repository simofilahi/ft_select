/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:02:10 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/24 22:20:43 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_select.h"

void	delete_node(void)
{
	t_output	*head_ref;
	t_output	*temp;

	head_ref = head_func(NULL);
	temp = head_func(NULL);
	if (head_ref->next == NULL && head_ref->key == 0)
	{
		free(head_ref);
		normal_mode();
	}
	if (head_ref && head_ref->cursor == 1)
	{
		head_func(&head_ref->next);
		temp = head_func(NULL);
		reset_cursor();
		temp->llen = reset_key();
		free(head_ref);
		init_tail();
		return ;
	}
	else
	{
		temp = head_ref;
		while (head_ref && head_ref->cursor != 1)
		{
			temp = head_ref;
			head_ref = head_ref->next;
		}
		temp->next = head_ref->next;
		if (temp->next == NULL)
			temp->cursor = 1;
		else
			temp->next->cursor = 1;
		temp->llen = reset_key();
		free(head_ref);
		init_tail();
		return ;
	}
}

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

void	apply_new_postion_cursor(int key, int flag)
{
	t_output *head_ref;
	
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
	while(head_ref)
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
				return(0);
			}	
		}
		head_ref = head_ref->next;
	}
	return (0);
}

void	get_input_3(int ch, int key)
{
	if (ch == SPACE)
	{
		if (!ft_selected())
		{
			key = finder_cursor();
			apply_new_postion_cursor(key, 0);
		}
		else
		{
			key = finder_cursor();
			apply_new_postion_cursor(key, 0);
		}
		print_list();
	}
	else if (ch == ENTER)
	{
		print_in_stdout();
	}
}

void	get_input_2(int ch, int key)
{
	if (ch == ESC)
	{   
		normal_mode();
		exit(0);
	}
	else if (ch == DELETE)
	{
		delete_node();
		tputs(CL_STRING, 1, my_putchar);
		print_list();
	}
	else if (ch == BACKSPACE)
	{
		delete_node();
		tputs(CL_STRING, 1, my_putchar);
		print_list();
	}
	else
		get_input_3(ch, key);

}

void	get_input(void)
{
	int ch;
	int key;

	while (1)
	{
		ch = 0;
		if (read(STDIN_FILENO, &ch, 4))
		{
			if (ch == KEYUP)
			{
				key = finder_cursor();
				apply_new_postion_cursor(key, 1);
				print_list();
			}
			else if (ch == KEYDOWN)
			{
				key = finder_cursor();
				apply_new_postion_cursor(key, 0);
				print_list();
			}
			else
				get_input_2(ch, key);
		}
	}
}