#include "inc/ft_select.h"

void create_node(t_output **head_ref, char *string)
{
    t_output *new_node;

    if (!(new_node = malloc(sizeof(t_output))))
        return ;
    if (!(new_node->string = ft_strnew(ft_strlen(string) + 1)))
        return ;
    ft_strcpy(new_node->string, string);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

t_output **create_list(char **argv)
{
    t_output *node;
    t_output **ptr;

    node = NULL;
    ptr = NULL;
    while ((*++argv))
    {
        create_node (&node, (*argv));
        if (ptr == NULL)
             ptr = &node;
    }
    return(ptr);
}

void print_list(t_output **head_ref)
{
    t_output *ptr;

    ptr = (*head_ref);
    while (ptr->next)
    {
        ft_putendl(ptr->string);
        ptr = ptr->next;
     }
}

int my_ft_putchar(int c)
{
	write (2, &c, 1);
	return (0);
}

void ft_select(t_output **head)
{
    t_output *head_ref;
    struct termios newconfig;
    struct termios oldconfig;
    int ch;
    char *termtype;
    int success;
    char *ti_string, *te_string, *vi_string, *ve_string, *gotostr;
   // char buf2[30];
	//char *ap = buf2;

    head_ref = (*head);
    if (!isatty(STDIN_FILENO))
        ft_putendl("error file descriptor not pointing to a tty");
    if (tcgetattr(STDIN_FILENO, &oldconfig))
        ft_putendl("error can't get the current configuration");
    newconfig = oldconfig;
    newconfig.c_lflag &= ~(ECHO | ICANON);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newconfig) < 0)
        ft_putendl("error can't apply the configuration");
    termtype = getenv("TERM");
    success = tgetent(0, termtype);
   /* if (success > 0)
        ft_putendl("success");*/
    ti_string = tgetstr("ti", NULL);
    te_string = tgetstr("te", NULL);
    vi_string = tgetstr("vi", NULL);
    ve_string = tgetstr("ve", NULL);
    gotostr = tgetstr("cm", NULL);
    tputs(ti_string, 1, my_ft_putchar);
    //fputs(vi_string, stdout);
	while (1)
    {
        //fputs(ti_string, stdout);
        ch = 0;
        if (read(STDIN_FILENO, &ch, 4))
        {
           if(ch == keyup || ch == keydown || ch == keyright || ch == keyleft)
            {
              write(1, &ch, 4);
            }
            else if(ch == esc)
            {
                //ft_putendl("value of esc is working");
               	 fputs(te_string, stdout); 
                    break ;
            }
            else if(ch == delete)
               write(1, &ch, 4);
            else if(ch == backspace)
                write(1, &ch, 4);
            else if(ch == space)
                write(1, &ch, 4);
         }
    } 
    // fputs(te_string, stdout);
    // fputs(ve_string, stdout);    
    }

int main(int argc, char **argv)
{
   t_output **head;

    (void)argc;
    (void)argv;
    head = create_list(argv);
  // print_list(head);
    ft_select(head);
    return (0);
}
