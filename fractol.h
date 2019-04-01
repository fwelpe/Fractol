/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:34:44 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/01 22:43:13 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <CL/cl.h>
# include <stdio.h>
# include "defines.h"
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"

# define MAX_SOURCE_SIZE (0x100000)
# define MALLCHECK(x) if (!x) return (0)

typedef struct	s_cam
{
	double	re_add;
	double	im_add;
	double	scale;
}				t_cam;

typedef struct	s_fctl
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	scale;
	void	*image_cont;
	char	*adr;
	int		b_p_pix;
	double	*re;
	double	*im;
	t_cam	cam;
	int		pxs;
}				t_fctl;

int		red_button(void *param);
int		deal_key(int key, t_fctl *s);
void	image_set_pixel(t_fctl *s, int x, int y, int color);
void	clear_image(t_fctl *s);
int		new_image(t_fctl *s);
void	field_iter(t_fctl *s);
void	draw(t_fctl *s);
int		mouse(int button, int x, int y, t_fctl *s);
void	zero_draw(t_fctl *s);
void	zoom(int key, t_fctl *s, int x, int y);

#endif