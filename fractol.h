/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/29 16:15:56 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define W 1000
# define H 1000
# define ESC 53
# define SPACE 49

# include <math.h>
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

typedef struct		s_mouse
{
	int				button;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;

typedef struct		s_image
{
	void			*image_cont;
	char			*adr;
	int				b_p_pix;
}					t_image;

typedef struct	s_fctl
{
		void	*mlx_ptr;
		void	*win_ptr;
		float	scale;
		t_image	*image;
		t_mouse	*mouse;
}				t_fctl;

int		red_button(void *param);
int		deal_key(int key, t_fctl *s);
void	image_set_pixel(t_image *image, int x, int y, int color);
void	clear_image(t_image *image);
t_image	*del_image(t_fctl *s, t_image *img);
t_image	*new_image(t_fctl *s);
int		s_init(t_fctl *s);
int		init_mouse(t_fctl *s);

#endif