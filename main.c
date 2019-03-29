/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/28 21:09:44 by fwlpe            ###   ########.fr       */
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

void	field_iter(t_mlx *mlx)
{
	int i;
	int j;

	float scale = H / 5;
	i = -1;
	while (++i < W)
	{
		j = -1;
		while (++j < H)
		{
			if (is_white(0, 0, (float)i / scale - W / scale / 2, (float)j / scale - H / scale / 2, 255))
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, i, j, 0xF5DEB3);
		}
	}
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_mlx mlx;

	// printf("Hello World!\n");
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, W, H, "Whooy");
	field_iter(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}