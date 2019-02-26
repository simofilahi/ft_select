/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:40:17 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/25 16:04:28 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	normal_mode_2(void)
{
	t_output	*ptr;

	ptr = head_func(NULL);
	tputs(TE_STRING, 1, my_putchar);
	tputs(VE_STRING, 1, my_putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
		normal_mode();
	else if (sign == SIGWINCH)
	{
		tputs(CL_STRING, 1, my_putchar);
		print_list();
	}
	else if (sign == SIGCONT)
	{
		ft_signal();
		ft_termios();
		ft_termcap();
		ft_select();
	}
	else if (sign == SIGTSTP)
	{
		normal_mode_2();
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\x1A");
	}
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGCONT, signal_handler);
	signal(SIGTSTP, signal_handler);
}

void	init_coor(void)
{
	struct s_coordone	p;
	
	(void)p;
	p.vpos = 0;
	p.hpos = 0;
}

void	init_tail(void)
{
	t_output	*head_ref;
	t_output	*current;

	head_ref = head_func(NULL);
	current = head_func(NULL);
	while (head_ref->next)
		head_ref = head_ref->next;
	current->tail = head_ref;
}
