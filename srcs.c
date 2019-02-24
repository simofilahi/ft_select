#include "inc/ft_select.h"

void init_coor()
{
    struct s_coordone p;

    p.vpos = 0;
    p.hpos = 0;
}

void print_in_stdout()
{
    t_output *ptr;
    t_output *head_ref;
    int key;

    ptr = head_func(NULL);
    tputs(TE_STRING, 1, my_putchar);
    tputs(VE_STRING, 1, my_putchar);
    tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
	head_ref = head_func(NULL);
    key = last_selected_elem();
	while (head_ref)
	{
		if (head_ref->selected)
		{
			ft_putstr_fd(head_ref->string, 1);
            if (head_ref->key != key)
			    ft_putchar_fd(' ', 1);
		}
		head_ref = head_ref->next;	
	}
	exit(0);
}

int last_selected_elem()
{
    t_output *head_ref;

    head_ref = head_func(NULL);
    int key;
    key = 0;
    while (head_ref)
    {
        if (head_ref->selected)
            key = head_ref->key;
        head_ref = head_ref->next;
    }
    return (key);
}

void init_tail()
{
	t_output *head_ref;
	t_output *current;

	head_ref = head_func(NULL);
	current = head_func(NULL);
	while (head_ref->next)
		head_ref = head_ref->next;
	current->tail = head_ref;
}

int  reset_key()
{
	t_output *head_ref;

	head_ref =  head_func(NULL);
	int i = 0;
	while (head_ref)
	{
		head_ref->key = i++;
		head_ref = head_ref->next;
	}
	return (i);
}

void reset_cursor()
{
	t_output *head_ref;

	head_ref = head_func(NULL);
	head_ref->cursor = 1;
}

int my_putchar(int c)
{
	write (2, &c, 1);
	return (0);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
        normal_mode();
    if (sign == SIGWINCH)
    {
        tputs(CL_STRING, 1, my_putchar);
        print_list();
    }
    if (sign == SIGTSTP)
    {
        t_output *ptr;

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

void ft_signal()
{
    signal(SIGINT, signal_handler);
    signal(SIGWINCH, signal_handler);
    signal(SIGTSTP,signal_handler);
    signal(SIGCONT, signal_handler);
}