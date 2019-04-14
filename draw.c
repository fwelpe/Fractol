/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:04:31 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/14 15:41:03 by cdenys-a         ###   ########.fr       */
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

void	out_params(t_fctl *s)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;

	s1 = "Mouse wheel to zoom. Coursor oriented.";
	s2 = "Arrows to move image.";
	s3 = "'+' or '-' to change precision.";
	s4 = "Space to reset cam. Q for color shift.";
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 0, 0xffffff, s1);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 25, 0xffffff, s2);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 50, 0xffffff, s3);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 75, 0xffffff, s4);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 0, 125, 0xffffff,
			"Precision. Max iters =");
	s5 = ft_itoa(s->cl_store[0]);
	mlx_string_put(s->mlx_ptr, s->win_ptr, 227, 125, 0xffffff, s5);
	free(s5);
}

void	draw(t_fctl *s)
{
	clear_image(s);
	field_iter(s);
	go_cl(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->image_cont, 0, 0);
	out_params(s);
}

void	zoom(int key, t_fctl *s, int x, int y)
{
	(void)y;
	(void)x;
	(void)key;
	s->cam.re_add += ((x - W / 2) / s->cam.scale) / 3;
	s->cam.im_add += ((H / 2 - y) / s->cam.scale) / 3;
	if (key == PLUS && s->cam.scale < 7489396532621200)
		s->cam.scale *= 1.2;
	if (key == MINUS && s->cam.scale > 60)
		s->cam.scale /= 1.2;
}

void	zero_cam(t_fctl *s)
{
	s->cam.scale = H / 5;
	s->cam.re_add = 0;
	s->cam.im_add = 0;
	clstore_reset_precision(s);
	s->cl_store[5] = 0;
}
