/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:25:50 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/24 19:38:20 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"

# define KEYUP 4283163
# define KEYDOWN 4348699
# define ESC 27
# define DELETE 2117294875
# define BACKSPACE 127
# define ENTER 10
# define SPACE 32
# define  STDIN_FILENO 0
# define TI_STRING tgetstr("ti", NULL)
# define TE_STRING tgetstr("te", NULL)
# define US_STRING tgetstr("us", NULL)
# define UE_STRING tgetstr("ue", NULL)
# define MR_STRING tgetstr("mr", NULL)
# define ME_STRING tgetstr("me", NULL)
# define VI_STRING tgetstr("vi", NULL)
# define VE_STRING tgetstr("ve", NULL)
# define GOTOSTR tgetstr("cm", NULL)
# define CL_STRING tgetstr("cl", NULL)

typedef	struct	s_output
{
	char				*string;
	int					cursor;
	int					selected;
	int					key;
	int					llen;
	struct s_follower		*ptr;
	struct s_coordone		*position;
	struct winsize		max;
	struct s_output		*next;
	struct s_output		*tail;
}				t_output;

struct			s_follower
{
	struct termios		newconfig;
	struct termios		oldconfig;
};

struct			s_coordone
{
	int					vpos;
	int					hpos;
};

void			print_list();
t_output		*add_node(char *string, int cursor, int key);
t_output		*create_list(char **argv, int argc);
void			ft_select();
int				my_putchar(int c);
int				main(int argc, char **argv);
int				ft_selected();
void			ft_termios();
t_output		*head_func(t_output **ptr);
void			signal_handler(int sign);
void			print_in_stdout();
void			ft_termcap();
void			ft_termios();
void			get_input();
void			apply_new_postion_cursor(int key, int flag);
int				finder_cursor();
void			delete_node();
void			ft_signal();
void			reset_cursor();
int				reset_key();
void			init_tail();
int				last_selected_elem();
void			print_in_stdout();
void			init_coor();
void			normal_mode();
void			fill_pos();
int				long_string();

#endif
