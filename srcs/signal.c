/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 23:18:09 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/24 23:50:51 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	signal_handler(int sign)
{
	t_output	*ptr;

	if (sign == SIGINT)
		normal_mode();
	if (sign == SIGWINCH)
	{
		tputs(CL_STRING, 1, my_putchar);
		print_list();
	}
	if (sign == SIGTSTP)
	{
		ptr = head_func(NULL);
		tputs(TE_STRING, 1, my_putchar);
		tputs(VE_STRING, 1, my_putchar);
		tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\x1A");
	}
	else if (sign == SIGCONT)
	{
		ft_termios();
		ft_termcap();
		ft_select();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGWINCH, signal_handler);
	signal(SIGTSTP, signal_handler);
	signal(SIGCONT, signal_handler);
}

void	init_coor(void)
{
	struct s_coordone	p;

	p.vpos = 0;
	p.hpos = 0;
}

int		my_putchar(int c)
{
	write(2, &c, 1);
	return (0);
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
