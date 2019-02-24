/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 21:23:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/24 23:49:20 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

t_output	*head_func(t_output **ptr)
{
	static t_output	*head_ref;

	if (ptr == NULL)
		return (head_ref);
	else
		head_ref = (*ptr);
	return (head_ref);
}

void		normal_mode(void)
{
	t_output	*ptr;

	ptr = head_func(NULL);
	tputs(TE_STRING, 1, my_putchar);
	tputs(VE_STRING, 1, my_putchar);
	tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
	exit(0);
}

void		ft_termios(void)
{
	t_output	*head_ref;

	head_ref = head_func(NULL);
	head_ref->ptr = malloc(sizeof(struct s_follower));
	if (!isatty(STDIN_FILENO))
		ft_putendl_fd("error file descriptor not pointing to a tty", 2);
	if (tcgetattr(STDIN_FILENO, &(head_ref->ptr)->oldconfig))
		ft_putendl_fd("error can't get the current configuration", \
				STDIN_FILENO);
	head_ref->ptr->newconfig = head_ref->ptr->oldconfig;
	head_ref->ptr->newconfig.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(head_ref->ptr)->newconfig) < 0)
		ft_putendl_fd("error can't apply the configuration", 2);
}

void		ft_termcap(void)
{
	char	*termtype;
	int		success;
	char	buf2[30];
	char	*ap;

	ap = buf2;
	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		ft_putendl_fd("variable TERM not found", 2);
		normal_mode();
	}
	success = tgetent(ap, termtype);
	if (success == -1)
	{
		ft_putendl_fd("set a valid TERM value *_-)", 2);
		normal_mode();
	}
}

void		ft_select(void)
{
	tputs(TI_STRING, 1, my_putchar);
	print_list(0);
	get_input();
}

int			main(int argc, char **argv)
{
	t_output	*head;

	if (argc == 1)
	{
		ft_putstr_fd("Usage : ", 2);
		ft_putendl_fd("./ft_select choice1 choice2 choice3 choice4", 2);
		return (0);
	}
	ft_signal();
	init_coor();
	head = create_list(argv, argc);
	head_func(&head);
	ft_termios();
	ft_termcap();
	ft_select();
	return (0);
}
