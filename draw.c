/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:04:31 by fwlpe             #+#    #+#             */
/*   Updated: 2019/03/31 19:57:49 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw(t_fctl *s)
{
	clear_image(s);
	field_iter(s);
	mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->image_cont, 0, 0);
}

void	zoom(int key, t_fctl *s)
{
	if (key == PLUS)
		s->cam.scale *= 2;
	if (key == MINUS)
		s->cam.scale /= 2;
	draw(s);
}

void	zero_draw(t_fctl *s)
{
	s->cam.scale = H / 5;
	s->cam.re_add = 0;
	s->cam.im_add = 0;
	draw(s);
}
