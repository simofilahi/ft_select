#include "inc/ft_select.h"

void create_node(t_output **head_ref, char *string, int i)
{
    t_output *new_node;

    if (!(new_node = malloc(sizeof(t_output))))
        return ;
    if (!(new_node->string = ft_strnew(ft_strlen(string))))
        return ;
    ft_strcpy(new_node->string, string);
    new_node->llen = i;
    new_node->next = (*head_ref);
   /* new_node->prev = NULL;
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;*/
    (*head_ref) = new_node;
}

t_output **create_list(char **argv)
{
    t_output *node;
    t_output **ptr;
    int i;

    node = NULL;
    ptr = NULL;
    i = 0;
    while ((*++argv))
    {
        create_node (&node, (*argv), i++);
        if (ptr == NULL)
             ptr = &node;
    }
   /* t_output *new_node;

    new_node = (*ptr);
    i = 0;
    while (new_node)
    {
        new_node->llen = i++;
        new_node = new_node->next;
    }*/
    return(ptr);
}

void print_list(t_output **head_ref)
{
    t_output *ptr;

    ptr = (*head_ref);
    ioctl(0, TIOCGWINSZ , &ptr->max);
    if (ptr->max.ws_row > ptr->llen)
    {   
        tputs(us_string, 1, my_putchar);
        ft_putendl_fd(ptr->string, 2);
        tputs(ue_string, 1, my_putchar);
        ptr = ptr->next;
        while (ptr)
        {
            ft_putendl_fd(ptr->string, 2);
            ptr = ptr->next;
        }
        tputs(tgoto(gotostr, 0, 0), 1, my_putchar);
    }
    else 
        ft_putendl_fd("windows so small", 2);
}