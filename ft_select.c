#include "inc/ft_select.h"
#include <stdio.h>


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

int main(int argc, char **argv)
{
    t_output **head;

    (void)argc;
    head = create_list(argv);
    print_list(head);
    return (0);
}