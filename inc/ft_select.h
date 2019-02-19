# ifndef FT_SELECT_H
#define FT_SELECT_H

#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_output
{
    char *string;
    int llen;
    struct s_output *next;
}              t_output;

#endif