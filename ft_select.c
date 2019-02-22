#include "inc/ft_select.h"


t_output **head_func(t_output *ptr)
{
    static t_output **head_ref;

    if (ptr == NULL)
        return (head_ref);
    else
        head_ref = &ptr;
    return (head_ref);
}

void normal_mode()
{
    t_output **head_node;
    t_output *ptr;

    head_node = head_func(NULL);
    ptr = (*head_node);
    tputs(te_string, 1, my_putchar);
    tcsetattr(STDIN_FILENO, TCSANOW, &(ptr->ptr)->oldconfig);
    exit(0);
}

void	signal_handler(int sign)
{
	if (sign == SIGINT)
    {
        normal_mode();
        exit(0);
    }
}

void ft_signal()
{
    signal(SIGINT, signal_handler);
}

int my_putchar(int c)
{
	write (2, &c, 1);
	return (0);
}

void ft_termios()
{
    t_output **ptr;
    t_output *head_ref;

    ptr  = head_func(NULL);
    head_ref = (*ptr);
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

void get_input()
{
    int ch;

    while (1)
    {
        ch = 0;
        if (read(STDIN_FILENO, &ch, 4))
        {
           if(ch == keyup || ch == keydown || ch == keyright || ch == keyleft)
            {
                write(2, &ch, 4);
            }
            else if(ch == esc)
            {   
                     normal_mode();
                     exit(0) ;
            }
           /* else if(ch == delete)   
            else if(ch == backspace)
            else if(ch == space)
            {
            }*/
        }
           
    }
} 

void ft_select()
{
    tputs(ti_string, 1, my_putchar);
    print_list();
    get_input();
}

int main(int argc, char **argv)
{
    t_output **head;

    SIG_NUM = 0;
    if (argc == 1)
    {
        ft_putstr_fd("Usage : ", 2);
        ft_putendl_fd("./ft_select choice1 choice2 choice3 choice4", 2);
        return (0);
    }
    head = create_list(argv);
    printf("head->string ==> %s\n", (*head)->string);
    printf("head @ is ---> %p\n", head);
    //printf("%s\n", (*ptr)->string);
    t_output *ref;

    ref = (*head);
    t_output **ptr = head_func(ref);
    printf("head->string ==> %s\n", (*ptr)->string);
    /*ft_termios();
    ft_termcap();
    ft_select();*/
    return (0);
}
