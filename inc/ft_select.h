# ifndef FT_SELECT_H
#define FT_SELECT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <termcap.h>
#include "../libft/libft.h"

#define keyup 4283163
#define keydown 4348699
#define keyright 4414235
#define keyleft 4479771
#define esc 27
#define delete 2117294875
#define backspace 127
#define space 32
#define STDIN_FILENO 0

typedef struct s_output
{
    char *string;
    int llen;
    struct s_output *next;
}              t_output;

#endif