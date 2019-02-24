#include "inc/ft_select.h"

t_output *head_func(t_output **ptr)
{
    static t_output *head_ref;

    if (ptr == NULL)
        return (head_ref);
    else
        head_ref = (*ptr);
    return (head_ref);
}

void normal_mode()
{
    t_output *ptr;

    ptr = head_func(NULL);
    tputs(TE_STRING, 1, my_putchar);
    tputs(VE_STRING, 1, my_putchar);
    tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
    exit(0);
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

int my_putchar(int c)
{
	write (2, &c, 1);
	return (0);
}

void ft_termios()
{
    t_output *head_ref;

    head_ref = head_func(NULL);
    head_ref->ptr = malloc(sizeof(struct s_follower));
    if (!isatty(STDIN_FILENO))
        ft_putendl_fd("error file descriptor not pointing to a tty", 2);
    if (tcgetattr(STDIN_FILENO, &(head_ref->ptr)->oldconfig))
        ft_putendl_fd("error can't get the current configuration", STDIN_FILENO);
    head_ref->ptr->newconfig = head_ref->ptr->oldconfig;
    head_ref->ptr->newconfig.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &(head_ref->ptr)->newconfig) < 0)
        ft_putendl_fd("error can't apply the configuration", 2);
}

void ft_termcap()
{
    char *termtype;
    int success;
    char buf2[30];
	char *ap = buf2;

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

/*void	delete_node()
{
	t_output *head_ref;
	t_output *temp;

	head_ref = head_func(NULL);
	temp = head_func(NULL);
	if (head_ref->next == NULL && head_ref->key == 0)
	{
	//	free(head_ref->string);
		free(head_ref);	
		normal_mode();	
	}
	if (head_ref && head_ref->cursor == 1)
	{
		head_func(&head_ref->next);
		temp = head_func(NULL);
		reset_cursor();
		temp->llen = reset_key();
	//	free(head_ref->string);
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
		free(head_ref->string);
		free(head_ref);
		init_tail();
		return ;
	}
}

int finder_cursor()
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


void apply_new_postion_cursor(int key, int flag)
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


int ft_selected()
{
	t_output *head_ref;

	head_ref = head_func(NULL);
	while(head_ref)
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
}*/

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

/*void get_input()
{
    int ch;
    int key;

    while (1)
    {
        ch = 0;
        if (read(STDIN_FILENO, &ch, 4))
        {
           if(ch == KEYUP)
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
           else if(ch == ESC)
            {   
                     normal_mode();
                     exit(0) ;
            }
            else if(ch == DELETE)
            {
		        delete_node();
                tputs(CL_STRING, 1, my_putchar);
		        print_list();
            }
            else if(ch == BACKSPACE)
            {
		        delete_node();
                tputs(CL_STRING, 1, my_putchar);
		        print_list();
            }
            else if(ch == SPACE)
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
           
    }
}*/

void ft_select()
{
    tputs(TI_STRING, 1, my_putchar);
    print_list(0);
    get_input();
}

void init_coor()
{
    struct s_coordone p;

    p.vpos = 0;
    p.hpos = 0;
}

int main(int argc, char **argv)
{
    t_output *head;

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
