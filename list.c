#include "inc/ft_select.h"

t_output *add_node(char *string, int cursor, int key)
{
    t_output *new_node;
    if (!(new_node = malloc(sizeof(t_output))))
        return (NULL);
    if (!(new_node->string = ft_strdup(string)))
        return (NULL);
    new_node->cursor = cursor;
    new_node->key = key;
    new_node->next = NULL;
    return(new_node);
}

t_output *create_list(char **argv, int argc)
{
    t_output *node;
    t_output *ptr;
    int i;
    int j;

    node = NULL;
    ptr = NULL;
    i = 0;
    j = 0;
    while ((*++argv))
    {
      if (node == NULL)
      {
        node = add_node(*argv, 1, j++);
        ptr = node;
      }
      else
      {
            node->next =  add_node(*argv, 0,j++);
            ptr->tail = node->next;
            node = node->next;
      }
    }
    ptr->llen = argc - 2;
    return(ptr);
}

int long_string()
{
    t_output *ptrnode;
    size_t len;

    ptrnode = head_func(NULL);
    len = 0;
    while (ptrnode)
    {
        if (ft_strlen(ptrnode->string) > len)
            len = ft_strlen(ptrnode->string);
        ptrnode = ptrnode->next;
    }
    return ((int)len);
}

void fill_pos()
{
    t_output *ptrnode;
    int i;

    ptrnode = head_func(NULL);
    i = 0;
    while (ptrnode)
    {
        ptrnode->position = malloc(sizeof(struct coordone));
        ptrnode->position->vpos = i++;
        ptrnode->position->hpos = 0;
        ptrnode = ptrnode->next;
    }
}


void fill_pos_2(int y)
{
    t_output *ptrnode;
    t_output *var;
    int i;

    ptrnode = head_func(NULL);
    var = ptrnode;
    i = 0;
    int j = 0;
    while (ptrnode)
    {
        ptrnode->position = malloc(sizeof(struct coordone));
        ptrnode->position->vpos = i++;
        ptrnode->position->hpos = y * j;
       // fprintf(stderr, "ptrnode->position->vpos %d \n", ptrnode->position->vpos);
       // fprintf(stderr, "ptrnode->position->hpos %d \n", ptrnode->position->hpos);
        ptrnode = ptrnode->next;
        if (i == var->max.ws_row - 1)
        {
            i = 0;
            j++;
        }
    }
}

int ft_calcule()
{
    t_output *ptrnode;
    float x;
    int l_string;

    ptrnode = head_func(NULL);
    x = ptrnode->llen / ptrnode->max.ws_row;
   /* fprintf(stderr, "max.ws_row %d\n", ptrnode->max.ws_row);
    fprintf(stderr, "max.ws_col %d\n", ptrnode->max.ws_col);
    fprintf(stderr, "ptrnode->llen %d\n", ptrnode->llen);
    fprintf(stderr, "x ==> %f\n", x);
    ft_putchar('\n');*/
    l_string = long_string();
   // fprintf(stderr, "l_string ==> %d\n", l_string);
    int y = x * (l_string + 6);
   // fprintf(stderr, "y ==> %d\n", y);
    //fprintf(stderr, "ptrnode->max.ws_col %d\n", ptrnode->max.ws_col);
    if (y < ptrnode->max.ws_col)
    {
        fill_pos_2(l_string + 6);
        return (1);
    }
    else
        return (0);
}

int windows_size()
{
    t_output *ptrnode;

    ptrnode = head_func(NULL);
    ioctl(0, TIOCGWINSZ , &ptrnode->max);
    if (ptrnode->max.ws_row > ptrnode->llen)
    {
       fill_pos();
       return (1);
    }
    else if (ptrnode->max.ws_row < ptrnode->llen)
    {
        if (ft_calcule())
            return (1);
    }
    return (0);
}

void print_list()
{
    t_output *ptr;

    ptr = head_func(NULL);
    if (windows_size())
    {
        tputs(vi_string, 1, my_putchar);
        while (ptr)
        {
           /* ft_putstr_fd("ptr->cursor --> ", 2);
            ft_putnbr_fd(ptr->cursor, 2);
            ft_putchar_fd('\n', 2);
            ft_putstr_fd("ptr->key --> ", 2);
            ft_putnbr_fd(ptr->key, 2);
            ft_putchar_fd('\n', 2);
             ptr = ptr->next;*/
           // tputs(tgoto(gotostr, 0, 0), 1, my_putchar);
            if (ptr->cursor == 1)
           {
                tputs(us_string, 1, my_putchar);
                tputs(tgoto(gotostr, ptr->position->hpos, ptr->position->vpos), 1, my_putchar);
                ft_putendl_fd(ptr->string, 2);
                tputs(ue_string, 1, my_putchar);
           }
           else
           {
                tputs(tgoto(gotostr, ptr->position->hpos, ptr->position->vpos), 1, my_putchar);
                ft_putendl_fd(ptr->string, 2);
           }
           ptr = ptr->next;
        }
        tputs(tgoto(gotostr, 0, 0), 1, my_putchar);
    }
   else 
       ft_putendl_fd("windows so small", 2);
}
