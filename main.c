/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/30 16:10:14 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	is_white(float re, float im, float re_start, float im_start, int depth)
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
			if (is_white(0, 0, (float)i / s->cam.scale - W / s->cam.scale / 2, (float)j / s->cam.scale - H / s->cam.scale / 2, 255))
				image_set_pixel(s->image, i, j, 0xF5DEB3);
		}
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_fctl	s;

	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, "Whooy");
	if (!s_init(&s))
		return (1);
	draw(&s);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_hook(s.win_ptr, 17, 0, red_button, NULL);
	mlx_hook(s.win_ptr, 4, 0, mouse_press, (void *)&s);
	// mlx_hook(s.win_ptr, 5, 0, mouse_release, (void *)&s);
	// mlx_hook(s.win_ptr, 6, 0, mouse_move, (void *)&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
