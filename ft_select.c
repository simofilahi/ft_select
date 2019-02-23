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
    tputs(te_string, 1, my_putchar);
    tputs(ve_string, 1, my_putchar);
    tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
    exit(0);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
        normal_mode();
    if (sign == SIGWINCH)
    {
        tputs(cl_string, 1, my_putchar);
        print_list();
    }
}

void ft_signal()
{
    signal(SIGINT, signal_handler);
    signal(SIGWINCH, signal_handler);
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
    head_ref->ptr = malloc(sizeof(struct follower));
    if (!isatty(STDIN_FILENO))
        ft_putendl_fd("error file descriptor not pointing to a tty", 2);
    if (tcgetattr(STDIN_FILENO, &(head_ref->ptr)->oldconfig))
        ft_putendl_fd("error can't get the current configuration", 2);
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
    success = tgetent(ap, termtype);
}

int finder_cursor()
{
    t_output *head_ref;

    head_ref = head_func(NULL);
    while (head_ref)
    {
        if (head_ref->cursor)
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

void get_input()
{
    int ch;
    int key;

    while (1)
    {
        ch = 0;
        if (read(STDIN_FILENO, &ch, 4))
        {
           if(ch == keyup)
           {
                key = finder_cursor();
                apply_new_postion_cursor(key, 1);
                tputs(cl_string, 1, my_putchar);
                print_list();
           }
           else if (ch == keydown)
           {
                key = finder_cursor();
                apply_new_postion_cursor(key, 0);
                tputs(cl_string, 1, my_putchar);
                print_list();
           }
           else if (ch == keyright)
           {

           }
           else if (ch == keyleft)
           {

           }
           else if(ch == esc)
            {   
                     normal_mode();
                     exit(0) ;
            }
            else if(ch == delete)
            {

            }
            else if(ch == backspace)
            {

            }
            else if(ch == space)
            {

            }
        }
           
    }
} 

void ft_select()
{
    tputs(ti_string, 1, my_putchar);
    print_list(0);
    get_input();
}

void init_coor()
{
    struct coordone *p;

    p = malloc(sizeof(struct coordone));
    p->vpos = 0;
    p->hpos = 0;
}

int main(int argc, char **argv)
{
    t_output *head;

    SIG_NUM = 0;
    if (argc == 1)
    {
        ft_putstr_fd("Usage : ", 2);
        ft_putendl_fd("./ft_select choice1 choice2 choice3 choice4", 2);
        return (0);
    }
    ft_signal();
    head = create_list(argv, argc);
    head_func(&head);
    ft_termios();
    ft_termcap();
    init_coor();
    ft_select();
    return (0);
}
