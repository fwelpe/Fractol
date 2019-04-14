/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:49:47 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/13 18:22:12 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	usage(void)
{
	char *s;

	s = "Usage: ./fractol [mandelbrot / julia / qube]";
	ft_putendl_fd(s, 2);
}

char	*parse_name(char **av)
{
	if (ft_strequ(av[1], "Mandelbrot") || ft_strequ(av[1], "mandelbrot") ||
			ft_strequ(av[1], "mandelbrot.cl"))
		return ("mandelbrot");
	if (ft_strequ(av[1], "Julia") || ft_strequ(av[1], "julia") ||
			ft_strequ(av[1], "julia.cl"))
		return ("julia");
	if (ft_strequ(av[1], "Qube") || ft_strequ(av[1], "qube") ||
			ft_strequ(av[1], "qube.cl"))
		return ("qube");
	return (0);
}

int		clstore_init(t_fctl *s)
{
	ft_bzero(s->cl_store, sizeof(double) * CLSTORE_SIZE);
	s->cl_store[1] = 0xffffff;
	s->cl_store[2] = 0xff0000;
	s->cl_store[5] = 0;
	return (0);
}

int		clstore_reset_precision(t_fctl *s)
{
	if (ft_strequ(s->f_name, "mandelbrot"))
		s->cl_store[0] = 128;
	if (ft_strequ(s->f_name, "julia"))
		s->cl_store[0] = 32;
	if (ft_strequ(s->f_name, "qube"))
		s->cl_store[0] = 16;
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
	s->win_ptr = mlx_new_window(s->mlx_ptr, W, H, s->f_name);
	if (!new_image(s))
		return (0);
	s->pxs = W * H;
	MALLCHECK((s->re = (double *)malloc(sizeof(double) * s->pxs)));
	MALLCHECK((s->im = (double *)malloc(sizeof(double) * s->pxs)));
	MALLCHECK((s->cl_store = (double *)malloc(sizeof(double) * CLSTORE_SIZE)));
	clstore_init(s);
	zero_cam(s);
	init_cl(s);
	return (1);
}
