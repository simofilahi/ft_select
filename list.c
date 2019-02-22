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
    printf("ptr @ is ---> %p\n", ptr);
    printf("%s\n", (*ptr)->string);
    return(ptr);
}

int long_string(t_output **head_ref)
{
    t_output *ptrnode;
    size_t len;

    ptrnode = (*head_ref);
    len = 0;
    while (ptrnode)
    {
        if (ft_strlen(ptrnode->string) > len)
            len = ft_strlen(ptrnode->string);
        ptrnode = ptrnode->next;
    }
    return ((int)len);
}

void fill_pos(t_output **head)
{
    t_output *ptrnode;
    struct coordone fill;
    int i;

    ptrnode = (*head);
    fill.vpos = 0;
    fill.hpos = 0;
    i = 0;
    while (ptrnode)
    {
        ptrnode->position = malloc(sizeof(struct coordone));
        ptrnode->position->vpos = 0;
        ptrnode->position->hpos = i++;
        ptrnode = ptrnode->next;
    }
}

int windows_size()
{
    t_output **head_ref;
    t_output *ptrnode;
    struct winsize max;

    head_ref = head_func(NULL);
    ptrnode = (*head_ref);
    ioctl(0, TIOCGWINSZ , &max);
    if (max.ws_row < ptrnode->llen)
    {
    /*   fill_pos(head_ref);
       while (ptrnode)
       {
           ft_putnbr(ptrnode->position->hpos);
           ptrnode = ptrnode->next;
       }*/
       printf("here\n");
       return (1);
    }
    return (0);
}

void print_list()
{
    t_output **head_ref;
    t_output *ptr;

    head_ref = head_func(NULL);
    ptr = (*head_ref);
    if (windows_size())
    {   
        printf("%p\n", ptr);
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