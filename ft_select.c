#include "inc/ft_select.h"

int my_putchar(int c)
{
	write (2, &c, 1);
	return (0);
}

void ft_termios(t_output **head_ref)
{
    t_output *ptrnode;

    ptrnode = (*head_ref);
    if (!isatty(STDIN_FILENO))
        ft_putendl_fd("error file descriptor not pointing to a tty", 2);
    if (tcgetattr(STDIN_FILENO, &ptrnode->oldconfig))
        ft_putendl_fd("error can't get the current configuration", 2);
    ptrnode->newconfig = ptrnode->oldconfig;
    ptrnode->newconfig.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &ptrnode->newconfig) < 0)
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

void ft_select(t_output **head)
{
    t_output *head_ref;
    int ch;

    head_ref = (*head);
    tputs(ti_string, 1, my_putchar);
    print_list(&head_ref);
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
                     tcsetattr(STDIN_FILENO, TCSANOW, &head_ref->oldconfig);
                     tputs(te_string, 1, my_putchar);
                     break ;
            }
           /* else if(ch == delete)   
            else if(ch == backspace)
            else if(ch == space)
            {
            }*/
        }
    }   
}

int main(int argc, char **argv)
{
    t_output **head;
    t_output *tail;

    (void)argc;
    (void)argv;
    tail = NULL;
    head = create_list(argv);
    ft_termios(head);
    ft_termcap();
    ft_select(head);
    return (0);
}
