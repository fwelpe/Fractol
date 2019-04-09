/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwlpe <fwlpe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:02:03 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/09 18:36:24 by fwlpe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		deal_key(int key, t_fctl *s)
{
	(void)s;
	if (key == ESC)
		exit(0);
	if (key == SPACE)
	{
		zero_cam(s);
		draw(s);
	}
	if (key == RES_UP || key == RES_DOWN)
	{
		s->cl_store[0] = key == RES_UP ?
				s->cl_store[0] * 2 : s->cl_store[0] / 2;
		draw(s);
	}
	return (0);
}

int		mouse(int button, int x, int y, t_fctl *s)
{
	if ((button == PLUS || button == MINUS) && y >= 0)
	{
		zoom(button, s, x, y);
		draw(s);
	}
	return (0);
}

int		mouse_move(int x, int y, t_fctl *s)
{
	printf("Works!\n");
	s->cl_store[10] = (x - W / 2) / s->cam.scale + s->cam.re_add;
	s->cl_store[11] = (H / 2 - y) / s->cam.scale + s->cam.im_add;
	if (ft_strequ(s->f_name, "julia"))
		draw(s);
	return (0);
}

int		red_button(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
