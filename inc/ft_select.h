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
#define vi_string tgetstr("vi", NULL)
#define ve_string tgetstr("ve", NULL)
#define gotostr tgetstr("cm", NULL)
#define cl_string tgetstr("cl", NULL)

int				SIG_NUM;

typedef struct s_output
{
    char *string;
    int cursor;
    int selected;
    int key;
    int llen;
    struct follower *ptr;
    struct coordone *position;
    struct winsize max;
    struct s_output *next;
    struct s_output *tail;
}              t_output;

struct follower
{
    struct termios newconfig;
    struct termios oldconfig;
};

struct coordone
{
    int vpos;
    int hpos;
};

void print_list();
t_output *add_node(char *string, int cursor, int key);
t_output *create_list(char **argv, int argc);
void ft_select();
int my_putchar(int c);
int main(int argc, char **argv);
void ft_termios();
t_output *head_func(t_output **ptr);
void	signal_handler(int sign);

#endif