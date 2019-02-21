# ifndef FT_SELECT_H
#define FT_SELECT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include "../libft/libft.h"

#define keyup 4283163
#define keydown 4348699
#define keyright 4414235
#define keyleft 4479771
#define esc 27
#define delete 2117294875
#define backspace 127
#define space 32


#define ti_string tgetstr("ti", NULL)
#define te_string tgetstr("te", NULL)
#define us_string tgetstr("us", NULL)
#define ue_string tgetstr("ue", NULL)
#define mr_string tgetstr("mr", NULL)
#define me_string tgetstr("me", NULL)
#define gotostr tgetstr("ho", NULL)
#define cl_string tgetstr("cl", NULL)

typedef struct s_output
{
    char *string;
    int llen;
    struct termios newconfig;
    struct termios oldconfig;
    struct winsize max;
    struct s_output *next;
    //struct s_output *prev;
}              t_output;

void print_list(t_output **head_ref);
void create_node(t_output **head_ref, char *string, int i);
t_output **create_list(char **argv);
void ft_select(t_output **head);
int my_putchar(int c);
int main(int argc, char **argv);
void ft_termios(t_output **head_ref);

#endif