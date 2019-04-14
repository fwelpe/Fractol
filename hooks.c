/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdenys-a <cdenys-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:02:03 by cdenys-a          #+#    #+#             */
/*   Updated: 2019/04/13 17:59:22 by cdenys-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		deal_key(int key, t_fctl *s)
{
	if (key == ESC)
		exit(0);
	if (key == SPACE)
	{
		zero_cam(s);
		draw(s);
	}
	if (key == CHANGE_COLOR)
		s->cl_store[5] = s->cl_store[5] == 0 ? 1 : 0;
	if (key == RES_UP)
		if (s->cl_store[0] <= 512)
			s->cl_store[0] *= 2;
	if (key == RES_DOWN)
		if (s->cl_store[0] >= 8)
			s->cl_store[0] /= 2;
	draw(s);
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

int		arrows_move_hook(int btn, t_fctl *s)
{
	double step;

	step = 35 / s->cam.scale;
	if (btn == UP)
		s->cam.im_add += step;
	if (btn == DOWN)
		s->cam.im_add -= step;
	if (btn == LEFT)
		s->cam.re_add -= step;
	if (btn == RIGHT)
		s->cam.re_add += step;
	draw(s);
	return (0);
}

int		mouse_move(int x, int y, t_fctl *s)
{
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
