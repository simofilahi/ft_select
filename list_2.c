#include "inc/ft_select.h"


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
		ptrnode->position->vpos = i++;
		ptrnode->position->hpos = y * j;
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
	l_string = long_string();
	int y = x * (l_string + 6);
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
		tputs(VI_STRING, 1, my_putchar);
		while (ptr)
		{
			if (ptr->selected)
			{
				tputs(MR_STRING, 1, my_putchar);
				tputs(tgoto(GOTOSTR, ptr->position->hpos, ptr->position->vpos), 1, my_putchar);
				ft_putendl_fd(ptr->string, 2);
				tputs(ME_STRING, 1, my_putchar);			
			}
			else if (ptr->cursor && !ptr->selected)
			{
				tputs(US_STRING, 1, my_putchar);
				tputs(tgoto(GOTOSTR, ptr->position->hpos, ptr->position->vpos), 1, my_putchar);
				ft_putendl_fd(ptr->string, 2);
				tputs(UE_STRING, 1, my_putchar);
			}
			else
			{		
				tputs(tgoto(GOTOSTR, ptr->position->hpos, ptr->position->vpos), 1, my_putchar);
				ft_putendl_fd(ptr->string, 2);
			}
			ptr = ptr->next;
		}
	}
	else 
		ft_putendl_fd("windows so small", 2);
}