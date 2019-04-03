/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:04:31 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/03 14:16:51 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	field_iter(t_fctl *s)
{
	int i;
	int j;

	i = -1;
	while (++i < W)
	{
		j = -1;
		while (++j < H)
		{
			s->re[i + W * j] = (i - W / 2) / s->cam.scale + s->cam.re_add;
			s->im[i + W * j] = (H / 2 - j) / s->cam.scale + s->cam.im_add;
		}
	}
}

void	draw(t_fctl *s)
{
	clear_image(s);
	field_iter(s);
	go_cl(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->image_cont, 0, 0);
}

void	zoom(int key, t_fctl *s, int x, int y)
{
	s->cam.re_add += (x - W / 2) / s->cam.scale;
	(void)y;
	(void)x;
	(void)key;
	s->cam.im_add += (H / 2 - y) / s->cam.scale;
	if (key == PLUS)
		s->cam.scale *= 2;
	if (key == MINUS)
		s->cam.scale /= 2;
	draw(s);
}

void	zero_cam(t_fctl *s)
{
	s->cam.scale = H / 5;
	s->cam.re_add = 0;
	s->cam.im_add = 0;
}
