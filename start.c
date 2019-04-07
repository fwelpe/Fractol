/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:49:47 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/07 14:00:40 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
		char *s;

		s = "Usage: ./fractol [mandelbrot / julia / other shit]";
		ft_putendl_fd(s, 2);
}

char	*parse_name(char **av)
{
	if (ft_strequ(av[1], "Mandelbrot") || ft_strequ(av[1], "mandelbrot"))
		return ("mandelbrot");
	if (ft_strequ(av[1], "Julia") || ft_strequ(av[1], "julia"))
		return ("julia");
	else
		return (0);
}

int		start(t_fctl *s, int ac, char **av)
{
	if (ac != 2 || !(s->f_name = parse_name(av)))
	{
		usage();
		return (0);
	}
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, W, H, "w!h0oy");
	if (!new_image(s))
		return (0);
	s->pxs = W * H;
	MALLCHECK((s->re = (double *)malloc(sizeof(double) * s->pxs)));
	MALLCHECK((s->im = (double *)malloc(sizeof(double) * s->pxs)));
	zero_cam(s);
	init_cl(s);
	return (1);
}
