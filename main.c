/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/31 19:57:02 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		is_white(float re, float im, float re_start, float im_start, int depth)
{
	float	re_new;
	float	im_new;
	
	if ((re * re + im * im) > 4)
		return (0);
	if (!depth)
		return (1);
	re_new = re * re - im * im + re_start;
	im_new = 2 * re * im + im_start;
	return (is_white(re_new, im_new, re_start, im_start, --depth));
}

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
			if (is_white(0, 0, (float)i / s->cam.scale - W / s->cam.scale / 2, H / s->cam.scale / 2 - (float)j / s->cam.scale, 255))
				image_set_pixel(s, i, j, 0xF5DEB3);
		}
	}
}

int		start(t_fctl *s)
{
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, W, H, "w!h0oy");
	if (!new_image(s))
		return (0);
	zero_draw(s);
	return (1);
}

int		main(int ac, char **av)
{
	t_fctl	s;

	(void)ac;
	(void)av;
	if (!start(&s))
		return (1);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_mouse_hook(s.win_ptr, mouse, (void *)&s);
	mlx_hook(s.win_ptr, 17, 0, red_button, NULL);
	mlx_loop(s.mlx_ptr);
	return (0);
}
