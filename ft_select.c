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
        create_node(&node, (*argv));
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

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void ft_select()
{
    struct termios config;
    int ch;
 
   if (!isatty(STDIN_FILENO))
        ft_putendl("error file descriptor not pointing to a tty");
    if (tcgetattr(STDIN_FILENO, &config))
        ft_putendl("error can't get the current configuration");
    config.c_lflag &= ~(ECHO | ICANON);
    config.c_cc[VMIN]  = 1;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &config) < 0)
        ft_putendl("error can't apply the configuration");
    while (1)
    {
        ch = 0;
        if (read(STDIN_FILENO, &ch, 4))
        {
            if(ch == keyup)
                ft_putendl("value of keyup is working");
            else if(ch == keydown)
                ft_putendl("value of keydown is working");
            else if(ch == keyright)
                ft_putendl("value of keyright is working");
            else if(ch == keyleft)
                ft_putendl("value of keyleft is working");
            else if(ch == esc)
            {
                ft_putendl("value of esc is working");
                break ;
            }
            else if(ch == delete)
                ft_putendl("value of delete is working");
            else if(ch == backspace)
                ft_putendl("value of backspace is working");
            else if(ch == space)
                ft_putendl("value of space is working");
            }
        }
        
    }

int main(int argc, char **argv)
{
   t_output **head;

    (void)argc;
    (void)argv;
    head = create_list(argv);
    print_list(head);
    ft_select();
    return (0);
}