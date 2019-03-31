/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/31 20:05:34 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "defines.h"
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

typedef struct	s_cam
{
	float	re_add;
	float	im_add;
	float	scale;
}				t_cam;

typedef struct	s_fctl
{
	void	*mlx_ptr;
	void	*win_ptr;
	float	scale;
	void	*image_cont;
	char	*adr;
	int		b_p_pix;
	t_cam	cam;
}				t_fctl;

int		red_button(void *param);
int		deal_key(int key, t_fctl *s);
void	image_set_pixel(t_fctl *s, int x, int y, int color);
void	clear_image(t_fctl *s);
int		new_image(t_fctl *s);
int		s_init(t_fctl *s);
int		init_mouse(t_fctl *s);
void	field_iter(t_fctl *s);
void	draw(t_fctl *s);
int		mouse(int button, int x, int y, t_fctl *s);
void	zero_draw(t_fctl *s);
void	zoom(int key, t_fctl *s, int x, int y);

#endif