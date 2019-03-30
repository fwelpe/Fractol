/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/30 12:50:09 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"

int	is_white(float r, float im, float r_start, float im_start, int depth)
{
	float	r_new;
	float	im_new;
	
	if ((r * r + im * im) > 4)
		return (0);
	if (!depth)
		return (1);
	r_new = r * r - im * im + r_start;
	im_new = 2 * r * im + im_start;
	return (is_white(r_new, im_new, r_start, im_start, --depth));
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
			if (is_white(0, 0, (float)(i + s->cam.x_shift) / s->cam.scale - W / s->cam.scale / 2, (float)(j +s->cam.y_shift) / s->cam.scale - H / s->cam.scale / 2, 255))
				mlx_pixel_put(s->mlx_ptr, s->win_ptr, i, j, 0xF5DEB3);
		}
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_fctl	s;

	// printf("Hello World!\n");
	s.mlx_ptr = mlx_init();
	s.win_ptr = mlx_new_window(s.mlx_ptr, W, H, "Whooy");
	if (!s_init(&s))
		return (1);
	//field_iter(&s);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_hook(s.win_ptr, 17, 0, red_button, NULL);
	mlx_hook(s.win_ptr, 4, 0, mouse_press, (void *)&s);
	mlx_hook(s.win_ptr, 5, 0, mouse_release, (void *)&s);
	mlx_hook(s.win_ptr, 6, 0, mouse_move, (void *)&s);
	mlx_loop(s.mlx_ptr);
	return (0);
}
