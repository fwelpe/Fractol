/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:11:04 by fwlpe             #+#    #+#             */
/*   Updated: 2019/04/04 22:15:09 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		start(t_fctl *s)
{
	s->mlx_ptr = mlx_init();
	s->win_ptr = mlx_new_window(s->mlx_ptr, W, H, "w!h0oy");
	if (!new_image(s))
		return (0);
	s->pxs = W * H;
	MALLCHECK((s->re = (double *)malloc(sizeof(double) * s->pxs)));
	MALLCHECK((s->im = (double *)malloc(sizeof(double) * s->pxs)));
	zero_cam(s);
	return (1);
}

int		main(int ac, char **av)
{
	t_fctl	s;

	(void)ac;
	(void)av;
	if (!start(&s))
		return (1);
	draw(&s);
	mlx_key_hook(s.win_ptr, deal_key, &s);
	mlx_mouse_hook(s.win_ptr, mouse, (void *)&s);
	mlx_hook(s.win_ptr, 17, 0, red_button, NULL);
	mlx_loop(s.mlx_ptr);
	return (0);
}
